#pragma once
#ifndef _POKEMON_BATTLE_HEADER_
#define _POKEMON_BATTLE_HEADER_
#include "nginx_common.h"
#include "book.h"

/*
배틀 UI 상태를 저장하는 구조체
	bool battleUIOpen;
	bool battleUIConv;
	bool battleUISkill;
	bool battleUIEnd;
	bool battleUICatching;
	int currentMenu;
	int currentIndex;	
	int currentPokemonIdx;
	int enemyPokemonIdx;
	int catchingIdx;
	bool catchingResult;
	bool battleIsGym;
*/
typedef struct BATTLEUI_STATUS {
	bool battleUIOpen;
	bool battleUIConv;
	bool battleUISkill;
	bool battleUIEnd;
	bool battleUICatching;
	int currentMenu;
	int currentIndex;	
	int currentPokemonIdx;
	int enemyPokemonIdx;
	int catchingIdx;
	bool catchingResult;
	bool battleIsGym;
} battleUIStatus;

#define TOTAL_APPEAR_RATE   0.125
#define GRADE_1_APPEAR_RATE 0.6
#define GRADE_2_APPEAR_RATE 0.3
#define GRADE_3_APPEAR_RATE 0.1

ALLEGRO_BITMAP* battleUIBitmap;

/// <summary>
/// 배틀 UI를 그리는 함수
/// </summary>
void showBattleUI();

/// <summary>
/// 적의 공격 프로세스를 수행하는 함수
/// </summary>
void CPUattackProcess();

/// <summary>
/// 플레이어의 공격 프로세스를 수행하는 함수
/// </summary>
/// <param name="attacker"></param>
/// <param name="defender"></param>
/// <param name="skill"></param>
void attackProcess(pokemon* attacker, pokemon* defender, pokemonSkill* skill);

#endif