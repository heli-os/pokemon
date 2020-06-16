#ifndef _POKEMON_BOOK_HEADER_
#define _POKEMON_BOOK_HEADER_
#include "nginx_common.h"
#include "skill.h"

ALLEGRO_BITMAP* pokemonBitmap;
ALLEGRO_BITMAP* pokemonMenuBitmap;

extern ALLEGRO_BITMAP* menuFrame;

/*
포켓몬 썸네일 상태를 저장하는 구조체
	bool thumbOpen;
	int currentThumb;
*/
typedef struct BOOKTHUMB {
	bool thumbOpen;
	int currentThumb;
} pokemonThumbStatus;

/*
포켓몬 메뉴 상태를 저장하는 구조체
	bool pokemonMenuOpen;
	int currentIndex;
*/
typedef struct POKEMONMENU {
	bool pokemonMenuOpen;
	int currentIndex;
} pokemonMenuStatus;


/// <summary>
/// 포켓몬 도감
/// 도감번호, 이름, 타입, HP, 공격, 방어, 속도, 비트맵(64x64, 64x64, 32x16, 32x16)
/// </summary>
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
	POKEMON_TYPE_NORMAL		= 0b0000001,
	POKEMON_TYPE_GRASS		= 0b0000010,
	POKEMON_TYPE_POISON		= 0b0000100,
	POKEMON_TYPE_FIRE		= 0b0001000,
	POKEMON_TYPE_FLYING		= 0b0010000,
	POKEMON_TYPE_WATER		= 0b0100000,
	POKEMON_TYPE_ELECTRIC	= 0b1000000
};

// 체력 상승량 8/16/24
// 공격 상승량 4/8/12
// 방어 상승량 2/4/6
// 속도 상승량 3/6/9
#define POKEMON_HP_PER_LEVELUP	0.005
#define POKEMON_DMG_PER_LEVELUP	0.015
#define POKEMON_DEF_PER_LEVELUP	0.030
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


/// <summary>
/// 포켓몬 썸네일을 초기화하는 함수
/// </summary>
void initPokemonThumb();

/// <summary>
/// 포켓몬 썸네일을 그리는 함수
/// </summary>
/// <param name="pokemonId"></param>
void showPokemonThumb(int pokemonId);

/// <summary>
/// 포켓몬 썸네일을 닫는 함수
/// </summary>
void closePokemonThumb();

/// <summary>
///  포켓몬 메뉴를 그리는 함수
/// </summary>
void showPokemonMenu();
/// <summary>
/// 포켓몬 메뉴를 닫는 함수
/// </summary>
void closePokemonMenu();

/// <summary>
///  포켓몬을 생성해주는 함수
/// </summary>
/// <param name="pokemonId"></param>
/// <param name="level"></param>
/// <returns>pokemon 구조체</returns>
pokemon createPokemon(int pokemonId, int level);

/// <summary>
/// 체육관 관장 포켓몬을 초기화 하는 함수
/// </summary>
void initGymLeaderPokemon();

/// <summary>
/// 진화 가능한지 확인하는 함수
/// </summary>
/// <param name="target"></param>
void isEvolution(pokemon* target);

#endif