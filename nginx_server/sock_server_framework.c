#include "sock_server_framework.h"
SOCKET client_list[10];
int client_idx = 0;
void __cdecl RecvThread(void* p)
{
	SOCKET sock = (SOCKET)p;
	char buf[256];
	while (1)
	{
		//Recive From Client
		int recvsize = recv(sock, buf, sizeof(buf), 0);
		if (recvsize <= 0)		break;
		//------------------------------------------------
		buf[recvsize] = '\0';
		printf("%s\n", buf);
		//Send Data To Clientx
		for (int i = 0; i < client_idx; i++)
		{
			if (client_list[i] != sock)
			{
				int sendsize = send(client_list[i], buf, (int)strlen(buf), 0);
			}
		}
		//-----------------------------------------------
	}
	printf("접속 종료\n");
	//------------vector에 있는 데이터 지우기-----------
	for (int i = 0; i < client_idx; i++)
	{
		if (client_list[i] == sock)
		{
			client_list[i] = NULL;
			break;
		}
	}
	//---------------------------------------------------

	//------------소켓 해제---------------------
	closesocket(sock);
	//----------------------------------------
}
void bind_sock_srv(void) {
	//-------소켓 라이브러리 불러오기(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
	}
	//-------------------------------------------

	//----------소켓 생성--------------
	SOCKET serv_sock;
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
	}
	//-----------------------------------

	//--------서버(자신)의 소켓 정보 입력------------
	SOCKADDR_IN serv_addr = { 0 };					// 초기화
	serv_addr.sin_family = AF_INET;					// IP 사용
	serv_addr.sin_port = htons(2513);				// 포트 4000번
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 주소는 알아서 찾기
	//------------------------------------------------

	//-----------인터넷에 연결---------------------
	retval = bind(serv_sock, (SOCKADDR*)& serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
	}
	//--------------------------------------------

	//-----------대기인원 설정-----------------
	listen(serv_sock, 5);		// 5명까지만 대기할 수 있게 함.
	//-------------------------------------------
	SOCKADDR_IN clnt_addr = { 0 };
	int size = sizeof(SOCKADDR_IN);

	while (1)
	{
		//-------------클라이언트 접속 대기, connect를 하면 리턴함-------------
		SOCKET clnt_sock = accept(serv_sock, (SOCKADDR*)& clnt_addr, &size);
		if (clnt_sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			continue;
		}
		//----------------------------------------------------------------------

		//----------------vector 에 데이터 넣기------------
		client_list[client_idx++] = clnt_sock;
		//--------------------------------------------------

		printf("클라이언트 접속\n");
		printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
		//-----------수신 스레드 생성-------------
		_beginthread(RecvThread, 0, (void*)clnt_sock);
		//-----------------------------------------
	}
	//----------소켓 닫음---------------
	closesocket(serv_sock);
	//-----------------------------------

	//-------라이브러리 해제(?)---------
	WSACleanup();
	//----------------------------------

}
void ErrorHandling(char* message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	char c = _getch();
	exit(1);
}