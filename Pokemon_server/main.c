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

#define BUF_SIZE 50000
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

	// argument로 bind port를 전달 받는데, 없다면 프로그램을 종료한다.
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// 다중 클라이언트 지원을 위한 POSIX 쓰레드 뮤텍스 초기화
	pthread_mutex_init(&mutx, NULL);

	// 서버 바인드 관련 정보 초기화
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	// 바인드 수행
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
	}
	//error_handling("bind() error");
	// listen 수행
	if (listen(serv_sock, 5) == -1)
	{
	}
	//error_handling("listen() error");

	// 무한히 반복하면 클라이언트 대기
	printf("waiting Client...\n");
	while (1)
	{
		// 클라이언트의 연결 요청을 accept
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		// 최대 수용 클라이언트를 초과했다면 연결 요청 반려
		if (clnt_cnt >= MAX_CLNT) {
			printf("CONNECT FAIL : %d \n", clnt_sock);
			write(clnt_sock, "too many users. sorry", BUF_SIZE);
			continue;
		}

		// POSIX 쓰레드 뮤텍스 점유(lock)
		pthread_mutex_lock(&mutx);

		// 클라이언트 배열에 연결 요청을 한 클라이언트 대입
		clnt_socks[clnt_cnt] = clnt_sock;

		// POSIX 쓰레드 뮤텍스 점유 종료(unlock)
		pthread_mutex_unlock(&mutx);

		// 패킷 송수신을 위한 handle_clnt에 대응하는 쓰레드 생성
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP: %s\n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

// 에러 발생에 따른 핸들링 처리
void error_handling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

// 클라이언트의 패킷 수신에 따른 로직 처리
void* handle_clnt(void* arg)
{
	int n;
	printf("%s\n", cSend_msg);
	int saveDataSize = -1;
	// 무한히 반복하면서 데이터 수신을 대기(read) 한다. 
	// 만약 1이상의 값을 정상적으로 수신했다면 관련 내용을 처리한다.
	while ((n = read(*(int*)arg, cLatLng, BUF_SIZE)) > 0)
	{
		//printf("%s\n", cLatLng);
		// saveDataSize가 -1이 아니라면, 클라이언트가 SAVE 요청을 보낸 것이다.
		if (saveDataSize != -1) {
			// 데이터가 크기때문에 한 번에 데이터를 수신할 수 없어 모든 데이터를 수신할 때까지 무한히 수신한다.
			while (strlen(cLatLng) < saveDataSize) {
				n = read(*(int*)arg, &cLatLng[strlen(cLatLng)], BUF_SIZE - strlen(cLatLng));
				printf("strlen(cLatLng):%d\nsaveDataSize:%d\nn:%d\n", strlen(cLatLng), saveDataSize, n);
				if (n == 0) break;
			}
			saveDataSize = -1;
		}

		// 클라이언트가 송신한 Json 패킷의 헤더와 데이터부를 추출한다.
		json_error_t error;
		json_t* pMessage = json_loads(cLatLng, JSON_ENCODE_ANY, &error);
		json_t* pHeader = json_array_get(pMessage, 0);
		json_t* pData = json_array_get(pMessage, 1);

		// 그중 ContentType을 추출한다.
		const char* ContentType = json_string_value(json_array_get(pHeader, 0));
		printf("ContentType is %s\n", ContentType);

		// ContentType이 NULL이라면 별 다른 인터랙션을 수행하지 않는다.
		if (ContentType == NULL) {
			memset(cLatLng, 0, sizeof(cLatLng));
			continue;
		}
		// ContentType이 PLAYER라면 Player의 상태 정보이다. 이를 파싱하여 출력한다.
		if (strcmp(ContentType, "PLAYER") == 0) {
			//printf("ContentType is PLAYER\n");
			const char* userName = json_string_value(json_array_get(pData, 0));
			const int userPosX = json_integer_value(json_array_get(pData, 4));
			const int userPosY = json_integer_value(json_array_get(pData, 5));

			printf("userName:%s, posX:%d, posY:%d\n", userName, userPosX, userPosY);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		// SAVE_SIZE라면, SAVE Data의 크기를 의미한다.
		else if (strcmp(ContentType, "SAVE_SIZE") == 0) {
			saveDataSize = json_integer_value(json_array_get(pData, 0));
			json_t* pHeader = json_array();
			json_t* pData = json_array();

			json_array_append_new(pHeader, json_string("SAVE_COMPLETE"));
			json_array_append_new(pData, json_string("READY"));

			json_t* jsonArray = json_array();
			json_array_append(jsonArray, pHeader);
			json_array_append(jsonArray, pData);

			// SAVE가 준비되었다면, 클라이언트에게 SAVE_COMPLETE 패킷을 송신한다.
			char sendBuf[BUF_SIZE] = { 0 };
			sprintf(sendBuf, "%s", json_dumps(jsonArray, JSON_ENCODE_ANY));
			//printf("%s\n", sendBuf);
			write(*(int*)arg, sendBuf, sizeof(sendBuf));
		}
		// SAVE라면, 실제 SAVE를 수행한다.
		else if (strcmp(ContentType, "SAVE") == 0) {
			//printf("ContentType is SAVE\n");
			const int userNo = json_integer_value(json_array_get(pData, 0));
			const char* pkms = json_dumps(json_array_get(pData, 1), JSON_ENCODE_ANY);

			// 유저 고유 식별코드(userNo)를 바탕으로 데이터베이스를 갱신한다.
			char query[BUF_SIZE] = { 0 };
			sprintf(query, "update data set pkms=%s where userNo=%d", pkms, userNo);

			mysql_init(&conn);
			connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

			mysql_query(connection, query);

			mysql_close(&conn);

			saveDataSize = -1;
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		// LOAD라면, 실제 LOAD를 수행한다.
		else if (strcmp(ContentType, "LOAD") == 0) {
			//printf("%s\n", cLatLng);
			const int userNo = json_integer_value(json_array_get(pData, 0));

			mysql_init(&conn);
			connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

			MYSQL_RES* result = NULL;
			MYSQL_ROW row = { 0 };

			char query[255] = { 0 };
			sprintf(query, "select * from data where userNo=%d", userNo);

			// 유저 고유 식별코드(userNo)를 바탕으로 데이터베이스에서 Save Data를 가져온다.
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

				// 데이터베이스에서 가져온 Save Data를 클라이언트에게 전송한다.
				char sendBuf[BUF_SIZE] = { 0 };
				sprintf(sendBuf, "%s", json_dumps(jsonArray, JSON_ENCODE_ANY));
				//printf("%s\n", sendBuf);
				write(*(int*)arg, sendBuf, sizeof(sendBuf));
			}
			mysql_close(&conn);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		// TRANSFER라면, 포켓몬 전송에 대한 패킷이다.
		else if (strcmp(ContentType, "TRANSFER") == 0) {
			char userID[15] = { 0 };
			char transferPokemon[500] = { 0 };
			sprintf(userID, "%s", json_string_value(json_array_get(pData, 0)));
			sprintf(transferPokemon, "%s", json_string_value(json_array_get(pData, 1)));

			mysql_init(&conn);
			connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

			MYSQL_RES* result = NULL;
			MYSQL_ROW row = { 0 };

			char query[255] = { 0 };
			sprintf(query, "select * from user where userid='%s'", userID);
			// userID를 기반으로하기에, 우선 유저 고유 식별코드(userNo)를 추출한다.
			if (mysql_query(connection, query) == 0) {
				result = mysql_store_result(connection);
				// 정상적으로 추출되었다면,
				if (mysql_num_rows(result) != 0) {
					row = mysql_fetch_row(result);
					int userNo = atoi(row[0]);

					char query[255] = { 0 };
					sprintf(query, "select * from data where userNo=%d", userNo);
					// 해당 유저 고유 식별코드를 바탕으로 세이브 데이터를 읽어온다.
					if (mysql_query(connection, query) == 0) {
						result = mysql_store_result(connection);

						json_error_t jError;

						char pkms[BUF_SIZE];
						row = mysql_fetch_row(result);
						sprintf(pkms, "%s", row[1]);
						// 읽어온 세이브 데이터 중, COMPUTER_LIST에 대응하는 Object의 Arrays 중 빈 공간을 찾는다.
						// 찾았다면 해당 공간에 전송된 포켓몬을 넣어준다.
						// 그 후 userNo를 바탕으로 세이브 데이터를 갱신한다.
						for (int i = 0; i < 35; i++) {
							json_t* pkmsJson = json_loads(pkms, JSON_ENCODE_ANY, &jError);
							json_t* tmpData = json_array_get(json_object_get(pkmsJson, "COMPUTER_LIST"), i);
							int tmpNo = json_integer_value(json_object_get(tmpData, "no"));
							if (tmpNo == -1) {
								json_array_set(json_object_get(pkmsJson, "COMPUTER_LIST"), i, json_loads(transferPokemon, JSON_ENCODE_ANY, &jError));
								memset(query, 0, sizeof(query));
								sprintf(query, "update data set pkms=%s where userNo=%d", json_dumps(json_string(json_dumps(pkmsJson, JSON_ENCODE_ANY)), JSON_ENCODE_ANY), userNo);
								mysql_query(connection, query);
								break;
							}
						}
					}
				}
			}
			mysql_close(&conn);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
		// 사전에 정의되지 않은 ContentType 혹은 포맷이라면 요청 전문을 출력한다.
		else {
			printf("arg: %d, LatLng: %s ,size:  %d, n: %d\n", *(int*)arg, cLatLng, (int)sizeof(cLatLng), n);
			memset(cLatLng, 0, sizeof(cLatLng));
		}
	}
}