#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "nginx_common.h"

#include <winsock2.h>
#include <Ws2tcpip.h >	
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"Ws2_32.lib ")

#define BUFSIZE 1024

void __cdecl sendMessage(const json_t* message);
json_t* htonJson(json_t* header, json_t* data);
void bind_sock_clnt(void);
