#include "nginx_framework.h"
#include "player.h"
#include "map.h"
#include <stdio.h>

enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};
enum key_type {
	ARROW_KEY,
	SPACE_KEY
};
PLAYER_STATUS user_player = { NULL, 0,0,0,0.0,0.0 };
void update()
{
	if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
		quit();

	if (user_player.action_type==0 &&(is_key_down(ALLEGRO_KEY_DOWN) || is_key_down(ALLEGRO_KEY_RIGHT) || is_key_down(ALLEGRO_KEY_UP) || is_key_down(ALLEGRO_KEY_LEFT)))
	{
		user_player.action_type = 0;
		user_player.action_idx = user_player.action_idx >= 3 ? 0 : user_player.action_idx + 1;
	}

	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_DOWN))  { user_player.pos_y += 1; user_player.player_direction = CHARACTER_DOWN; }
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_RIGHT)) { user_player.pos_x += 1; user_player.player_direction = CHARACTER_RIGHT;}
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_UP))	{ user_player.pos_y -= 1; user_player.player_direction = CHARACTER_UP;	 }
	if (user_player.action_type == 0 && is_key_down(ALLEGRO_KEY_LEFT))  { user_player.pos_x -= 1; user_player.player_direction = CHARACTER_LEFT; }


	if (is_key_pressed(ALLEGRO_KEY_SPACE)) {user_player.action_idx = 0; user_player.action_type = 1;}
		
	if (is_key_released(ALLEGRO_KEY_DOWN) || is_key_released(ALLEGRO_KEY_RIGHT) || is_key_released(ALLEGRO_KEY_UP) || is_key_released(ALLEGRO_KEY_LEFT))
		user_player.action_idx = 0;

	if (is_key_released(ALLEGRO_KEY_SPACE)) { user_player.action_type = 0; user_player.action_idx = 0; }
}


void render()
{	
	printf("%d, %d :: x:%f, y:%f :: action_type:%d\n", user_player.player_direction, user_player.action_idx,user_player.pos_x,user_player.pos_y,user_player.action_type);
	ALLEGRO_BITMAP* _map = al_load_bitmap("gfx/Overworld.png");
	init_map(_map);
	al_destroy_bitmap(_map);
	switch(user_player.action_type) {
		case 0:
			movement_character(user_player.player, user_player.pos_x, user_player.pos_y, user_player.player_direction, user_player.action_idx);
			break;
		case 1:
			attack_character(user_player.player, user_player.pos_x, user_player.pos_y, user_player.player_direction, user_player.action_idx);
			user_player.action_idx += 1;
			if (user_player.action_idx >= 3) { user_player.action_type = 0;  user_player.action_idx = 0; }
			break;
		default:
			break;
	}
	
	//al_rest(1.0/GAME_FPS);

}
int main(int argc, char* argv[])
{
	
	// must be called first!
	init_framework("nginx_test_ync", 800, 600, false);	

	user_player.player = al_load_bitmap("gfx/character.png");

	
	// the game loop runs until we call quit()
	run_game_loop(update, render);
	
	return 0;
}