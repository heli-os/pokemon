#ifndef _NGINX_SKILL_HEADER_
#define _NGINX_SKILL_HEADER_
#include "nginx_common.h"

typedef struct _SKILL_STATUS {
	int no;				// 스킬 번호
	char* displayName;	// 스킬 이름
	char type;			// 타입(풀,독,불꽃,비행,물,노말,전기)
	double dmg_cf;		// 피해 계수
	double acc;
	int crt_pp;
	int max_pp;
	int level_condition;
	bool own;
} pokemonSkill;

static char* SkillType[] = {
	"NORMAL",
	"GRASS",
	"POISION",
	"FIRE",
	"FLYING",
	"WATER",
	"ELECTRO"
};

void initPokemonSkill();
void showSkillList();

#endif