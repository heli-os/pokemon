#include "sock_client_framework.h"
#include "player.h"

SOCKET serv_sock;

extern char messages[5][256];

extern player user_player;

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
	char buf[256];
	int i;
	for (i = 0; i < 5; i++) messages[i][0] = 0;
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

		const char* ContentType = json_string_value(json_array_get(pHeader, 0));
		if (ContentType == NULL) continue;
		if (strcmp(ContentType, "CHAT") == 0)
		{
			const char* UserName = json_string_value(json_array_get(pData, 0));
			const char* ChatData = json_string_value(json_array_get(pData, 1));

			int i;
			for (i = 0; i < 4; i++) strcpy_s(&messages[i][0], 256, &messages[i + 1][0]);

			sprintf_s(&messages[4][0], 256, "[%s] %s", UserName, ChatData);
		}
		free(pMessage);
		free(pHeader);
		free(pData);
	}
}

void __cdecl sendMessage(const json_t* message) {

	char* buf = json_dumps(message, JSON_ENCODE_ANY);
	//sprintf_s(buf, sizeof(buf), "[%s] %s",nick, message);

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
	serv_addr.sin_port = htons(4000);

	char* server_type;
	server_type = "local";
	if (server_type == "remote") {
		struct addrinfo hints;
		struct addrinfo* servinfo; // 결과를 저장할 변수
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET; // IPv4만 받겠다.
		hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
		int status = getaddrinfo("foretion.codns.com", "http", &hints, &servinfo);

		struct sockaddr_in* saddr = (struct sockaddr_in*)servinfo->ai_addr;
		char* ip_addr = inet_ntoa(saddr->sin_addr);
		serv_addr.sin_addr = saddr->sin_addr; //SOCKADDR_IN::sin_addr에 할당
		freeaddrinfo(servinfo);
	}
	else if (server_type == "local") {
		serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	}


	retval = connect(serv_sock, (SOCKADDR*)& serv_addr, sizeof(SOCKADDR));
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
