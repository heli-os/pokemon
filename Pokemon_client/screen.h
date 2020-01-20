#ifndef _NGINX_CAMERA_HEADER_
#define _NGINX_CAMERA_HEADER_
#include "nginx_common.h"
#include "map.h"
#include "player.h"
float camera_get_position(char type, float type_pos, int player_idx);
void fadeOut();
void fadeIn();
extern float camera_position_x;
extern float camera_position_y;
extern ALLEGRO_TRANSFORM camera;
void updateCamera(player _player);
#endif