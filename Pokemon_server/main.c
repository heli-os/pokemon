#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include <jansson.h>
#include <mysql.h>

#define BUF_SIZE 16384
#define MAX_CLNT 100
#define NAME_SIZE 512

void* handle_clnt(void* arg);
void send_msg(char* msg, int len);
void error_handling(char* msg);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
char clnt_name[NAME_SIZE] = {};
char clnt_names[MAX_CLNT][NAME_SIZE] = {};
char cLatLng[BUF_SIZE] = {};
char cSend_msg[BUF_SIZE] = {};

pthread_mutex_t mutx;

#define DB_HOST "jupiterflow.com"
#define DB_USER "pokemon"
#define DB_PASS "xvxjXqmnOweW8QYv"
#define DB_NAME "pokemon"

MYSQL* connection = NULL;
MYSQL conn = { 0 };

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock, i;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	pthread_t t_id;
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

	pthread_mutex_init(&mutx, NULL);
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
	}
	//error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
	{
	}
	//error_handling("listen() error");
	printf("waiting Client...\n");

	while (1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		if (clnt_cnt >= MAX_CLNT) {
			printf("CONNECT FAIL : %d \n", clnt_sock);
			write(clnt_sock, "too many users. sorry", BUF_SIZE);
			continue;
		}


		pthread_mutex_lock(&mutx);

		clnt_socks[clnt_cnt] = clnt_sock;

		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP: %s\n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

void error_handling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void* handle_clnt(void* arg)
{
	int n;
	printf("%s\n", cSend_msg);
	int saveDataSize = -1;
	while ((n = read(*(int*)arg, cLatLng, BUF_SIZE)) > 0)
	{
		if (saveDataSize != -1) {
			while (strlen(cLatLng) < saveDataSize) {
				n = read(*(int*)arg, &cLatLng[strlen(cLatLng)], BUF_SIZE - strlen(cLatLng));
				printf("strlen(cLatLng):%d\nsaveDataSize:%d\nn:%d\n", strlen(cLatLng), saveDataSize, n);
				if (n == 0) break;
			}
			saveDataSize = -1;
		}

		json_error_t error;
		json_t* pMessage = json_loads(cLatLng, JSON_ENCODE_ANY, &error);
		json_t* pHeader = json_array_get(pMessage, 0);
		json_t* pData = json_array_get(pMessage, 1);


		const char* ContentType = json_string_value(json_array_get(pHeader, 0));
		printf("ContentType is %s\n", ContentType);
		if (strcmp(ContentType, "PLAYER") == 0) {
			//printf("ContentType is PLAYER\n");
			const char* userName = json_string_value(json_array_get(pData, 0));
			const int userPosX = json_integer_value(json_array_get(pData, 4));
			const int userPosY = json_integer_value(json_array_get(pData, 5));

			printf("userName:%s, posX:%d, posY:%d\n", userName, userPosX, userPosY);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		else if (strcmp(ContentType, "SAVE_SIZE") == 0) {
			saveDataSize = json_integer_value(json_array_get(pData, 0));
		}
		else if (strcmp(ContentType, "SAVE") == 0) {
			//printf("ContentType is SAVE\n");
			const int userNo = json_integer_value(json_array_get(pData, 0));
			const char* pkms = json_dumps(json_array_get(pData, 1), JSON_ENCODE_ANY);

			char query[BUF_SIZE] = { 0 };
			sprintf(query, "update data set pkms=%s where userNo=%d", pkms, userNo);
			mysql_query(connection, query);
			saveDataSize = -1;
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		else if (strcmp(ContentType, "LOAD") == 0) {
			//printf("%s\n", cLatLng);
			const int userNo = json_integer_value(json_array_get(pData, 0));

			MYSQL_RES* result = NULL;
			MYSQL_ROW row = { 0 };

			char query[255] = { 0 };
			sprintf(query, "select * from data where userNo=%d", userNo);

			if (mysql_query(connection, query) == 0) {
				result = mysql_store_result(connection);

				char writeBuf[BUF_SIZE];
				row = mysql_fetch_row(result);
				sprintf(writeBuf, "%s", row[1]);

				json_t* pHeader = json_array();
				json_t* pData = json_array();

				json_array_append_new(pHeader, json_string("LOAD_COMPLETE"));
				json_array_append_new(pData, json_string(writeBuf));

				json_t* jsonArray = json_array();
				json_array_append(jsonArray, pHeader);
				json_array_append(jsonArray, pData);

				char sendBuf[BUF_SIZE] = { 0 };
				sprintf(sendBuf, "%s", json_dumps(jsonArray, JSON_ENCODE_ANY));
				//printf("%s\n", sendBuf);
				write(*(int*)arg, sendBuf, sizeof(sendBuf));
			}
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		else {
			printf("arg: %d, LatLng: %s ,size:  %d, n: %d\n", *(int*)arg, cLatLng, (int)sizeof(cLatLng), n);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
	}
}