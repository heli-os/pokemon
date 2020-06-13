#include "book.h"
extern pokemon myPokemonList[6];
extern pokemon computerSystemList[35];

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