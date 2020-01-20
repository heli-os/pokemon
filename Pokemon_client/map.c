#include "map.h"
//#include "player.h"

//캐릭터는 스크린 중앙에 고정.
//맵은 캐릭터의 움직임에 따라 scroll transform
void init_terrain(ALLEGRO_BITMAP* bitmap) {
	
	al_set_target_bitmap(world_map);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	int screenWidth  = al_get_display_width(al_get_current_display());
	int screenHeight = al_get_display_height(al_get_current_display());

	printf("map.c->init_terrain->GAME_STAGE::%d\n", GAME_STAGE);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, mapOffset[GAME_STAGE][3],mapOffset[GAME_STAGE][4], mapOffset[GAME_STAGE][5], mapOffset[GAME_STAGE][6], al_map_rgb(255, 255, 255), 0, 0, /*screenWidth/2-88*GAME_SCALE*/500, /*screenHeight / 2 - 72 * GAME_SCALE*/500, GAME_SCALE, GAME_SCALE, 0, 0);

	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}
