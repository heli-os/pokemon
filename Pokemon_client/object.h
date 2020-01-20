#ifndef _NGINX_OBJECT_HEADER_
#define _NGINX_OBJECT_HEADER_
#include "nginx_common.h"

#define OBJECT_COUNT 5

enum OBJECT_LIST {
	FOUNTAIN_1,
	FOUNTAIN_2,
	FOUNTAIN_3,
	CASTLE_1,
	HOUSE_1,
	HOUSE_2
};

typedef struct OBJECT_INFO {
	float dx;
	float dy;
	float sw;
	float sh;
}object_info;
object_info create_object(ALLEGRO_BITMAP* bitmap, int type, float dx, float dy);

#endif