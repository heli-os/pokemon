#pragma once
#ifndef _NGINX_BAG_HEADER_
#define _NGINX_BAG_HEADER_
#include "nginx_common.h"

typedef struct BAGUI_STATUS {
	bool bagUIOpen;
	bool bagUIConv;
	int currentMenu;
	int currentIndex;
	int lastIndex;
} bagUIStatus;

ALLEGRO_BITMAP* bagUIBitmap;

void drawBagUI();
void closeBagMenu();
#endif