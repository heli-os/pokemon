#ifndef _NGINX_BUSH_HEADER_
#define _NGINX_BUSH_HEADER_
#include "nginx_common.h"
#include "player.h"
static int mapBush[][5] = {
	// Bush in MAP
	{191,44,160,32,1},
	{63,138,114,34,2},
	{271,138,82,34,3},
	{31,170,114,34,4},
	{239,170,82,34,5},
	{191,186,34,82,6}
};

int isBush(player _player);
#endif