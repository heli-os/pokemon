#include "map.h"


//캐릭터는 스크린 중앙에 고정.
//맵은 캐릭터의 움직임에 따라 scroll transform

// init map tile
void init_tile() {
	int idx = 0;
	int i, j;
	for (i = 0; i < 36; i++)
	{
		for (j = 0; j < 40; j++)
		{
			map_tile[idx].posX = 16 * j;
			map_tile[idx].posY = 16 * i;
			idx++;
		}
	}
}

void init_terrain(ALLEGRO_BITMAP* bitmap) {
	al_set_target_bitmap(world_map);

	//memset(map_tile, 0, sizeof(map_tile));
	int layer, i, j;
	for (layer = 0; layer<2; layer++)
	{
		for (i = 0; i < 60; i++) {
			for (j = 0; j < 75; j++) {
				int tile_idx = word_map[layer][i][j]-1;
				if (tile_idx != -1)
					//al_draw_tinted_scaled_rotated_bitmap_region(bitmap, map_tile[tile_idx].posX, map_tile[tile_idx].posY, 16, 16, al_map_rgb(255, 255, 255), 0, 0, 16*j, 16*i, GAME_SCALE, GAME_SCALE, 0, 0);
					al_draw_bitmap_region(bitmap, map_tile[tile_idx].posX, map_tile[tile_idx].posY, 16, 16, 16 * j, 16 * i, 0);

			}
		}
	}
	printf("BITMAP_SAVE..:%s\n", al_save_bitmap("a.png", world_map)?"true":"false");
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}