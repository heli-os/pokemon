#pragma once
#ifndef _NGINX_CATCHING_HEADER_
#define _NGINX_CATCHING_HEADER_
#include "nginx_common.h"

#define CATCHING_MOD_POKEBALL   1.0
#define CATCHING_MOD_GREATBALL  1.5
#define CATCHING_MOD_ULTRABALL  2.0
#define CATCHING_MOD_MASTERBALL 255.0

/*
GRADE3: 30
GRADE2: 70
GRADE1: 100
*/

void catchingPokemon(int pokemonId, int level);
#endif
