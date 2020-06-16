#include "book.h"
extern pokemon myPokemonList[6];
extern pokemon computerSystemList[35];

// 포켓몬 포획 성공 시 호출되는 함수
// 플레이어 포켓몬 공간에 여유가 있다면 바로 획득
// 그렇지 않다면 보관 시스템(컴퓨터)에 보관
void catchingPokemon(pokemon target) {
	for (int i = 0; i < 6; i++) {
		if (myPokemonList[i].no != -1)
			continue;

		myPokemonList[i] = target;
		printf("myPokemonList::pokemonId:%d[%s]\n", i, myPokemonList[i].displayName);
		return;
	}
	for (int i = 0; i < 35; i++) {
		if (computerSystemList[i].no != -1)
			continue;

		computerSystemList[i] = target;
		printf("computerSystemList::pokemonId:%d[%s]\n", i, computerSystemList[i].displayName);
		return;
	}
	printf("error\n");
}