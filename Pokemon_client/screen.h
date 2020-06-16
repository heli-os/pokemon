#ifndef _POKEMON_CAMERA_HEADER_
#define _POKEMON_CAMERA_HEADER_
#include "nginx_common.h"
#include "map.h"
#include "player.h"

/// <summary>
/// position에 대한 
/// </summary>
/// <param name="type"></param>
/// <param name="type_pos"></param>
/// <param name="player_idx"></param>
/// <returns>카메라 포지션을 반환</returns>
float camera_get_position(char type, float type_pos, int player_idx);

/// <summary>
/// 화면이 밝게 전환되는 효과
/// </summary>
/// <param name="seconds"></param>
void fadeOut(double seconds);

/// <summary>
/// 화면이 어둡게 전환되는 효과
/// </summary>
/// <param name="seconds"></param>
void fadeIn(double seconds);

extern float camera_position_x;
extern float camera_position_y;
extern ALLEGRO_TRANSFORM camera;

/// <summary>
/// 플레이어 좌표에 기반하여 화면 위치를 갱신하는 함수
/// </summary>
/// <param name="_player"></param>
void updateCamera(player _player);
#endif