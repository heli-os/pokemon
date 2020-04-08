#ifndef _NGINX_COMMON_HEADER_
#define _NGINX_COMMON_HEADER_
//==============================================================================
// Includes.
//==============================================================================
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <jansson.h>

#define GAME_ENV_DEVELOPMENT 0
#define GAME_ENV_PRODUCTION  1 

#define GAME_MODE GAME_ENV_PRODUCTION

#define GAME_WIDTH 800
#define GAME_HEIGHT 640

#define GAME_FPS 60
#define GAME_SCALE 4
#define GAME_MOVE_TICK 1

#define GAME_MAP_WIDTH 550*GAME_SCALE
#define GAME_MAP_HEIGHT 800*GAME_SCALE


extern int GAME_SPEED;
extern int GAME_STAGE;

/*
#define CHARACTER_DOWN 1
#define CHARACTER_RIGHT 1
#define CHARACTER_UP -1
#define CHARACTER_LEFT -1
*/
enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};

void render();


#endif