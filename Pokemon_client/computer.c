#include "computer.h"

void initComputerSystemList() {
	int size = sizeof(computerSystemList) / sizeof(pokemon);
	for (int i = 0; i < size; i++) {
		//computerSystemList[i] = createPokemon(5, 99);
		computerSystemList[i].no = -1;
	}
}