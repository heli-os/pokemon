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
void __cdecl RecvThread(void* p)
{
	SOCKET sock = (SOCKET)p;
	char buf[16384];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		//Recive wait From Server(_beginThread)
		int recvsize = recv(sock, buf, sizeof(buf), 0);
		if (recvsize <= 0)
		{
			printf("접속종료\n");
			break;
		}
		//------------------------------------------------
		json_error_t error;
		json_t* pMessage = json_loads(buf, JSON_ENCODE_ANY, &error);
		json_t* pHeader = json_array_get(pMessage, 0);
		json_t* pData = json_array_get(pMessage, 1);
		printf("receiveMessage, size = %d\n", (int)strlen(buf));
		const char* ContentType = json_string_value(json_array_get(pHeader, 0));
		if (ContentType == NULL) continue; 
		if (strcmp(ContentType, "LOAD_COMPLETE") == 0) {
			environmentParse(json_loads(json_string_value(json_array_get(pData, 0)), JSON_ENCODE_ANY, &error));
		}
		else if (strcmp(ContentType, "SAVE_COMPLETE") == 0) {
			environmentSave(userNo, 1);
		}
		free(pMessage);
		free(pHeader);
		free(pData);
	}
}

void __cdecl sendMessage(const json_t* message) {

	char* buf = json_dumps(message, JSON_ENCODE_ANY);
	//sprintf_s(buf, sizeof(buf), "[%s] %s",nick, message);
	printf("sendMessage, size = %d\n", (int)strlen(buf));

	//send Packet Data (Client To Server)
	int sendsize = send(serv_sock, buf, (int)strlen(buf), 0);
	//if (sendsize <= 0)
	//------------------------------------------
}

void bind_sock_clnt(void) {

	//-------소켓 라이브러리 불러오기(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
	}
	//------------------------------------------

	//---------소켓생성-------- 
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//TCP를 이용한 소켓
	//-------------------------

	//---------서버 정보 입력--------------------
	SOCKADDR_IN serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(23245);

	//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_addr.s_addr = inet_addr("15.165.97.230");




	retval = connect(serv_sock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("connect() Error\n");
	}
	//-------------------------------

	//printf("닉네임 >> ");
	//gets_s(nick,sizeof(nick));
	_beginthread(RecvThread, 0, (void*)serv_sock);
	/*
	while (1)
	{
		char buf[256] = { 0 };
		char str[256];
		printf(">> ");
		gets_s(str,sizeof(str));
		sprintf_s(buf, sizeof(buf),"[%s] %s", nick, str);

		//---------서버에 메시지 전송---------------
		int sendsize = send(serv_sock, buf, (int)strlen(buf), 0);
		if (sendsize <= 0)
			break;
		//------------------------------------------
	}
	*/
	//----------소켓 닫음------------------
	//closesocket(serv_sock);
	//-------------------------------------

	//---------라이브러리 해제(?)---------
	//WSACleanup();
	//-------------------------------------

}
