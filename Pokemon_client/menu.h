#ifndef _POKEMON_MENU_HEADER_
#define _POKEMON_MENU_HEADER_
#include "nginx_common.h"

ALLEGRO_BITMAP* menuFrame;

typedef struct MENU_STATUS {
	bool menuOpen;
	int currentMenu;
	int menuIndex;
	int maxMenuIndex;
} menuStatus;

enum MENU_ID {
	GLOBAL_MENU,
	POKEBALL_00_MENU,
	POKEBALL_01_MENU,
	POKEBALL_02_MENU
};

// maxIndex, 가로, 세로
static int mapMenu[][3] = {
	{4, 8, 6}, //GLOBAL_MENU
	{2, 5, 3}, //POKEBALL_00_MENU
	{2, 5, 3}, //POKEBALL_01_MENU
	{2, 5, 3}, //POKEBALL_02_MENU
};

static char* mapMenuChar[][4] = {
	{"POKEMON", "BAG", "SAVE", "EXIT"},
	{"YES", "NO"},
	{"YES", "NO"},
	{"YES", "NO"}
};

void showMenu(int menuId);
void closeMenu();
void menuHandler();

#endif