#ifndef _POKEMON_MENU_HEADER_
#define _POKEMON_MENU_HEADER_
#include "nginx_common.h"

ALLEGRO_BITMAP* menuFrame;

/// <summary>
/// 
/// </summary>
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
	POKEBALL_02_MENU,
	ITEM_MARKET_LIST_00,
	ITEM_MARKET_LIST_01,
	PLAYER_GOLD_MENU,
	COMPUTER_SYSTEM_POPUP,
	COMPUTER_SYSTEM_MENU_RELEASE,
	COMPUTER_SYSTEM_MENU_TAKE,
	COMPUTER_SYSTEM_MENU_STORE,
	COMPUTER_SYSTEM_MENU_TRANSFER,
	COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT
};

// maxIndex, 가로, 세로
static int mapMenu[][3] = {
	{4, 8, 6},   // GLOBAL_MENU
	{2, 5, 3},   // POKEBALL_00_MENU
	{2, 5, 3},   // POKEBALL_01_MENU
	{2, 5, 3},	 // POKEBALL_02_MENU
	{6, 11, 9 }, // ITEM_MARKET_LIST_00
	{4, 11, 6 }, // ITEM_MARKET_LIST_01
	{2, 6, 3},   // PLAYER_GOLD_MENU
	{4, 8, 6},	 // COMPUTER_SYSTEM_POPUP
	{6, 25, 18}, // COMPUTER_SYSTEM_MENU_RELEASE
	{6, 25, 18}, // COMPUTER_SYSTEM_MENU_TAKE
	{0,  0,  0}, // COMPUTER_SYSTEM_MENU_STORE
	{6, 25, 18}, // COMPUTER_SYSTEM_MENU_TRANSFER
	{2, 12, 3},	 // COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT
};

static char* mapMenuChar[][6] = {
	{"POKEMON", "BAG", "SAVE", "EXIT"},
	{"YES", "NO"},
	{"YES", "NO"},
	{"YES", "NO"},
	{"POTION","SUPER POTION","HYPER POTION","MAX POTION","ETHER","REVIVE"},
	{"Poke BALL", "GREAT BALL", "ULTRA BALL", "MASTER BALL"},
	{"GOLD", ""},
	{"RELEASE", "TAKE", "STORE", "TRANSFER"},
	{""},
	{""},
	{""},
};

void showMenu(int menuId);
void closeMenu();
void menuHandler();

#endif