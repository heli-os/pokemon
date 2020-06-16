#include "computer.h"

ALLEGRO_USTR* transferUserNickInput;

// 포켓몬 보관시스템(컴퓨터) 초기화
// 컴퓨터의 모든 포켓몬을 -1로 초기화한다.
void initComputerSystemList() {
	int size = sizeof(computerSystemList) / sizeof(pokemon);
	for (int i = 0; i < size; i++) {
		//computerSystemList[i] = createPokemon(5, 99);
		computerSystemList[i].no = -1;
	}
}