#include "book.h"
#include <math.h>
#include "battle.h"

extern pokemonSkill pokemonSkillRef[20];
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
pokemon pokemonBook[15] = {
	// 이상해씨, 이상해풀, 이상해꽃
	{ 1,  "Bulbasaur",  POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 1, 0, 110, 110, 21, 10 ,5},
	{ 2,  "Ivysaur",    POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 1, 0, 220, 220, 45, 15 ,7},
	{ 3,  "Venusaur",   POKEMON_TYPE_GRASS | POKEMON_TYPE_POISON, 1, 0, 385, 385, 78, 22 ,10},
	// 파이리, 리자드, 리자몽
	{ 4,  "Charmander", POKEMON_TYPE_FIRE						, 1, 0,  90,  90, 27,  8 ,5},
	{ 5,  "Charmeleon", POKEMON_TYPE_FIRE						, 1, 0, 180, 180, 55, 12 ,7},
	{ 6,  "Charizard",  POKEMON_TYPE_FIRE | POKEMON_TYPE_FLYING , 1, 0, 315, 315, 96, 18 ,10},
	// 꼬부기, 어니부기, 거북왕
	{ 7,  "Squirtle",   POKEMON_TYPE_WATER, 1, 0, 95, 95, 22, 9 ,5},
	{ 8,  "Wartortle",  POKEMON_TYPE_WATER, 1, 0, 190, 190, 47, 14 ,7},
	{ 9,  "Blastoise",  POKEMON_TYPE_WATER, 1, 0, 332, 332, 83, 20 ,10},
	// 구구, 피죤, 피죤투
	{ 10, "Pidgey",     POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 1, 0,  93,  93, 23,  8 ,9},
	{ 11, "Pidgeotto",  POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 1, 0, 186, 186, 46, 12 ,13},
	{ 12, "Pidgeot",    POKEMON_TYPE_NORMAL | POKEMON_TYPE_FLYING, 1, 0, 325, 325, 81, 18 ,18},
	// 꼬렛
	{ 13, "Rattata",    POKEMON_TYPE_NORMAL, 1, 0, 83, 83, 20, 15 ,8},
	// 피카츄, 라이츄
	{ 14, "Pikachu",    POKEMON_TYPE_ELECTRIC, 1, 0, 105, 105, 28,  9,  6},
	{ 15, "Raichu",     POKEMON_TYPE_ELECTRIC, 1, 0, 240, 240, 70, 21, 14},
};

bool checkPokemonType(const pokemon _pokemon, const int type) {
	for (int i = 0; i < 7; i++) {
		if (_pokemon.type & type)
			return true;
	}
	return false;
}

void initPokemonThumb() {
	int i = 0;
	al_convert_mask_to_alpha(pokemonBitmap, al_map_rgb(200, 200, 168));

	for (i = 0; i < 15; i++) {
		pokemonBook[i].front = al_create_bitmap(64 * GAME_SCALE, 64 * GAME_SCALE);
		pokemonBook[i].back = al_create_bitmap(64 * GAME_SCALE, 64 * GAME_SCALE);
		pokemonBook[i].icon[0] = al_create_bitmap(32 * GAME_SCALE, 32 * GAME_SCALE);
		pokemonBook[i].icon[1] = al_create_bitmap(32 * GAME_SCALE, 32 * GAME_SCALE);


		al_set_target_bitmap(pokemonBook[i].front);
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonBitmap, 0, 64 * i, 64, 64, al_map_rgb(255, 255, 255), 0, 0, 0, 0, GAME_SCALE, GAME_SCALE, 0, 0);

		al_set_target_bitmap(pokemonBook[i].back);
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonBitmap, 64, 64 * i, 64, 64, al_map_rgb(255, 255, 255), 0, 0, 0, 0, GAME_SCALE, GAME_SCALE, 0, 0);

		al_set_target_bitmap(pokemonBook[i].icon[0]);
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonBitmap, 128, 64 * i, 32, 32, al_map_rgb(255, 255, 255), 0, 0, 0, 0, GAME_SCALE, GAME_SCALE, 0, 0);

		al_set_target_bitmap(pokemonBook[i].icon[1]);
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonBitmap, 128, 32 + 64 * i, 32, 32, al_map_rgb(255, 255, 255), 0, 0, 0, 0, GAME_SCALE, GAME_SCALE, 0, 0);
	}
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

extern float camera_position_x;
extern float camera_position_y;
void showPokemonThumb(int pokemonId) {
	if (pokemonId == -1) return;

	int col = 0, row = 0;
	ALLEGRO_BITMAP* menuBitmap = al_clone_bitmap(menuFrame);
	al_convert_mask_to_alpha(menuBitmap, al_map_rgb(112, 200, 160));


	int thumbX = camera_position_x + (GAME_WIDTH / 2) - 28 * GAME_SCALE;
	int thumbY = camera_position_y + (GAME_HEIGHT / 2) - 28 * GAME_SCALE;

	int thumbCol = 7;
	int thumbRow = 7;

	// 상단
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, thumbY, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < thumbCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY, GAME_SCALE, GAME_SCALE, 0, 0);

	// 중단
	for (row = 0; row < thumbRow; row++) {
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		for (col = 0; col < thumbCol; col++)
			al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	}
	// 하단
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < thumbCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, thumbY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);

	//al_draw_tinted_scaled_rotated_bitmap_region(pokemonBook[pokemonId].front, 0, 0, 64, 64, al_map_rgb(255, 255, 255), 0, 0, thumbX, thumbY, GAME_SCALE, GAME_SCALE, 0, 0);

	al_draw_bitmap(pokemonBook[pokemonId].front, thumbX, thumbY, 0);
}
extern pokemonThumbStatus pokemonThumb_status;

void closePokemonThumb() {
	pokemonThumb_status.currentThumb = -1;
	pokemonThumb_status.thumbOpen = false;
}

extern pokemonMenuStatus pokemonMenu_status;
extern pokemon myPokemonList[6];
extern ALLEGRO_FONT* get_pokemonmenuPirnt_font();
extern ALLEGRO_FONT* get_menuPirnt_font();
extern ALLEGRO_FONT* get_pokemonmenu_level_Print_font();
extern ALLEGRO_FONT* get_pokemonmenu_hp_Print_font();
void showPoekmonMenu() {
	if (!pokemonMenu_status.pokemonMenuOpen) return;


	al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 250, 5, 240, 160, al_map_rgb(255, 255, 255), 0, 0, camera_position_x, camera_position_y, 3.33333333, GAME_SCALE, 0, 0);

	int index_0_pos_x = camera_position_x + 2 * GAME_SCALE;
	int index_0_pos_y = camera_position_y + 18 * GAME_SCALE;
	if (myPokemonList[0].no != -1) {
		if (pokemonMenu_status.currentIndex == 0)
			al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 406, 170, 89, 57, al_map_rgb(255, 255, 255), 0, 0, index_0_pos_x, index_0_pos_y, 3.33333333, GAME_SCALE, 0, 0);
		else
			al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 317, 170, 89, 57, al_map_rgb(255, 255, 255), 0, 0, index_0_pos_x, index_0_pos_y, 3.33333333, GAME_SCALE, 0, 0);
		al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(115, 115, 115), index_0_pos_x + (myPokemonList[0].no == 6 ? 30 : 27) * GAME_SCALE, index_0_pos_y + 22 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, myPokemonList[0].displayName);
		al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(255, 255, 255), index_0_pos_x + (myPokemonList[0].no == 6 ? 30 : 27) * GAME_SCALE - 2, index_0_pos_y + 22 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, myPokemonList[0].displayName);

		char tmp_level[255];
		sprintf_s(tmp_level, sizeof(tmp_level), "%d", myPokemonList[0].level);
		al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(115, 115, 115), index_0_pos_x + 40 * GAME_SCALE, index_0_pos_y + 29 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_level);
		al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(255, 255, 255), index_0_pos_x + 40 * GAME_SCALE - 2, index_0_pos_y + 29 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_level);
		char tmp_crt_hp[255], tmp_max_hp[255];
		sprintf_s(tmp_crt_hp, sizeof(tmp_crt_hp), "%d", myPokemonList[0].crt_hp);
		sprintf_s(tmp_max_hp, sizeof(tmp_max_hp), "%d", myPokemonList[0].max_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_0_pos_x + 36 * GAME_SCALE, index_0_pos_y + 46 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_0_pos_x + 36 * GAME_SCALE - 2, index_0_pos_y + 46 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_0_pos_x + 54 * GAME_SCALE, index_0_pos_y + 46 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_0_pos_x + 54 * GAME_SCALE - 2, index_0_pos_y + 46 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
		
		int index_0_hp_pos_x = index_0_pos_x + 25.1 * GAME_SCALE;
		int index_0_hp_pos_y = index_0_pos_y + 41 * GAME_SCALE;
		double hp_matrix = myPokemonList[0].crt_hp / (double)myPokemonList[0].max_hp * 100;
		for (int i = 0; i < hp_matrix; i++) {
			if(hp_matrix<=25)
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 360, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_0_hp_pos_x + 0.3945 * i * GAME_SCALE, index_0_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
			else if(hp_matrix<=50)
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 366, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_0_hp_pos_x + 0.3945 * i * GAME_SCALE, index_0_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
			else
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 384, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_0_hp_pos_x + 0.3945 * i * GAME_SCALE, index_0_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
		}	
	}

	int index_other_pos_x = camera_position_x + 73.4 * GAME_SCALE;
	int index_other_pos_y = camera_position_y + 9 * GAME_SCALE;
	int index_other_hp_pos_x = index_other_pos_x + 80 * GAME_SCALE;
	int index_other_hp_pos_y = index_other_pos_y + 9 * GAME_SCALE;
	if (myPokemonList[1].no != -1) {
		if (pokemonMenu_status.currentIndex == 1)
			al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 162, 203, 150, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x, index_other_pos_y, 3.33333333, GAME_SCALE, 0, 0);
		else
			al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 162, 179, 150, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x, index_other_pos_y + 4, 3.33333333, GAME_SCALE, 0, 0);
		al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 23 * GAME_SCALE, index_other_pos_y + 5 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, myPokemonList[1].displayName);
		al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 23 * GAME_SCALE - 2, index_other_pos_y + 5 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, myPokemonList[1].displayName);

		char tmp_level[255];
		sprintf_s(tmp_level, sizeof(tmp_level), "%d", myPokemonList[1].level);
		al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 42 * GAME_SCALE, index_other_pos_y + 14 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_level);
		al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 42 * GAME_SCALE - 2, index_other_pos_y + 14 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_level);
		char tmp_crt_hp[255], tmp_max_hp[255];
		sprintf_s(tmp_crt_hp, sizeof(tmp_crt_hp), "%d", myPokemonList[1].crt_hp);
		sprintf_s(tmp_max_hp, sizeof(tmp_max_hp), "%d", myPokemonList[1].max_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 91 * GAME_SCALE, index_other_pos_y + 14 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 91 * GAME_SCALE - 2, index_other_pos_y + 14 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 109 * GAME_SCALE, index_other_pos_y + 14 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
		al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 109 * GAME_SCALE - 2, index_other_pos_y + 14 * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
	
		
		double hp_matrix = myPokemonList[1].crt_hp / (double)myPokemonList[1].max_hp * 100;
		for (int i = 0; i < hp_matrix; i++) {
			if (hp_matrix <= 25)
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 360, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * i * GAME_SCALE, index_other_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
			else if (hp_matrix <= 50)
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 366, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * i * GAME_SCALE, index_other_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
			else
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 384, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * i * GAME_SCALE, index_other_hp_pos_y, 3.33333333, GAME_SCALE, 0, 0);
		}
	}
	for (int i = 2; i <= 5; i++) {
		if (myPokemonList[i].no != -1) {
			if (pokemonMenu_status.currentIndex == i)
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 162, 203, 150, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x, index_other_pos_y + ((i - 2) * 24 + 24) * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
			else
				al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 162, 179, 150, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x, index_other_pos_y + ((i - 2) * 24 + 25) * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
			al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 23 * GAME_SCALE, index_other_pos_y + ((i-2)*24 + 29) * GAME_SCALE, ALLEGRO_ALIGN_LEFT, myPokemonList[i].displayName);
			al_draw_text(get_pokemonmenuPirnt_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 23 * GAME_SCALE - 2, index_other_pos_y + ((i - 2) * 24 + 29) * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, myPokemonList[i].displayName);

			char tmp_level[255];
			sprintf_s(tmp_level, sizeof(tmp_level), "%d", myPokemonList[i].level);
			al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 42 * GAME_SCALE, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_level);
			al_draw_text(get_pokemonmenu_level_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 42 * GAME_SCALE - 2, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_level);
			char tmp_crt_hp[255], tmp_max_hp[255];
			sprintf_s(tmp_crt_hp, sizeof(tmp_crt_hp), "%d", myPokemonList[i].crt_hp);
			sprintf_s(tmp_max_hp, sizeof(tmp_max_hp), "%d", myPokemonList[i].max_hp);
			al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 91 * GAME_SCALE, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
			al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 91 * GAME_SCALE - 2, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_crt_hp);
			al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(115, 115, 115), index_other_pos_x + 109 * GAME_SCALE, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
			al_draw_text(get_pokemonmenu_hp_Print_font(), al_map_rgb(255, 255, 255), index_other_pos_x + 109 * GAME_SCALE - 2, index_other_pos_y + ((i - 2) * 24 + 38) * GAME_SCALE - 2, ALLEGRO_ALIGN_LEFT, tmp_max_hp);
			
			double hp_matrix = myPokemonList[i].crt_hp / (double)myPokemonList[i].max_hp * 100;
			for (int j = 0; j < hp_matrix; j++) {
				if (hp_matrix <= 25)
					al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 360, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * j * GAME_SCALE, index_other_hp_pos_y + 24 * (i-1) * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
				else if (hp_matrix <= 50)
					al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 366, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * j * GAME_SCALE, index_other_hp_pos_y + 24 * (i - 1) * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
				else
					al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 384, 235, 1, 3, al_map_rgb(255, 255, 255), 0, 0, index_other_hp_pos_x + 0.3945 * j * GAME_SCALE, index_other_hp_pos_y + 24 * (i - 1) * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
			}
		}
	}
	if (pokemonMenu_status.currentIndex == 6)
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 62.5, 251, 56.5, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x + 78 * GAME_SCALE, index_other_pos_y + 123 * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);
	else
		al_draw_tinted_scaled_rotated_bitmap_region(pokemonMenuBitmap, 6, 251, 56.5, 24, al_map_rgb(255, 255, 255), 0, 0, index_other_pos_x + 80 * GAME_SCALE, index_other_pos_y + 123 * GAME_SCALE, 3.33333333, GAME_SCALE, 0, 0);


	int index_0_icon_pos_x = camera_position_x + -1 * GAME_SCALE;
	int index_0_icon_pos_y = camera_position_y + 22 * GAME_SCALE;
	if (myPokemonList[0].no != -1) {
		if (pokemonMenu_status.currentIndex == 0)
			al_draw_bitmap(myPokemonList[0].icon[0], index_0_icon_pos_x, index_0_icon_pos_y, 0);
		else
			al_draw_bitmap(myPokemonList[0].icon[1], index_0_icon_pos_x, index_0_icon_pos_y, 0);
	}

	int index_other_icon_pos_x = camera_position_x + 63 * GAME_SCALE;
	int index_other_icon_pos_y = camera_position_y + 1 * GAME_SCALE;
	for (int i = 1; i <= 5; i++) {
		if (myPokemonList[i].no != -1) {
			if (pokemonMenu_status.currentIndex == i)
				al_draw_bitmap(myPokemonList[i].icon[0], index_other_icon_pos_x, index_other_icon_pos_y + 24 * (i-1) * GAME_SCALE, 0);
			else
				al_draw_bitmap(myPokemonList[i].icon[1], index_other_icon_pos_x, index_other_icon_pos_y + 24 * (i - 1) * GAME_SCALE, 0);
		}
	}
}

extern battleUIStatus battleUI_status;
void closePokemonMenu() {
	if (battleUI_status.battleUIOpen) {
		battleUI_status.battleUIConv = false;
		battleUI_status.currentIndex = battleUI_status.currentMenu - 1;
		battleUI_status.currentMenu = 0;
	}
	pokemonMenu_status.currentIndex = -1;
	pokemonMenu_status.pokemonMenuOpen = false;
}

pokemon createPokemon(int pokemonId, int level) {
	pokemon tmpPokemon = pokemonBook[pokemonId];
	tmpPokemon.level = level;
	tmpPokemon.exp = pow(level, 3);
	tmpPokemon.crt_hp = tmpPokemon.crt_hp * pow(1 + POKEMON_HP_PER_LEVELUP, level);
	tmpPokemon.max_hp = tmpPokemon.crt_hp;
	tmpPokemon.dmg = tmpPokemon.dmg * pow(1 + POKEMON_DMG_PER_LEVELUP, level);
	tmpPokemon.def = tmpPokemon.def * pow(1 + POKEMON_DEF_PER_LEVELUP, level);
	tmpPokemon.spd = tmpPokemon.spd * pow(1 + POKEMON_SPD_PER_LEVELUP, level);

	for (int i = 0; i < 4; i++)
		if(tmpPokemon.skill[i].no != 0)
			tmpPokemon.skill[i].own = tmpPokemon.level >= tmpPokemon.skill[i].level_condition;

	return tmpPokemon;
}
void catchingPokemon(int pokemonId, int level) {
	for (int i = 0; i < 6; i++) {
		if (myPokemonList[i].no != -1)
			continue;

		myPokemonList[i] = createPokemon(pokemonId, level);
		printf("pokemonId:%d[%s]\n", i, myPokemonList[i].displayName);
		return;
	}
	printf("error\n");
}