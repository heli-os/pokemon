#include "sock_client_framework.h"





void bind_sock_clnt(void) {

	SOCKET clntSock;
	WSADATA wsaData;
	SOCKADDR_IN servAddr;

	char sAddr[15] = "127.0.0.1";
	int sPort = 2513;
	int nRcv;
	char message[BUFSIZE];

	//printf("Server Address : ");       gets(sAddr);
	//printf("%s", sAddr);
	//printf("Port Number : ");       gets(message);
	//sPort = atoi(message);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("Load WinSock 2.2 DLL Error");

	clntSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clntSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(sAddr);
	servAddr.sin_port = htons(sPort);

	if (connect(clntSock, (void*)& servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("Connection Error");
	}
	else {
		printf("Connect OK!\nStart...\n");
	}

	while (1) {
		printf("\nSend Message : ");
		gets_s(message,BUFSIZE);

		if (strcmp(message, "exit") == 0) {
			send(clntSock, message, (int)strlen(message), 0);
			break;
		}

		send(clntSock, message, (int)strlen(message), 0);
		printf("Message Receives ...\n");

		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);
		if (nRcv == SOCKET_ERROR) {
			printf("Receive Error..\n");
			break;
		}
		message[nRcv] = '\0';

		if (strcmp(message, "exit") == 0) {
			printf("Close Server Connection..\n");
			break;
		}

		printf("Receive Message : %s", message);
	}

	closesocket(clntSock);
	WSACleanup();
	printf("Close Connection..\n");
	
	_getch();

}


void ErrorHandling(char* message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	_getch();
	exit(1);
}