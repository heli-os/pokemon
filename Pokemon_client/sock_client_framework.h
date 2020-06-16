#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "nginx_common.h"

#include <winsock2.h>
#include <Ws2tcpip.h >	
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* 
	윈도우 소켓 사용을 위한 전처리기 선언/수행
*/
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"Ws2_32.lib ")

/// <summary>
/// 서버에 메시지를 전송하는 함수
/// </summary>
/// <param name="message"></param>
/// <returns></returns>
void __cdecl sendMessage(const json_t* message);

/// <summary>
/// 헤더와 데이터부를 합쳐 하나의 JSON Array로 만들어주는 함수
/// </summary>
/// <param name="header"></param>
/// <param name="data"></param>
/// <returns>Json Array</returns>
json_t* htonJson(json_t* header, json_t* data);

/// <summary>
/// 서버에 접속하는 함수
/// </summary>
void bind_sock_clnt(void);
