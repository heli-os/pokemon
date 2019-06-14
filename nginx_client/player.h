#include "nginx_common.h"
typedef struct _PLAYER_STATUS {
	ALLEGRO_BITMAP* player;
	ALLEGRO_BITMAP* hit_efftect;
	char* name;

	int action_type;
	int player_direction;
	int action_idx;

	float pos_x;
	float pos_y;

	int hp;
	int armor;
} PLAYER_STATUS;

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