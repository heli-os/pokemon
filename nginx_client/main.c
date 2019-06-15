#include "nginx_framework.h"
#include "player.h"
#include "map.h"
#include "object.h"
#include "cameara.h"
#include "sock_client_framework.h"
#include "collision.h"
#include <stdio.h>

#include <time.h>


enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};

player_status user_player = { NULL, NULL,NULL, 0,0,0,0.0,0.0,100,0,0 };
// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y, hp, armor, buf
ALLEGRO_BITMAP* _map = NULL;
ALLEGRO_BITMAP* _object = NULL;
ALLEGRO_TRANSFORM camera;
extern ALLEGRO_BITMAP* world_map;

extern object_info object_list[OBJECT_COUNT];

void update()
{

	sendMessage("TEST_MESSAGE");
	if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
		quit();

	if (user_player.iAction_type==0 &&(is_key_down(ALLEGRO_KEY_DOWN) || is_key_down(ALLEGRO_KEY_RIGHT) || is_key_down(ALLEGRO_KEY_UP) || is_key_down(ALLEGRO_KEY_LEFT)))
	{
		user_player.iAction_type = 0;
		user_player.iAction_idx = user_player.iAction_idx >= 3 ? 0 : user_player.iAction_idx + 1;
	}

	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_DOWN)) {
		user_player.fPos_y += GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_DOWN; 
		if (isCollision(user_player)) 
			user_player.fPos_y -= GAME_MOVE_TICK; 
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_RIGHT)) {
		user_player.fPos_x += GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_RIGHT;
		if (isCollision(user_player)) 
			user_player.fPos_x -= GAME_MOVE_TICK;
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_UP))	{
		user_player.fPos_y -= GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_UP;
		if (isCollision(user_player)) 
			user_player.fPos_y += GAME_MOVE_TICK;
	}
	if (user_player.iAction_type == 0 && is_key_down(ALLEGRO_KEY_LEFT))  {
		user_player.fPos_x -= GAME_MOVE_TICK; user_player.iPlayer_direction = CHARACTER_LEFT;
		if (isCollision(user_player)) 
			user_player.fPos_x += GAME_MOVE_TICK;
	}

	if (user_player.fPos_x < 0)user_player.fPos_x = 0;
	if (user_player.fPos_x >= GAME_MAP_WIDTH- PLAYER_WIDTH*GAME_SCALE) user_player.fPos_x = GAME_MAP_WIDTH - PLAYER_WIDTH * GAME_SCALE;
	if (user_player.fPos_y < 0) user_player.fPos_y = 0;
	if (user_player.fPos_y >= GAME_MAP_HEIGHT- PLAYER_HEIGHT * GAME_SCALE) user_player.fPos_y = GAME_MAP_HEIGHT - PLAYER_HEIGHT * GAME_SCALE;



	if (is_key_pressed(ALLEGRO_KEY_Z)) {user_player.iAction_idx = 0; user_player.iAction_type = 1;}
		
	if (is_key_released(ALLEGRO_KEY_DOWN) || is_key_released(ALLEGRO_KEY_RIGHT) || is_key_released(ALLEGRO_KEY_UP) || is_key_released(ALLEGRO_KEY_LEFT))
		user_player.iAction_idx = 0;

	//if (is_key_released(ALLEGRO_KEY_SPACE)) { user_player.iAction_type = 0; user_player.iAction_idx = 0; }

	

	float camera_position_x = camera_get_position('x',user_player.fPos_x, 16);
	float camera_position_y = camera_get_position('y',user_player.fPos_y, 32);
	al_identity_transform(&camera);
	al_translate_transform(&camera, -camera_position_x, -camera_position_y);
	al_use_transform(&camera);
}


void render()
{
	al_draw_bitmap(world_map, 0, 0, 0);

	//printf("%d, %d :: x:%f, y:%f :: action_type:%d\n", user_player.iPlayer_direction, user_player.iAction_idx,user_player.fPos_x,user_player.fPos_y,user_player.iAction_type);
	
	object_list[0] = create_object(_map, FOUNTAIN_1, 400, 400);
	object_list[1] = create_object(_map, FOUNTAIN_1, 400, 400);
	object_list[2] = create_object(_map, CASTLE_1, 200, 0);
	object_list[3] = create_object(_map, HOUSE_1, 600, 300);
	object_list[4] = create_object(_map, HOUSE_2, 760, 300);

	
	
	switch(user_player.iAction_type) {
		case 0:
			movement_character(user_player._player, user_player.fPos_x, user_player.fPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
			break;
		case 1:
			attack_character(user_player._player, user_player.fPos_x, user_player.fPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
			user_player.iAction_idx += 1;
			if (user_player.iAction_idx >= 3) { user_player.iAction_type = 2; user_player.iAction_idx = 0;}
			break;
		case 2:
			movement_character(user_player._player, user_player.fPos_x, user_player.fPos_y, user_player.iPlayer_direction, user_player.iAction_idx);
			show_hit_effect(user_player._hit_efftect, user_player.fPos_x, user_player.fPos_y,user_player.iPlayer_direction, user_player.iAction_idx);
			user_player.iAction_idx += 1;
			if (user_player.iAction_idx >= 3) { user_player.iAction_type = 0; user_player.iAction_idx = 0;	}

		default:
			break;
	}
	//al_rest(1.0 / GAME_FPS);
}

int main(int argc, char* argv[])
{

	bind_sock_clnt();
	// must be called first!l
	init_framework("OverWorld", GAME_WIDTH, GAME_HEIGHT, false);
	
	_map = al_load_bitmap("gfx/Overworld.png");
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);
	init_map(_map);	
	
	_object = al_load_bitmap("gfx/objects.png");

	user_player._player = al_load_bitmap("gfx/character.png");
	user_player._hit_efftect = al_load_bitmap("gfx/hit_effect.png");
	user_player.fPos_x = al_get_display_width(al_get_current_display()) / 2 -8;
	user_player.fPos_y = al_get_display_height(al_get_current_display()) /2 -16;

	
	// the game loop runs until we call quit()
	run_game_loop(update,render);
	
	return 0;
}