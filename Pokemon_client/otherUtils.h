#pragma once
#ifndef _POKEMON_OTHERUTILS_HEADER_
#define _POKEMON_OTHERUTILS_HEADER_

#include "book.h"

/// <summary>
/// 포켓몬이 사망했는지 확인하는 함수
/// </summary>
/// <param name="target"></param>
/// <returns>사망여부(true/false)</returns>
bool isDead(pokemon* target);

/// <summary>
/// 플레이어의 포켓몬이 남아있는지 확인하는 함수
/// </summary>
/// <returns>존재여부(true/false)</returns>
bool remainPokemon();

/// <summary>
/// 보유한 모든 포켓몬의 HP와 스킬 PP 회복
/// </summary>
void healingPokemon();

/// <summary>
/// 체육관 관장의 포켓몬이 남아있는지 확인하는 함수
/// </summary>
/// <returns>존재여부(true/false)</returns>
bool gymLeaderRemainPokemon();

#endif