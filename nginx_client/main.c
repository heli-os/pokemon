#include "nginx_framework.h"
#include "player.h"
#include "map.h"
#include "object.h"
#include "cameara.h"
#include "sock_client_framework.h"
#include "collision.h"
#include "chat.h"
#include <stdio.h>

#include <time.h>

enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};

player_status user_player = { NULL, NULL,"", 0,0,0,0.0,0.0,100,0,0 };
// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y, hp, armor, buf
ALLEGRO_BITMAP* _map = NULL;
ALLEGRO_BITMAP* _object = NULL;
ALLEGRO_TRANSFORM camera;
extern ALLEGRO_BITMAP* world_map;

extern object_info object_list[OBJECT_COUNT];

extern ALLEGRO_USTR* chatInput;
extern bool onChat;


void update()
{
	/*
	time_t c_time;
	time(&c_time);
	char buf[256];
	ctime_s(buf, sizeof(buf), &c_time);
	sendMessage(buf);
	*/
	if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
		quit();

	if (user_player.iAction_type == 0 && (is_key_down(ALLEGRO_KEY_DOWN) || is_key_down(ALLEGRO_KEY_RIGHT) || is_key_down(ALLEGRO_KEY_UP) || is_key_down(ALLEGRO_KEY_LEFT)))
	{
		user_player.iAction_type = 0;
		user_player.iAction_idx = user_player.iAction_idx >= 3 ? 0 : user_player.iAction_idx + 1;
	}

	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_DOWN)) {
		user_player.iPos_y += GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_DOWN;
		if (isCollision(user_player))
			user_player.iPos_y -= GAME_MOVE_TICK;
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_RIGHT)) {
		user_player.iPos_x += GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_RIGHT;
		if (isCollision(user_player))
			user_player.iPos_x -= GAME_MOVE_TICK;
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_UP)) {
		user_player.iPos_y -= GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_UP;
		if (isCollision(user_player))
			user_player.iPos_y += GAME_MOVE_TICK;
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_LEFT)) {
		user_player.iPos_x -= GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_LEFT;
		if (isCollision(user_player))
			user_player.iPos_x += GAME_MOVE_TICK;
	}

	if (user_player.iPos_x < 0)user_player.iPos_x = 0;
	if (user_player.iPos_x >= GAME_MAP_WIDTH - PLAYER_WIDTH * GAME_SCALE) user_player.iPos_x = GAME_MAP_WIDTH - PLAYER_WIDTH * GAME_SCALE;
	if (user_player.iPos_y < 0) user_player.iPos_y = 0;	
	if (user_player.iPos_y >= GAME_MAP_HEIGHT - PLAYER_HEIGHT * GAME_SCALE) user_player.iPos_y = GAME_MAP_HEIGHT - PLAYER_HEIGHT * GAME_SCALE;


	if (!onChat)
	{
		if (is_key_pressed(ALLEGRO_KEY_Z)) { user_player.iAction_idx = 0; user_player.iAction_type = 1; }
	}

	if (is_key_released(ALLEGRO_KEY_DOWN) || is_key_released(ALLEGRO_KEY_RIGHT) || is_key_released(ALLEGRO_KEY_UP) || is_key_released(ALLEGRO_KEY_LEFT))
		user_player.iAction_idx = 0;

	//if (is_key_released(ALLEGRO_KEY_SPACE)) { user_player.iAction_type = 0; user_player.iAction_idx = 0; }



	float camera_position_x = camera_get_position('x', user_player.iPos_x, 16);
	float camera_position_y = camera_get_position('y', user_player.iPos_y, 32);
	al_identity_transform(&camera);
	al_translate_transform(&camera, -camera_position_x, -camera_position_y);
	al_use_transform(&camera);

	if (is_key_pressed(ALLEGRO_KEY_ENTER)) 
	{
		if (onChat && chatInput->slen > 0)
		{
			const char* txt = al_cstr(chatInput);
			json_t* pHeader = json_array();
			json_t* pData = json_array();
			json_array_append_new(pHeader, json_string("CHAT"));
			json_array_append_new(pData, json_string(user_player.cName));
			json_array_append_new(pData, json_string(txt));
			
			json_t* pMessage = htonJson(pHeader, pData);

			sendMessage(pMessage);
			chatInput = al_ustr_new("");
		}
		onChat = !onChat;
	}
	showChat(camera_position_x,camera_position_y);
}


void render()
{
	al_draw_bitmap(world_map, 0, 0, 0);




	switch (user_player.iAction_type) {
	case 0:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
		break;
	case 1:
		attack_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
		user_player.iAction_idx += 1;
		if (user_player.iAction_idx >= 3) { user_player.iAction_type = 2; user_player.iAction_idx = 0; }
		break;
	case 2:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
		show_hit_effect(user_player._hit_efftect, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
		user_player.iAction_idx += 1;
		if (user_player.iAction_idx >= 3) { user_player.iAction_type = 0; user_player.iAction_idx = 0; }

	default:
		break;
	}
	//al_rest(1.0 / GAME_FPS);
}

int main(int argc, char* argv[])
{
	//gets_s(user_player.cName, sizeof(user_player.cName));
	strcpy_s(user_player.cName, sizeof(user_player.cName), "TEST_NICK");
	bind_sock_clnt();
	// must be called first!l
	init_framework("OverWorld", GAME_WIDTH, GAME_HEIGHT, false);

	_map = al_load_bitmap("gfx/Overworld.png");
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);

	init_tile();
	init_terrain(_map);

	initCollision();

	//_object = al_load_bitmap("gfx/objects.png");

	user_player._player = al_load_bitmap("gfx/character.png");
	user_player._hit_efftect = al_load_bitmap("gfx/hit_effect.png");
	user_player.iPos_x = al_get_display_width(al_get_current_display()) / 2 - 8;
	user_player.iPos_y = al_get_display_height(al_get_current_display()) / 2 - 16;


	// the game loop runs until we call quit()
	run_game_loop(update, render);

	return 0;
}