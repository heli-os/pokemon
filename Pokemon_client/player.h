#ifndef _POKEMON_PLAYER_HEADER_
#define _POKEMON_PLAYER_HEADER_

#include "nginx_common.h"

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 20



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
static int character_attack[4][4][4] = {
	{{0,0,1,2},{1,0,1,2},{2,0,1,2},{3,0,1,2}},
	{{0,2,1,2},{1,2,1,2},{2,2,1,2},{3,2,1,2}},
	{{0,1,1,2},{1,1,1,2},{2,1,1,2},{3,1,1,2}},
	{{0,3,1,2},{1,3,1,2},{2,3,1,2},{3,3,1,2}}
};

static int character_hit_effect[10][4] = {
	{0,0,1,1},{1,0,1,1},{2,0,1,1},{3,0,1,1},{4,0,1,1},
	{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{4,1,1,1}
};

void sendPlayerStatus(const char* header, const player uPlayer);
void movement_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_mode, int action_idx);
void attack_character(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_type, int action_idx);
void show_hit_effect(ALLEGRO_BITMAP* bitmap, int dx, int dy, int action_idx);

#endif