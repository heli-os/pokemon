#include "player.h"
#include "sock_client_framework.h"

// 플레이어 정보를 전송하는 함수
// jansson 라이브러리를 이용하여 JSON으로 제작하여 전송한다.
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


	json_t* pMessage = htonJson(pHeader, pData);

	sendMessage(pMessage);
}

// 플레이어 움직임에 대한 출력
void movement_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_mode, int action_idx) {
	int sx = character_movement[action_type][action_idx * action_mode][0];
	int sy = character_movement[action_type][action_idx * action_mode][1];
	int sw = character_movement[action_type][action_idx * action_mode][2];
	int sh = character_movement[action_type][action_idx * action_mode][3];


	//al_draw_bitmap_region(bitmap, 8+sx, 36+sy, sw, sh, dx, dy, 0);
	//al_draw_filled_rounded_rectangle(dx,dy,dx+16,dy+32,0,0,al_map_rgb(255,0,0));

	int iFlag = action_type == CHARACTER_RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0;
	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);

	// character_movement keyset에 정의된 값을 바탕으로 플레이어 출력
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, iFlag);
}

// 플레이어 출력
void draw_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_idx) {
	int sx = character_movement[action_type][action_idx][0] * 16;
	int sy = character_movement[action_type][action_idx][1] * 16;
	int sw = character_movement[action_type][action_idx][2] * 16;
	int sh = character_movement[action_type][action_idx][3] * 20;

	//al_draw_bitmap_region(bitmap, 8+sx, 36+sy, sw, sh, dx, dy, 0);
	//al_draw_filled_rounded_rectangle(dx,dy,dx+16,dy+32,0,0,al_map_rgb(255,0,0));

	ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);
	// character_movement keyset에 정의된 값을 바탕으로 플레이어 출력
	al_draw_tinted_scaled_rotated_bitmap_region(bitmap, 8 + sx, 36 + sy, sw, sh, tint, 0, 0, dx, dy, GAME_SCALE, GAME_SCALE, 0, 0);
}