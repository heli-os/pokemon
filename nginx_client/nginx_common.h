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


#define GAME_WIDTH 800
#define GAME_HEIGHT 600

#define GAME_MAP_WIDTH 1200
#define GAME_MAP_HEIGHT 960


#define GAME_FPS 40
#define GAME_SCALE 1
#define GAME_MOVE_TICK 2

enum character_movement {
	CHARACTER_DOWN,
	CHARACTER_RIGHT,
	CHARACTER_UP,
	CHARACTER_LEFT
};


#endif