#ifndef _NGINX_BOOK_HEADER_
#define _NGINX_BOOK_HEADER_
#include "nginx_common.h"

/*
포켓몬 도감
포켓몬 정보(구조체)를 담은 리스트?
*/
// 도감번호, 이름, 타입, HP, 공격, 방어, 속도
typedef struct _POKEMON_STATUS {
	int no;				// 도감 번호

	const char* displayName;	// 포켓몬 이름

	char type;			// 타입(풀,독,불꽃,비행,물,노말,전기)

	int hp;

	int dmg;

	int def;

	int spd;

} pokemon;

#define POKEMON_TYPE_NORMAL		0b0000001
#define POKEMON_TYPE_GRASS		0b0000010
#define POKEMON_TYPE_POISON		0b0000100
#define POKEMON_TYPE_FIRE		0b0001000
#define POKEMON_TYPE_FLYING		0b0010000
#define POKEMON_TYPE_WATER		0b0100000
#define POKEMON_TYPE_ELECTRIC	0b1000000

// 체력 상승량 8/16/24
// 공격 상승량 4/8/12
// 방어 상승량 2/4/6
// 속도 상승량 3/6/9
#define POKEMON_HP_PER_LEVELUP	8
#define POKEMON_DMG_PER_LEVELUP	4
#define POKEMON_DEF_PER_LEVELUP	2
#define POKEMON_SPD_PER_LEVELUP	3


/*
01. 이상해씨
02. 이상해풀
03. 이상해꽃
04. 파이리
05. 리자드
06. 리자몽
07. 꼬부기
08. 어니부기
09. 거북왕
10. 구구
11. 피죤
12. 피죤투
13. 꼬렛
14.피카츄
15.라이츄
*/
// 도감번호, 이름, 타입, HP, 공격, 방어, 속도
static pokemon pokemonBook[15] = {
	// 이상해씨, 이상해풀, 이상해꽃
	{ 1,  "Bulbasaur",  POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 110, 20, 10 ,5},
	{ 2,  "Ivysaur",    POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 220, 30, 15 ,7},
	{ 3,  "Venusaur",   POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 385, 44, 22 ,10},
	// 파이리, 리자드, 리자몽
	{ 4,  "Charmander", POKEMON_TYPE_FIRE						, 90, 24, 8 ,5},
	{ 5,  "Charmeleon", POKEMON_TYPE_FIRE						, 180, 36, 12 ,7},
	{ 6,  "Charizard",  POKEMON_TYPE_FIRE | POKEMON_TYPE_FLYING , 315, 53, 18 ,10},
	// 꼬부기, 어니부기, 거북왕
	{ 7,  "Squirtle",   POKEMON_TYPE_WATER, 95, 22, 9 ,5},
	{ 8,  "Wartortle",  POKEMON_TYPE_WATER, 190, 33, 14 ,7},
	{ 9,  "Blastoise",  POKEMON_TYPE_WATER, 332, 49, 20 ,10},
	// 구구, 피죤, 피죤투
	{ 10, "Pidgey",     POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 93, 23, 8 ,9},
	{ 11, "Pidgeotto",  POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 186, 35, 12 ,13},
	{ 12, "Pidgeot",    POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 325, 51, 18 ,18},
	// 꼬렛
	{ 13, "Rattata",    POKEMON_TYPE_NORMAL, 83, 17, 15 ,8},
	// 피카츄, 라이츄
	{ 14, "Pikachu",    POKEMON_TYPE_ELECTRIC, 105, 22, 9 ,6},
	{ 15, "Raichu",     POKEMON_TYPE_ELECTRIC, 240, 51, 21 ,14}
};

bool checkPokemonType(const pokemon _pokemon, const int type);
#endif