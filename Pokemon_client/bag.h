#pragma once
#ifndef _POKEMON_BAG_HEADER_
#define _POKEMON_BAG_HEADER_
#include "book.h"
#include "nginx_common.h"

/*
가방 상태를 저장하는 구조체
	bool bagUIOpen;
	bool bagUIConv;
	int currentMenu;
	int currentIndex;
*/
typedef struct BAGUI_STATUS {
	bool bagUIOpen;
	bool bagUIConv;
	int currentMenu;
	int currentIndex;
	int lastIndex;
} bagUIStatus;

/*
인벤토리 아이템을 저장하는 구조체
	int itemType;
	int itemStock;
	int itemPrice;
	char* itemName;
	char* itemDesc[3];
*/
typedef struct INVENTORY_ITEM {
	int itemType;
	int itemStock;
	int itemPrice;
	char* itemName;
	char* itemDesc[3];
} inventoryItem;

// 가방 UI 비트맵을 저장하는 변수
ALLEGRO_BITMAP* bagUIBitmap;

/// <summary>
/// 인벤토리 상호작용에 대한 함수
/// </summary>
void interactInventory();
/// <summary>
/// 아이템 상호작용에 대한 함수
/// </summary>
/// <param name="itemNo"></param>
/// <param name="target"></param>
void interactItem(int itemNo, pokemon* target);
/// <summary>
/// 가방 UI를 그리는 함수
/// </summary>
void drawBagUI();
/// <summary>
/// 가방 메뉴를 닫는 함수
/// </summary>
void closeBagMenu();
#endif