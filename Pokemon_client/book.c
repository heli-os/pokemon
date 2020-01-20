#include "book.h"
bool checkPokemonType(const pokemon _pokemon, const int type) {
	for (int i = 0; i < 7; i++) {
		if (_pokemon.type & type)
			return true;
	}
	return false;
}