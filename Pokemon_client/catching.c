#include "book.h"
extern pokemon myPokemonList[6];

void catchingPokemon(pokemon target) {
	for (int i = 0; i < 6; i++) {
		if (myPokemonList[i].no != -1)
			continue;

		myPokemonList[i] = target;;
		printf("pokemonId:%d[%s]\n", i, myPokemonList[i].displayName);
		return;
	}
	printf("error\n");
}