#pragma once
#ifndef _NGINX_BATTLE_HEADER_
#define _NGINX_BATTLE_HEADER_
#include "nginx_common.h"
#include "book.h"

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
} battleUIStatus;

#define TOTAL_APPEAR_RATE 1.0//0.125
#define GRADE_1_APPEAR_RATE 0.6
#define GRADE_2_APPEAR_RATE 0.3
#define GRADE_3_APPEAR_RATE 0.1

ALLEGRO_BITMAP* battleUIBitmap;

void showBattleUI();
void CPUattackProcess();
void attackProcess(pokemon* attacker, pokemon* defender, pokemonSkill* skill);

#endif