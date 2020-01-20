#ifndef _NGINX_SCREEN_HEADER_
#define _NGINX_SCREEN_HEADER_
#include "nginx_common.h"
float camera_get_position(char type, float type_pos, int player_idx);

void transformScreen();
#endif