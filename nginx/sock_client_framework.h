#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#pragma comment(lib,"wsock32.lib")

#define BUFSIZE 1024

void bind_sock_clnt(void);
void ErrorHandling(char* message);