#include "nginx_framework.h"
#include "player.h"
#include "map.h"
#include "object.h"
#include "cameara.h"
#include <stdio.h>

enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};
PLAYER_STATUS user_player = { NULL, NULL, 0,0,0,0.0,0.0 };

ALLEGRO_BITMAP* _map = NULL;
ALLEGRO_BITMAP* _object = NULL;
ALLEGRO_TRANSFORM camera;
extern ALLEGRO_BITMAP* world_map;

object_info fountain_1;
object_info castle_1;
object_info house_1;
object_info house_2;

void update()
{
	if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
		quit();

	if (user_player.action_type==0 &&(is_key_down(ALLEGRO_KEY_DOWN) || is_key_down(ALLEGRO_KEY_RIGHT) || is_key_down(ALLEGRO_KEY_UP) || is_key_down(ALLEGRO_KEY_LEFT)))
	{
		user_player.action_type = 0;
		user_player.action_idx = user_player.action_idx >= 3 ? 0 : user_player.action_idx + 1;
	}

	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_DOWN))  { user_player.pos_y += GAME_MOVE_TICK; user_player.player_direction = CHARACTER_DOWN; }
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_RIGHT)) { user_player.pos_x += GAME_MOVE_TICK; user_player.player_direction = CHARACTER_RIGHT;}
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_UP))	{ user_player.pos_y -= GAME_MOVE_TICK; user_player.player_direction = CHARACTER_UP;	 }
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_LEFT))  { user_player.pos_x -= GAME_MOVE_TICK; user_player.player_direction = CHARACTER_LEFT; }

	if (user_player.pos_x < 0)user_player.pos_x = 0;
	if (user_player.pos_x >= GAME_MAP_WIDTH-32) user_player.pos_x = GAME_MAP_WIDTH - 32;
	if (user_player.pos_y < 0) user_player.pos_y = 0;
	if (user_player.pos_y >= GAME_MAP_HEIGHT-64) user_player.pos_y = GAME_MAP_HEIGHT - 64;



	if (is_key_pressed(ALLEGRO_KEY_SPACE)) {user_player.action_idx = 0; user_player.action_type = 1;}
		
	if (is_key_released(ALLEGRO_KEY_DOWN) || is_key_released(ALLEGRO_KEY_RIGHT) || is_key_released(ALLEGRO_KEY_UP) || is_key_released(ALLEGRO_KEY_LEFT))
		user_player.action_idx = 0;

	//if (is_key_released(ALLEGRO_KEY_SPACE)) { user_player.action_type = 0; user_player.action_idx = 0; }

	float camera_position_x = camera_get_position('x',user_player.pos_x, 16);
	float camera_position_y = camera_get_position('y',user_player.pos_y, 32);
	al_identity_transform(&camera);
	al_translate_transform(&camera, -camera_position_x, -camera_position_y);
	al_use_transform(&camera);
}


void render()
{
	al_draw_bitmap(world_map, 0, 0, 0);

	printf("%d, %d :: x:%f, y:%f :: action_type:%d\n", user_player.player_direction, user_player.action_idx,user_player.pos_x,user_player.pos_y,user_player.action_type);
	
	fountain_1 = create_object(_map, FOUNTAIN_1, 400, 400);
	castle_1 = create_object(_map, CASTLE_1, 200, 0);
	house_1 = create_object(_map, HOUSE_1, 600, 300);
	house_2 = create_object(_map, HOUSE_2, 760, 300);

	
	
	switch(user_player.action_type) {
		case 0:
			movement_character(user_player.player, user_player.pos_x, user_player.pos_y, user_player.player_direction, user_player.action_idx);
			break;
		case 1:
			attack_character(user_player.player, user_player.pos_x, user_player.pos_y, user_player.player_direction, user_player.action_idx);
			user_player.action_idx += 1;
			if (user_player.action_idx >= 3) { user_player.action_type = 2; user_player.action_idx = 0;}
			break;
		case 2:
			movement_character(user_player.player, user_player.pos_x, user_player.pos_y, user_player.player_direction, user_player.action_idx);
			show_hit_effect(user_player.hit_efftect, user_player.pos_x, user_player.pos_y,user_player.player_direction, user_player.action_idx);
			user_player.action_idx += 1;
			if (user_player.action_idx >= 3) { user_player.action_type = 0; user_player.action_idx = 0;	}

		default:
			break;
	}
	//al_rest(1.0 / GAME_FPS);
}

int main(int argc, char* argv[])
{
	
	// must be called first!l
	init_framework("OverWorld", GAME_WIDTH, GAME_HEIGHT, false);
	
	_map = al_load_bitmap("gfx/Overworld.png");
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);
	init_map(_map);
	
	_object = al_load_bitmap("gfx/objects.png");

	user_player.player = al_load_bitmap("gfx/character.png");
	user_player.hit_efftect = al_load_bitmap("gfx/hit_effect.png");
	user_player.pos_x = al_get_display_width(al_get_current_display()) / 2 -8;
	user_player.pos_y = al_get_display_height(al_get_current_display()) /2 -16;

	
	// the game loop runs until we call quit()
	run_game_loop(update,render);
	
	return 0;
}