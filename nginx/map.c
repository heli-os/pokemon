#include "map.h"

void init_map(ALLEGRO_BITMAP* bitmap) {
	memset(map_tile, 0, sizeof(map_tile));
	for (int i = 0; i < 75; i++) {
		for (int j = 0; j < 60; j++) {
			switch (map_tile[0][i][j]) {
				case 0:
					al_draw_bitmap_region(bitmap, 0, 0, 16, 16, 16 * i, 16 * j, 0);
					break;
			}
		}
	}
}