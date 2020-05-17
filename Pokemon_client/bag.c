#include "bag.h"

extern float camera_position_x;
extern float camera_position_y;

void drawBagUI() {
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, 0, 0, 240, 160, al_map_rgb(255, 255, 255), 0, 0, camera_position_x, camera_position_y, 3.3333333, GAME_SCALE, 0, 0);
}