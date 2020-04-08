#ifndef _NGINX_OBJECT_HEADER_
#define _NGINX_OBJECT_HEADER_
#include "nginx_common.h"
#include "player.h"
static int objectItem[][4] = {
	{0},
	// 포켓볼
	{10,392,10,10}
};

enum OBJECT_ID {
	LAB_POKEBALL_0,
	LAB_POKEBALL_1,
	LAB_POKEBALL_2
};


typedef struct _OBJEECT_BOX {
	int btmId;
	int type;
	int sx;
	int sy;
	int sw;
	int sh;
}objectBox;

static objectBox* objBoxes = NULL;
void initObject(ALLEGRO_BITMAP* object);
int isObject(const player _player);
void interactObject(int objId);
#endif