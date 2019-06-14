#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <winsock2.h>
#include <Ws2tcpip.h >	
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"Ws2_32.lib ")

#define BUFSIZE 1024
void __cdecl sendMessage(const char* message);
void bind_sock_clnt(void);