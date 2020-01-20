#include "player.h"
#include "sock_client_framework.h"

void sendPlayerStatus(const char* header, const player uPlayer) {
	json_t* pHeader = json_array();
	json_t* pData = json_array();


	json_array_append_new(pHeader, json_string(header));
	json_array_append_new(pData, json_string(uPlayer.cName));

	json_array_append_new(pData, json_integer(uPlayer.iAction_type));
	json_array_append_new(pData, json_integer(uPlayer.iPlayer_direction));
	json_array_append_new(pData, json_integer(uPlayer.iAction_idx));
	
	json_array_append_new(pData, json_integer(uPlayer.iPos_x));
	json_array_append_new(pData, json_integer(uPlayer.iPos_y));
	
	json_array_append_new(pData, json_integer(uPlayer.iHp));
	json_array_append_new(pData, json_integer(uPlayer.iArmor));
	json_array_append_new(pData, json_integer(uPlayer.iBuf));
	
	
	json_t* pMessage = htonJson(pHeader, pData);

	sendMessage(pMessage);
}

void movement_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_idx) {
	int sx = character_movement[action_type][action_idx][0];
	int sy = character_movement[action_type][action_idx][1];
	int sw = character_movement[action_type][action_idx][2];
	int sh = character_movement[action_type][action_idx][3];

	//al_draw_bitmap_region(bitmap, 8+sx, 36+sy, sw, sh, dx, dy, 0);
	//al_draw_filled_rounded_rectangle(dx,dy,dx+16,dy+32,0,0,al_map_rgb(255,0,0));

	int iFlag = action_type == CHARACTER_RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0;
	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, iFlag);
}
void draw_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_idx) {
	int sx = character_movement[action_type][action_idx][0] * 16;
	int sy = character_movement[action_type][action_idx][1] * 16;
	int sw = character_movement[action_type][action_idx][2] * 16;
	int sh = character_movement[action_type][action_idx][3] * 20;

	//al_draw_bitmap_region(bitmap, 8+sx, 36+sy, sw, sh, dx, dy, 0);
	//al_draw_filled_rounded_rectangle(dx,dy,dx+16,dy+32,0,0,al_map_rgb(255,0,0));

	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, 8 + sx, 36 + sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
}
void attack_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_idx) {
    int sx = character_attack[action_type][action_idx][0] * 32;
	int sy = 128 + character_attack[action_type][action_idx][1] * 32;
	int sw = character_attack[action_type][action_idx][2] * 32;
	int sh = character_attack[action_type][action_idx][3] * 16;

	al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, 0);
	//al_draw_filled_rounded_rectangle(dx, dy, dx + 16, dy + 32, 0, 0, al_map_rgb(0, 0, 255));

	//ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	//al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
}

void show_hit_effect(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_idx) {
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
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, 0.7, 0.7, 0, 0);

}