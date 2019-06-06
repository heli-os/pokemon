#include "player.h"

void movement_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx) {
	int sx = character_movement[action_type][action_idx][0] * 16;
	int sy = character_movement[action_type][action_idx][1] * 16;
	int sw = character_movement[action_type][action_idx][2] * 16;
	int sh = character_movement[action_type][action_idx][3] * 16;

	al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);

}

void attack_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx) {
      	int sx = character_attack[action_type][action_idx][0] * 32;
	int sy = 128 + character_attack[action_type][action_idx][1] * 32;
	int sw = character_attack[action_type][action_idx][2] * 32;
	int sh = character_attack[action_type][action_idx][3] * 16;

	al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);
}