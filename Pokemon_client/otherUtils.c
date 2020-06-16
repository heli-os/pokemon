#include "otherUtils.h"
#include "sound.h"

extern pokemon myPokemonList[6];
extern pokemon gymLeaderPokemonList[6];

// 포켓몬이 사망했는지 확인하는 함수.
bool isDead(pokemon* target) {
	if (target->no == -1) return true;

	return target->crt_hp <= 0;
}

// 보유한 모든 포켓몬의 HP와 스킬 PP를 회복
void healingPokemon() {
	for (int i = 0; i < 6; i++)
		if (myPokemonList[i].no != -1) {
			myPokemonList[i].crt_hp = myPokemonList[i].max_hp;
			for (int j = 0; j < 4; j++) {
				if (myPokemonList[i].skill[j].own)
					myPokemonList[i].skill[j].crt_pp = myPokemonList[i].skill[j].max_pp;
			}			
		}
	soundHandler(500);
}

// 플레이어의 포켓몬이 남아있는지 확인하는 함수
bool remainPokemon() {
	for (int i = 0; i < 6; i++)
		if (!isDead(&myPokemonList[i]))
			return true;
	return false;
}

// 체육관 관장의 포켓몬이 남아있는지 확인하는 함수
bool gymLeaderRemainPokemon() {
	for (int i = 0; i < 6; i++)
		if (!isDead(&gymLeaderPokemonList[i]))
			return true;
	return false;
}