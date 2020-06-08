#ifndef _POKEMON_CONVERSATION_HEADER_
#define _POKEMON_CONVERSATION_HEADER_
#include "nginx_common.h"

extern ALLEGRO_BITMAP* menuFrame;


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
	POKEMON_HEALING_CONVERSATION
};


static char* mapConversationChar[][2] = {
	{"So, you're claiming the","GRASS Pokemon Bulbasaur?"},
	{"So, you're claiming the","FIRE Pokemon Charmander?"},
	{"So, you're claiming the","WATER Pokemon Squirtle?"},
	{"Save Success!"},
	{"All of your Pokemon have","been restored"}
};

void showConversation(int convsId);
void closeConversation();
void conversationHandler();

#endif