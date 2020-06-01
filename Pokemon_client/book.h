#ifndef _POKEMON_BOOK_HEADER_
#define _POKEMON_BOOK_HEADER_
#include "nginx_common.h"
#include "skill.h"

ALLEGRO_BITMAP* pokemonBitmap;
ALLEGRO_BITMAP* pokemonMenuBitmap;

extern ALLEGRO_BITMAP* menuFrame;

typedef struct BOOKTHUMB {
	bool thumbOpen;
	int currentThumb;
} pokemonThumbStatus;

typedef struct POKEMONMENU {
	bool pokemonMenuOpen;
	int currentIndex;
} pokemonMenuStatus;


/*
포켓몬 도감
포켓몬 정보(구조체)를 담은 리스트?
*/
// 도감번호, 이름, 타입, HP, 공격, 방어, 속도, 비트맵(64x64, 64x64, 32x16, 32x16)
typedef struct _POKEMON_STATUS {
	int no;				// 도감 번호
	char* displayName;	// 포켓몬 이름
	char type;			// 타입(풀,독,불꽃,비행,물,노말,전기)
	int level;
	int exp;
	int crt_hp;
	int max_hp;
	int dmg;
	int def;
	int spd;
	pokemonSkill skill[4];
	ALLEGRO_BITMAP* front;
	ALLEGRO_BITMAP* back;
	ALLEGRO_BITMAP* icon[2];
} pokemon;

enum {
	POKEMON_TYPE_NORMAL,
	POKEMON_TYPE_GRASS,
	POKEMON_TYPE_POISON,
	POKEMON_TYPE_FIRE,
	POKEMON_TYPE_FLYING,
	POKEMON_TYPE_WATER,
	POKEMON_TYPE_ELECTRIC
};

// 체력 상승량 8/16/24
// 공격 상승량 4/8/12
// 방어 상승량 2/4/6
// 속도 상승량 3/6/9
#define POKEMON_HP_PER_LEVELUP	0.005
#define POKEMON_DMG_PER_LEVELUP	0.015
#define POKEMON_DEF_PER_LEVELUP	0.00125
#define POKEMON_SPD_PER_LEVELUP	0.003


enum POKEMONBOOK {
	POKEMON_Bulbasaur,
	POKEMON_Ivysaur,
	POKEMON_Venusaur,
	POKEMON_Charmander,
	POKEMON_Charmeleon,
	POKEMON_Charizard,
	POKEMON_Squirtle,
	POKEMON_Wartortle,
	POKEMON_Blastoise,
	POKEMON_Pidgey,
	POKEMON_Pidgeotto,
	POKEMON_Pidgeot,
	POKEMON_Rattata,
	POKEMON_Pikachu,
	POKEMON_Raichu,
};


void initPokemonThumb();
bool checkPokemonType(const pokemon _pokemon, const int type);
void showPokemonThumb(int pokemonId);
void closePokemonThumb();

void showPokemonMenu();
void closePokemonMenu();


pokemon createPokemon(int pokemonId, int level);

#endif