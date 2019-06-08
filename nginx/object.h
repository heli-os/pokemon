#include "nginx_common.h"

enum OBJECT_LIST {
	FOUNTAIN_1,
	FOUNTAIN_2,
	FOUNTAIN_3,
	CASTLE_1,
	HOUSE_1,
	HOUSE_2
};

typedef struct OBJECT_INFO {
	float sx;
	float sy;
	float sw;
	float sh;
	float dx;
	float dy;
}object_info;
object_info create_object(ALLEGRO_BITMAP* bitmap, int type, float sx, float sy);
