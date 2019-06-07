#include "nginx_common.h"

static int map_tile[][50][38] = {
	{{0,}}
};

void init_map(ALLEGRO_BITMAP* bitmap);
void create_object(ALLEGRO_BITMAP* bitmap);