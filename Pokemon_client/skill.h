#ifndef _POKEMON_SKILL_HEADER_
#define _POKEMON_SKILL_HEADER_
#include "nginx_common.h"

/* 
포켓몬 스킬을 정의하는 ㄱ ㅜ조체
	int no;				// 스킬 번호
	char* displayName;	// 스킬 이름
	char type;			// 타입(풀,독,불꽃,비행,물,노말,전기)
	double dmg_cf;		// 피해 계수
	double acc;
	int crt_pp;
	int max_pp;
	int level_condition;
	bool own;
*/
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

/// <summary>
/// 포켓몬 스킬을 초기화한느 함수
/// </summary>
void initPokemonSkill();

/// <summary>
/// 배틀 중 스킬 목록을 보여주는 함수
/// </summary>
void showSkillList();

/// <summary>
/// this Type이 target Type에 어떤 시너지를 가지는지 반환해주는 함수
/// </summary>
/// <param name=""></param>
/// <param name="target"></param>
/// <returns>시너지 수치(0.5/1.0/2.0)</returns>
double convertSynergy(int this, int target);

#endif