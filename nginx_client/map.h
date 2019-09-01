#include "nginx_common.h"

void init_terrain(ALLEGRO_BITMAP* bitmap);

static char mapChapter1[9][11] = {
	"11111111111",
	"00000000000",
	"00000000000",
	"00000000000",
	"00000000000",
	"00000000000",
	"00000000000",
	"00000000000",
	"00000000000"
};



ALLEGRO_BITMAP* world_map;