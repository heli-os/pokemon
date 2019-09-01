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


player_status user_player = { NULL, NULL,"", 0,0,0,false,0,0,100,0,0 };
// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y, hp, armor, buf
ALLEGRO_BITMAP* _map = NULL;
ALLEGRO_BITMAP* _object = NULL;
ALLEGRO_TRANSFORM camera;
extern ALLEGRO_BITMAP* world_map;

extern object_info object_list[OBJECT_COUNT];

extern ALLEGRO_USTR* chatInput;
extern bool onChat;

extern int GAME_SPEED;

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

	if (user_player.bMoveFlag == false && is_key_down(ALLEGRO_KEY_DOWN)) {
		user_player.bMoveFlag = true;
		user_player.iAction_type = 1;
		user_player.iPlayer_direction = CHARACTER_DOWN;
	}
	if (user_player.bMoveFlag == false && is_key_down(ALLEGRO_KEY_RIGHT)) {
		user_player.bMoveFlag = true;
		user_player.iAction_type = 1;
		user_player.iPlayer_direction = CHARACTER_RIGHT;
	}
	if (user_player.bMoveFlag == false && is_key_down(ALLEGRO_KEY_UP)) {
		user_player.bMoveFlag = true;
		user_player.iAction_type = 1;
		user_player.iPlayer_direction = CHARACTER_UP;
	}
	if (user_player.bMoveFlag == false && is_key_down(ALLEGRO_KEY_LEFT)) {
		user_player.bMoveFlag = true;
		user_player.iAction_type = 1;
		user_player.iPlayer_direction = CHARACTER_LEFT;
	}
	/*
	if (is_key_down(ALLEGRO_KEY_SPACE)) {
		GAME_SPEED = 4;
	}

	if (is_key_released(ALLEGRO_KEY_SPACE)) {
		GAME_SPEED = 1;
	}
	*/
	if (user_player.bMoveFlag) {
		user_player.iAction_idx++;
		switch (user_player.iPlayer_direction)
		{
		case CHARACTER_DOWN:
			user_player.iPos_y += GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_y -= GAME_MOVE_TICK * GAME_SCALE;
			break;
		case CHARACTER_RIGHT:
			user_player.iPos_x += GAME_MOVE_TICK * GAME_SCALE;
			if(isCollision(user_player))
				user_player.iPos_x -= GAME_MOVE_TICK * GAME_SCALE;
				break;
		case CHARACTER_UP:
			user_player.iPos_y -= GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_y += GAME_MOVE_TICK * GAME_SCALE;
			break;
		case CHARACTER_LEFT:
			user_player.iPos_x -= GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_x += GAME_MOVE_TICK * GAME_SCALE;
			break;

		}
		if (user_player.iAction_idx >= 16)
		{
			user_player.iAction_type = 0;
			user_player.iAction_idx = 0;
			user_player.bMoveFlag = false;
		}
	}
	
	
	//isCollision(user_player);

	
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
	
	showChat(camera_position_x, camera_position_y + (GAME_HEIGHT - 120));
	
	
	if (user_player.iHp <= 0)
		sendPlayerStatus("EXIT", user_player);
	else
		sendPlayerStatus("PLAYER", user_player);
}

int move_tick = 0;
void render()
{
	
	al_draw_bitmap(world_map, 0, 0, 0);
	switch (user_player.iAction_type)
	{
	case 0:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
		break;
	case 1:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_idx / 8);
		break;
	}
	
	//al_rest(1.0 / GAME_FPS);
}

void a() {
	for (int i = 0; i < 10; i++) {
		int c = 0;
		int* a = &c;
		printf("%d\n", *a);
	}
}
void b() {}

void abc(void (*test)()) {
	while (1) {
		test();
	}
}

int main(int argc, char* argv[])
{
	//gets_s(user_player.cName, sizeof(user_player.cName));
	//strcpy_s(user_player.cName, sizeof(user_player.cName), "TEST_NICK");
	bind_sock_clnt();

	// must be called first!l
	init_framework("OverWorld", GAME_WIDTH, GAME_HEIGHT, false);

	_map = al_load_bitmap("gfx/Pallet_Town_Interiors.png");
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);

	init_terrain(_map);

	initCollision();

	//_object = al_load_bitmap("gfx/objects.png");

	user_player._player = al_load_bitmap("gfx/Hero&Heroine.png");
	al_convert_mask_to_alpha(user_player._player, al_map_rgb(255, 200, 106));
	//user_player._hit_efftect = al_load_bitmap("gfx/hit_effect.png");
	user_player.iPos_x = 500 + 16*5*GAME_SCALE;
	user_player.iPos_y = 500 + 16*6*GAME_SCALE-16;

	sendPlayerStatus("JOIN_GAME", user_player);
	
	// the game loop runs until we call quit()
	run_game_loop(update, render);
	return 0;
}