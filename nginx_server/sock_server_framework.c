#include "sock_server_framework.h"
void bind_sock_srv(void) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int fromLen, nRcv;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("Load WinSock 2.2 DLL Error");

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");

	memset(&servAddr, 0, sizeof(SOCKADDR_IN));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SOCK_PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(servSock, (void*)& servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("Bind Error");

	if (listen(servSock, 3) == SOCKET_ERROR)
		ErrorHandling("Listen Error");

	fromLen = sizeof(clntAddr);

	clntSock = accept(servSock, (void*)& clntAddr, &fromLen);
	if (clntSock == INVALID_SOCKET) {
		ErrorHandling("Accept Error");
	}
	else {
		printf("%s Connection Complete!\n", inet_ntoa(clntAddr.sin_addr));
		printf("Start ...\n");
	}

	closesocket(servSock);

	while (1) {
		printf("Message Receives ...\n");
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);

		if (nRcv == SOCKET_ERROR) {
			printf("Receive Error..\n");
			break;
		}
		message[nRcv] = '\0';

		if (strcmp(message, "exit") == 0) {
			printf("Close Clinet Connection..\n");
			break;
		}

		printf("Receive Message : %s", message);
		printf("\nSend Message : ");
		gets_s(message,BUFSIZE);
		if (strcmp(message, "exit") == 0) {
			send(clntSock, message, (int)strlen(message), 0);
			break;
		}

		send(clntSock, message, (int)strlen(message), 0);
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