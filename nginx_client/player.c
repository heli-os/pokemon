#include "player.h"

void movement_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx) {
	int sx = character_movement[action_type][action_idx][0] * 16;
	int sy = character_movement[action_type][action_idx][1] * 16;
	int sw = character_movement[action_type][action_idx][2] * 16;
	int sh = character_movement[action_type][action_idx][3] * 16;

	//al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);
	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
}

void attack_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx) {
    int sx = character_attack[action_type][action_idx][0] * 32;
	int sy = 128 + character_attack[action_type][action_idx][1] * 32;
	int sw = character_attack[action_type][action_idx][2] * 32;
	int sh = character_attack[action_type][action_idx][3] * 16;

	//al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);
	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
}

void show_hit_effect(ALLEGRO_BITMAP* bitmap, float dx, float dy, int player_direction,int action_idx) {
	int sx = character_hit_effect[action_idx][0] * 64;
	int sy = character_hit_effect[action_idx][1] * 64;
	int sw = character_hit_effect[action_idx][2] * 64;
	int sh = character_hit_effect[action_idx][3] * 64;
	/*
	float tmp_x = 0.0f;
	float tmp_y = 0.0f;
	switch (player_direction) {
	case 0: // CHARACTER_DOWN
		tmp_y = 30.0f;
		break;
	case 1: // CHARACTER_RIGHT
		tmp_x = 30.0f;
		break;
	case 2: // CHARACTER_UP
		tmp_y = -30.0f;
		break;
	case 3: // CHARACTER_LEFT
		tmp_x = -30.0f;
		break;
		
	}
	*/
	//al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);
	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, 1, 1, 0, 0);

}