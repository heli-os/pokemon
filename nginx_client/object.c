#include "object.h"

object_info create_object(ALLEGRO_BITMAP* bitmap, int type, float dx, float dy) {
	float sx=0.0f, sy = 0.0f,sw = 0.0f,sh = 0.0f;
	switch (type) {
	case FOUNTAIN_1:
		sx = 352; sy = 144; sw = 48, sh = 48;
		break;
	case FOUNTAIN_2:
		sx = 400; sy = 144; sw = 48, sh = 48;
		break;
	case FOUNTAIN_3:
		sx = 448; sy = 144; sw = 48, sh = 48;
		break;
	case CASTLE_1:
		sx = 0; sy = 336; sw = 48, sh = 120;
		break;
	case HOUSE_1:
		sx = 96; sy = 0; sw = 80, sh = 80;
		break;
	case HOUSE_2:
		sx = 176; sy = 0; sw = 80, sh = 80;
		break;
	}

	object_info obj = { dx,dy,sw,sh};
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, al_map_rgb(255, 255, 255), 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
	return obj;
}