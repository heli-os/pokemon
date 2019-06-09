#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#pragma comment(lib,"wsock32.lib")

#define BUFSIZE 1024
#define SOCK_PORT 2513

void bind_sock_srv(void);
void ErrorHandling(char* message);