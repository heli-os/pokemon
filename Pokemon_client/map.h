#ifndef _POKEMON_MAP_HEADER_
#define _POKEMON_MAP_HEADER_
#include "nginx_common.h"

void init_terrain(ALLEGRO_BITMAP* bitmap);

// bitmap array index
// start_x(from Screen), start_y(from Screen),
// start_x(from sprite), start_y(from sprite),
// object_width(from sprite), object_height(from srpite)
// start_position_x(from Screen), start_position_y(from Screen)
static int mapOffset[][9] = {
	{0,500,500,5,5,176,148,144,32},		// 집 2층
	{0,500,500,186,5,176,148,144,32},	// 집 1층(1)
	{1,500,500,0,0,384,735,240,396},	// 마을(1)
	{0,500,500,186,5,176,148,48,128},	// 집 1층(2)
	{0,500,500,218,178,208,212,96,192},	// 오박사 연구실
	{1,500,500,0,0,384,735,256,492},	// 마을(2)
	{2,500,500,0,0,240,251,112,227},	// 체육관
	{1,500,500,0,0,384,735,96,364}		// 마을(3)
};

ALLEGRO_BITMAP* world_map;
#endif