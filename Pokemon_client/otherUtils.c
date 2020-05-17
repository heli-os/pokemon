#include "otherUtils.h"
extern pokemon myPokemonList[6];
bool isDead(pokemon* target) {
	if (target->no == -1) return true;

	return target->crt_hp <= 0;
}
void healingPokemon() {
	for (int i = 0; i < 6; i++)
		if (myPokemonList[i].no != -1)
			myPokemonList[i].crt_hp = myPokemonList[i].max_hp;
}
bool remainPokemon() {
	for (int i = 0; i < 6; i++)
		if (!isDead(&myPokemonList[i]))
			return true;
	return false;
}