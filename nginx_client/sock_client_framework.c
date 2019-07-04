#include "sock_client_framework.h"
#include "player.h"

SOCKET serv_sock;

extern char messages[5][256];

extern player_status user_player;

extern player_status user_list[10];
extern int player_idx;
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
		else if (strcmp(ContentType, "JOIN_GAME") == 0)
		{
			const char* userName = json_string_value(json_array_get(pData, 0));
			const int action_type = json_integer_value(json_array_get(pData, 1));
			const int player_direction = json_integer_value(json_array_get(pData, 2));
			const int action_idx = json_integer_value(json_array_get(pData, 3));
			const int pos_x = json_integer_value(json_array_get(pData, 4));
			const int pos_y = json_integer_value(json_array_get(pData, 5));
			const int hp = json_integer_value(json_array_get(pData, 6));
			const int armor = json_integer_value(json_array_get(pData, 7));
			const int buf = json_integer_value(json_array_get(pData, 8));

			strcpy_s(user_list[player_idx].cName, 12, userName);

			user_list[player_idx].iAction_type = action_type;
			user_list[player_idx].iPlayer_direction = player_direction;
			user_list[player_idx].iAction_idx = action_idx;

			user_list[player_idx].iPos_x = pos_x;
			user_list[player_idx].iPos_y = pos_y;

			user_list[player_idx].iHp = hp;
			user_list[player_idx].iArmor = armor;
			user_list[player_idx].iBuf = buf;

			player_idx++;
		}
		else if (strcmp(ContentType, "PLAYER") == 0)
		{
			const char* userName = json_string_value(json_array_get(pData, 0));
			const int action_type = json_integer_value(json_array_get(pData, 1));
			const int player_direction = json_integer_value(json_array_get(pData, 2));
			const int action_idx = json_integer_value(json_array_get(pData, 3));
			const int pos_x = json_integer_value(json_array_get(pData, 4));
			const int pos_y = json_integer_value(json_array_get(pData, 5));
			const int hp = json_integer_value(json_array_get(pData, 6));
			const int armor = json_integer_value(json_array_get(pData, 7));
			const int buf = json_integer_value(json_array_get(pData, 8));


			int i;
			bool exist = false;
			for (i = 0; i < player_idx; i++) {
				if (strcmp(user_list[i].cName,userName)==0)
				{
					exist = true;
					user_list[i].iAction_type = action_type;
					user_list[i].iPlayer_direction = player_direction;
					user_list[i].iAction_idx = action_idx;

					user_list[i].iPos_x = pos_x;
					user_list[i].iPos_y = pos_y;

					user_list[i].iHp = hp;
					user_list[i].iArmor = armor;
					user_list[i].iBuf = buf;
				}
			}
			
			if (!exist) {
				strcpy_s(user_list[player_idx].cName, 12, userName);
				user_list[player_idx].iAction_type = action_type;
				user_list[player_idx].iPlayer_direction = player_direction;
				user_list[player_idx].iAction_idx = action_idx;

				user_list[player_idx].iPos_x = pos_x;
				user_list[player_idx].iPos_y = pos_y;

				user_list[player_idx].iHp = hp;
				user_list[player_idx].iArmor = armor;
				user_list[player_idx].iBuf = buf;
				player_idx++;
			}
			
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
	serv_addr.sin_port = htons(2513);

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
