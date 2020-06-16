#include "sock_client_framework.h"
#include "player.h"
#include "environment.h"

SOCKET serv_sock;

extern player user_player;
extern int userNo;

void ErrorHandling(char* message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	char c = _getch();
	exit(1);
}
json_t* htonJson(json_t* header, json_t* data) {
	json_t* jsonData = json_array();
	json_array_append(jsonData, header);
	json_array_append(jsonData, data);
	return jsonData;
}

char* buf;
extern bool loadCompleteFlag;
// 데이터를 수신하는 함수
void __cdecl RecvThread(void* p)
{
	SOCKET sock = (SOCKET)p;
	// 무한히 반복하면서 데이터 수신
	while (1)
	{
		// 버퍼를 BUF_SIZE로 동적 할당
		buf = (char*)malloc(BUF_SIZE);
		memset(buf, 0, BUF_SIZE);
		// 패킷 수신 대기 From Server(_beginThread)
		int recvsize = recv(sock, buf, BUF_SIZE, 0);
		if (recvsize <= 0)
		{
			printf("접속종료\n");
			break;
		}

		// 수신한 패킷에서 헤더와 데이터를 분리
		json_error_t error;
		json_t* pMessage = json_loads(buf, JSON_ENCODE_ANY, &error);
		json_t* pHeader = json_array_get(pMessage, 0);
		json_t* pData = json_array_get(pMessage, 1);

		printf("receiveMessage, size = %d\n", (int)strlen(buf));

		const char* ContentType = json_string_value(json_array_get(pHeader, 0));
		// ContenType이 없다면 별 다른 처리를 하지 않음.
		if (ContentType == NULL) {
			free(pMessage);
			free(pHeader);
			free(pData);
			free(buf);
			continue;
		}

		/* 
			LOAD와 SAVE는 용량이 크기때문에 비동기적으로 처리하기에 부적합하다.
			이에 LOAD 성공, SAVE 성공 패킷 수신을 대기한다.
		*/
		// ContentType이 LOAD_COMPLATE라면, 세이브 파일을 파싱한다.
		printf("ContentType IS %s\n", ContentType);
		if (strcmp(ContentType, "LOAD_COMPLETE") == 0) {
			environmentParse(json_loads(json_string_value(json_array_get(pData, 0)), JSON_ENCODE_ANY, &error));
			loadCompleteFlag = true;
		}
		// ContentType이 SAVE_COMPLETE라면, 실제 세이브 수행
		else if (strcmp(ContentType, "SAVE_COMPLETE") == 0) {
			environmentSave(userNo, 1);
		}
		free(pMessage);
		free(pHeader);
		free(pData);
		free(buf);
	}
}

// 서버에 메시지를 전송하는 함수
void __cdecl sendMessage(const json_t* message) {

	char* buf = json_dumps(message, JSON_ENCODE_ANY);
	printf("sendMessage, size = %d\n", (int)strlen(buf));

	// send Packet Data (Client To Server)
	int sendsize = send(serv_sock, buf, (int)strlen(buf), 0);
	free(buf);
}

// 서버에 접속하는 함수
void bind_sock_clnt(void) {
	// 소켓 라이브러리 불러오기
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
	}

	// 소켓 생성
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP를 이용한 소켓

	// 서버 정보 입력(포트는 23245)
	SOCKADDR_IN serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(23245);

	// 서버 접속(AWS)
	serv_addr.sin_addr.s_addr = inet_addr("15.165.97.230");

	retval = connect(serv_sock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("connect() Error\n");
	}

	// 서버 접속 성공 시 데이터 수신 쓰레드 생성
	_beginthread(RecvThread, 0, (void*)serv_sock);
}
