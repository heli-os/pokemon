#ifndef _PLAYER_HEADER_
#define _PLAYER_HEADER_
#include "nginx_common.h"

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32


typedef struct _PLAYER_STATUS {
	ALLEGRO_BITMAP* _player;
	ALLEGRO_BITMAP* _hit_efftect;
	char* cName;

	int iAction_type;
	int iPlayer_direction;
	int iAction_idx;

	float fPos_x;
	float fPos_y;

	int iHp;
	int iArmor;

	int iBuf;
} player_status;

static int character_movement[4][4][4] = {
	{{0,0,1,2},{1,0,1,2},{2,0,1,2},{3,0,1,2}},
	{{0,2,1,2},{1,2,1,2},{2,2,1,2},{3,2,1,2}},
	{{0,4,1,2},{1,4,1,2},{2,4,1,2},{3,4,1,2}},
	{{0,6,1,2},{1,6,1,2},{2,6,1,2},{3,6,1,2}}
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


void movement_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx);
void attack_character(ALLEGRO_BITMAP* bitmap, float dx, float dy, int action_type, int action_idx);
void show_hit_effect(ALLEGRO_BITMAP* bitmap, float dx, float dy, int player_direction, int action_idx);

#endif