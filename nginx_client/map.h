#include "nginx_common.h"

static int map_tile[][75][60] = {
	{{0,}}
};

void init_map(ALLEGRO_BITMAP* bitmap);


ALLEGRO_BITMAP* world_map;