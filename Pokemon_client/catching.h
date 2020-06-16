#pragma once
#ifndef _POKEMON_CATCHING_HEADER_
#define _POKEMON_CATCHING_HEADER_
#include "nginx_common.h"
#include "book.h"

#define CATCHING_MOD_POKEBALL   1.0
#define CATCHING_MOD_GREATBALL  1.5
#define CATCHING_MOD_ULTRABALL  2.0
#define CATCHING_MOD_MASTERBALL 255.0

/*
GRADE3: 30
GRADE2: 70
GRADE1: 100
*/

/// <summary>
/// 포켓몬을 포획하는 함수
/// createPokemon과 연계하여 작동한다
/// </summary>
/// <param name="target"></param>
void catchingPokemon(pokemon target);
#endif
