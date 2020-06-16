#ifndef _POKEMON_CONVERSATION_HEADER_
#define _POKEMON_CONVERSATION_HEADER_
#include "nginx_common.h"

extern ALLEGRO_BITMAP* menuFrame;

/*
Conversation 상태를 저장하는 구조체
	bool convsOpen;
	int currentConvs;
	int index;
	int maxIndex;
*/
typedef struct CONVERSATION {
	bool convsOpen;
	int currentConvs;
	int index;
	int maxIndex;
} conversationStatus;

enum CONVERSATION_ID {
	POKEBALL_00_CONVERSATION,
	POKEBALL_01_CONVERSATION,
	POKEBALL_02_CONVERSATION,
	SAVE_SUCCESS_CONVERSATION,
	POKEMON_HEALING_CONVERSATION,
	ITEM_MARKET_CONVERSATION,
	ITEM_BUY_FAIL_CONVERSATION
};


static char* mapConversationChar[][2] = {
	{"So, you're claiming the","GRASS Pokemon Bulbasaur?"},
	{"So, you're claiming the","FIRE Pokemon Charmander?"},
	{"So, you're claiming the","WATER Pokemon Squirtle?"},
	{"Save Success!"},
	{"All of your Pokemon have","been restored"},
	{"You can purchase items"," here"},
	{"You don't have enough gold","to purchase the item"}
};

/// <summary>
/// Conversation을 그리는 함수
/// </summary>
/// <param name="convsId"></param>
void showConversation(int convsId);

/// <summary>
/// Conversation을 닫는 함수
/// </summary>
void closeConversation();

/// <summary>
/// Conversation 인터랙션을 처리하는 핸들러 함수
/// </summary>
void conversationHandler();

#endif