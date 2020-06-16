#ifndef _POKEMON_PLAYER_HEADER_
#define _POKEMON_PLAYER_HEADER_

#include "nginx_common.h"

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 20

/*
플레이어 정보를 저장하는 구조체
	ALLEGRO_BITMAP* _player;
	char cName[12];

	int iAction_type;
	int iAction_mode;
	int iPlayer_direction;
	int iAction_idx;
	bool bMoveFlag;

	int iPos_x;
	int iPos_y;

	int iGold;
*/
typedef struct _player {
	ALLEGRO_BITMAP* _player;
	char cName[12];

	int iAction_type;
	int iAction_mode;
	int iPlayer_direction;
	int iAction_idx;
	bool bMoveFlag;

	int iPos_x;
	int iPos_y;

	int iGold;
} player;

// 플레이어 움직임에 대응하는 Bitmap Sprite Keyset
static int character_movement[8][3][4] = {
	{{24,36,16,20},{8,36,16,20},{40,36,16,20}}, // 하(1)
	{{24,100,16,20},{8,100,16,20},{40,100,16,20}}, // 우(1)
	{{24,68,16,20},{8,68,16,20},{40,68,16,20}}, // 상(1)
	{{24,100,16,20},{8,100,16,20},{40,100,16,20} },  // 좌(1)

	{{80,36,16,20},{64,36,16,20},{96,36,16,20}}, // 하(2)
	{{80,100,16,20},{64,100,16,20},{96,100,16,20}}, // 우(2)
	{{80,68,16,20},{64,68,16,20},{96,68,16,20}}, // 상(2)
	{{80,100,16,20},{64,100,16,20},{96,100,16,20} }  // 좌(2)

};

/// <summary>
/// 플레이어 정보(player 구조체)를 서버에 전송하는 함수
/// </summary>
/// <param name="header"></param>
/// <param name="uPlayer"></param>
void sendPlayerStatus(const char* header, const player uPlayer);

/// <summary>
/// 플레이어의 움직임 갱신하는 함수
/// </summary>
/// <param name="bitmap"></param>
/// <param name="dx"></param>
/// <param name="dy"></param>
/// <param name="action_type"></param>
/// <param name="action_mode"></param>
/// <param name="action_idx"></param>
void movement_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_mode, int action_idx);

#endif