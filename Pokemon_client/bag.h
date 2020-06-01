#pragma once
#ifndef _POKEMON_BAG_HEADER_
#define _POKEMON_BAG_HEADER_
#include "book.h"
#include "nginx_common.h"

typedef struct BAGUI_STATUS {
	bool bagUIOpen;
	bool bagUIConv;
	int currentMenu;
	int currentIndex;
	int lastIndex;
} bagUIStatus;

typedef struct INVENTORY_ITEM {
	int itemType;
	int itemStock;
	char* itemName;
	char* itemDesc[3];
} inventoryItem;

ALLEGRO_BITMAP* bagUIBitmap;

void interactInventory();
void interactItem(int itemNo, pokemon* target);
void drawBagUI();
void closeBagMenu();
#endif