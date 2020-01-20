#ifndef _NGINX_MAP_HEADER_
#define _NGINX_MAP_HEADER_
#include "nginx_common.h"

void init_terrain(ALLEGRO_BITMAP* bitmap);

// bitmap array index
// start_x(from Screen), start_y(from Screen),
// start_x(from sprite), start_y(from sprite),
// object_width(from sprite), object_height(from srpite)
// start_position_x(from Screen), start_position_y(from Screen)
static int mapOffset[][9] = {
	{0,500,500,5,5,176,148,144,32},
	{0,500,500,186,5,176,148,144,32},
	{1,500,500,0,0,384,735,240,396},
//{1,500,500,0,0,384,735,100,100},
	{0,500,500,186,5,176,148,48,128},
	{0,500,500,218,178,208,212,96,192},
	{1,500,500,0,0,384,735,256,492},
};



ALLEGRO_BITMAP* world_map;
#endif