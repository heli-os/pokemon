#include "book.h"
#include "skill.h"
#include "battle.h"

extern pokemon pokemonBook[15];
extern battleUIStatus battleUI_status;
extern pokemon myPokemonList[6];
extern ALLEGRO_FONT* get_pokemonSkill_list_font();
pokemonSkill pokemonSkillRef[20] = {
	{1,		"Tackle",			POKEMON_TYPE_NORMAL,	1.1,	0.95,	35,	35, 1,	true},
	{2,		"Vine Whip",		POKEMON_TYPE_GRASS,		1.1,	1.0,	10,	10, 13,	false},
	{3,		"Razor Leaf",		POKEMON_TYPE_GRASS,		1.3,	0.95,	25,	25, 30,	false},
	{4,		"SolarBeam",		POKEMON_TYPE_GRASS,		2.0,	1.0,	10,	10, 65,	false},

	{5,		"Scratch",			POKEMON_TYPE_NORMAL,	1.15,	1.0,	35,	35, 1,	true},
	{6,		"Ember",			POKEMON_TYPE_FIRE,		1.15,	1.0,	25,	25, 9,	false},
	{7,		"Slash",			POKEMON_TYPE_NORMAL,	1.7,	1.0,	20,	20, 36,	false},
	{8,		"Flamethrower",		POKEMON_TYPE_FIRE,		1.8,	1.0,	15,	15, 46,	false},

	{9,		"Tackle",			POKEMON_TYPE_NORMAL,	1.1,	0.95,	35,	35, 1,	true},
	{10,	"Bubble",			POKEMON_TYPE_WATER,		0.9,	1.0,	30,	30, 8,	false},
	{11,	"Water Gun",		POKEMON_TYPE_WATER,		1.15,	1.0,	25,	25, 15,	false},
	{12,	"Hydro Pump",		POKEMON_TYPE_WATER,		2.0,	0.8,	5,	5,	52,	false},

	{13,	"Gust",				POKEMON_TYPE_FLYING,	1.1,	1.0,	35,	35, 1,	true},
	{14,	"Quick Attack",		POKEMON_TYPE_NORMAL,	1.1,	1.0,	30,	30, 12,	false},
	{15,	"Wing Attack",		POKEMON_TYPE_FLYING,	1.2,	1.0,	35,	35, 31,	false},

	{16,	"Hyper Fang",		POKEMON_TYPE_NORMAL,	1.7,	0.9,	15,	15, 14,	false},
	{17,	"Super Fang",		POKEMON_TYPE_NORMAL,	2.0,	0.9,	10,	10, 34,	false},

	{18,	"ThunderShock",		POKEMON_TYPE_ELECTRIC,	1.1,	1.0,	30,	30, 1,	true},
	{19,	"Thunderbolt",		POKEMON_TYPE_ELECTRIC,	1.8,	1.0,	15,	15, 26,	false},
	{20,	"Thunder",			POKEMON_TYPE_ELECTRIC,	2.0,	0.7,	10,	10, 41,	false},
};

void initPokemonSkill() {
	for (int i = 0; i <= 2; i++) {
		pokemonBook[i].skill[0] = pokemonSkillRef[0];
		pokemonBook[i].skill[1] = pokemonSkillRef[1];
		pokemonBook[i].skill[2] = pokemonSkillRef[2];
		pokemonBook[i].skill[3] = pokemonSkillRef[3];
	}

	for (int i = 3; i <= 5; i++) {
		pokemonBook[i].skill[0] = pokemonSkillRef[4];
		pokemonBook[i].skill[1] = pokemonSkillRef[5];
		pokemonBook[i].skill[2] = pokemonSkillRef[6];
		pokemonBook[i].skill[3] = pokemonSkillRef[7];
	}

	for (int i = 6; i <= 8; i++) {
		pokemonBook[i].skill[0] = pokemonSkillRef[8];
		pokemonBook[i].skill[1] = pokemonSkillRef[9];
		pokemonBook[i].skill[2] = pokemonSkillRef[10];
		pokemonBook[i].skill[3] = pokemonSkillRef[11];
	}

	for (int i = 9; i <= 11; i++) {
		pokemonBook[i].skill[0] = pokemonSkillRef[12];
		pokemonBook[i].skill[1] = pokemonSkillRef[13];
		pokemonBook[i].skill[2] = pokemonSkillRef[14];
	}

	pokemonBook[12].skill[0] = pokemonSkillRef[0];
	pokemonBook[12].skill[1] = pokemonSkillRef[13];
	pokemonBook[12].skill[2] = pokemonSkillRef[15];
	pokemonBook[12].skill[3] = pokemonSkillRef[16];

	for (int i = 13; i <= 14; i++) {
		pokemonBook[i].skill[0] = pokemonSkillRef[17];
		pokemonBook[i].skill[1] = pokemonSkillRef[13];
		pokemonBook[i].skill[2] = pokemonSkillRef[18];
		pokemonBook[i].skill[3] = pokemonSkillRef[19];
	}
}
extern float camera_position_x;
extern float camera_position_y;
void showSkillList() {
	int convsX = camera_position_x + 14 * GAME_SCALE;
	int convsY = camera_position_y + (GAME_HEIGHT - 48 * GAME_SCALE) + 14 * GAME_SCALE;

	if (strlen(myPokemonList[battleUI_status.currentPokemonIdx].skill[0].displayName) != 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[0].own)
		al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX, convsY, ALLEGRO_ALIGN_LEFT, myPokemonList[battleUI_status.currentPokemonIdx].skill[0].displayName);

	if (strlen(myPokemonList[battleUI_status.currentPokemonIdx].skill[1].displayName) != 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[1].own)
		al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX + 54.5 * GAME_SCALE, convsY , ALLEGRO_ALIGN_LEFT, myPokemonList[battleUI_status.currentPokemonIdx].skill[1].displayName);

	if (strlen(myPokemonList[battleUI_status.currentPokemonIdx].skill[2].displayName) != 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[2].own)
		al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX, convsY + 14 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, myPokemonList[battleUI_status.currentPokemonIdx].skill[2].displayName);

	if (strlen(myPokemonList[battleUI_status.currentPokemonIdx].skill[3].displayName) != 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[3].own)
		al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX + 54.5 * GAME_SCALE, convsY + 14 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, myPokemonList[battleUI_status.currentPokemonIdx].skill[3].displayName);

	
	char tmp_crt_pp[255], tmp_max_pp[255];
	sprintf_s(tmp_crt_pp, sizeof(tmp_crt_pp), "%d", myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex].crt_pp);
	sprintf_s(tmp_max_pp, sizeof(tmp_max_pp), "%d", myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex].max_pp);
	al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX + 154 * GAME_SCALE, convsY + -2 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_crt_pp);
	al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX + 169 * GAME_SCALE, convsY + -2 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_crt_pp);

	al_draw_text(get_pokemonSkill_list_font(), al_map_rgb(64, 64, 64), convsX + 145 * GAME_SCALE, convsY + 16 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, SkillType[myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex].type]);

	int arrowOffset_x = 0;
	int arrowOffset_y = 0;

	switch (battleUI_status.currentIndex) {
	case 0:
		arrowOffset_x = -5.5 * GAME_SCALE;
		arrowOffset_y = -1 * GAME_SCALE;
		break;
	case 1:
		arrowOffset_x = 49 * GAME_SCALE;
		arrowOffset_y = -1 * GAME_SCALE;
		break;
	case 2:
		arrowOffset_x = -5.5 * GAME_SCALE;
		arrowOffset_y = 13 * GAME_SCALE;
		break;
	case 3:
		arrowOffset_x = 49 * GAME_SCALE;
		arrowOffset_y = 13 * GAME_SCALE;
		break;
	}
	al_draw_tinted_scaled_rotated_bitmap_region(battleUIBitmap, 123, 0, 6, 10, al_map_rgb(255, 255, 255), 0, 0, convsX + arrowOffset_x, convsY + arrowOffset_y, 3.3333333, GAME_SCALE, 0, 0);

}

double convertSynergy(int this, int target) {
	if (this == POKEMON_TYPE_NORMAL) return 1.0;
	if (this == target) return 0.5;

	double ret = 0.0;
	switch (this) {
	case POKEMON_TYPE_GRASS:
		if (target == POKEMON_TYPE_FIRE) return 0.5;
		if (target == POKEMON_TYPE_POISON) return 0.5;
		if (target == POKEMON_TYPE_FLYING) return 0.5;
		if (target == POKEMON_TYPE_WATER) return 2.0;
		return 1.0;
	case POKEMON_TYPE_POISON:
		if (target == POKEMON_TYPE_GRASS) return 2.0;
		return 1.0;
	case POKEMON_TYPE_FIRE:
		if (target == POKEMON_TYPE_WATER) return 0.5;
		if (target == POKEMON_TYPE_GRASS) return 2.0;
		return 1.0;
	case POKEMON_TYPE_FLYING:
		if (target == POKEMON_TYPE_ELECTRIC) return 0.5;
		if (target == POKEMON_TYPE_GRASS) return 2.0;
		return 1.0;
	case POKEMON_TYPE_WATER:
		if (target == POKEMON_TYPE_GRASS) return 0.5;
		if (target == POKEMON_TYPE_FIRE) return 2.0;
		return 1.0;
	case POKEMON_TYPE_ELECTRIC:
		if (target == POKEMON_TYPE_GRASS) return 0.5;
		if (target == POKEMON_TYPE_WATER) return 2.0;
		if (target == POKEMON_TYPE_FLYING) return 2.0;
		return 1.0;
	}
}