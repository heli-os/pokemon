#include "nginx_framework.h"
#include "menu.h"
#include "catching.h"
#include "conversation.h"
#include "book.h"
#include "environment.h"
#include "object.h"
#include "map.h"
#include "bag.h"
#include "sound.h"

// 9구간이 7px 간격으로 나누어져있음
// -------------------------------
// | (00,00) | (07,00) | (14,00) |
// -------------------------------
// | (00,07) | (07,07) | (14,07) |
// -------------------------------
// | (00,14) | (07,14) | (14,14) |
// -------------------------------
extern menuStatus menu_status;
extern conversationStatus conversation_status;
extern pokemonMenuStatus pokemonMenu_status;
extern bagUIStatus bagUI_status;
extern float camera_position_x;
extern float camera_position_y;

extern ALLEGRO_BITMAP* _map[3];

extern ALLEGRO_FONT* get_menuPirnt_font();

extern int objectPosition[][4][5];

extern int userNo;
void showMenu(int menuId) {
	if (menuId == -1) return;
	int col = 0, row = 0;
	ALLEGRO_BITMAP* menuBitmap = al_clone_bitmap(menuFrame);
	al_convert_mask_to_alpha(menuBitmap, al_map_rgb(112, 200, 160));

	int thumbX = camera_position_x + GAME_WIDTH - (mapMenu[menuId][1] + 2) * 7 * GAME_SCALE - 16;
	int menuY = camera_position_y + 16;

	menu_status.maxMenuIndex = mapMenu[menuId][0];
	int menuCol = mapMenu[menuId][1];
	int menuRow = mapMenu[menuId][2];

	// 상단
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, menuY, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < menuCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY, GAME_SCALE, GAME_SCALE, 0, 0);

	// 중단
	for (row = 0; row < menuRow; row++) {
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		for (col = 0; col < menuCol; col++)
			al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	}
	// 하단
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < menuCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 7, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 14, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, thumbX + (col + 1) * 7 * GAME_SCALE, menuY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);

	for (int mChar = 0; mChar < menu_status.maxMenuIndex; mChar++) 
		al_draw_text(get_menuPirnt_font(), al_map_rgb(90, 90, 90), thumbX + 15 * GAME_SCALE, menuY + 8 * GAME_SCALE + (43 * mChar), ALLEGRO_ALIGN_LEFT, mapMenuChar[menuId][mChar]);
	
	al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 21, 6, 8, al_map_rgb(255, 255, 255), 0, 0, thumbX + 7 * GAME_SCALE, menuY + 8 * GAME_SCALE + (43 * menu_status.menuIndex), GAME_SCALE, GAME_SCALE, 0, 0);

}

void closeMenu() {
	menu_status.menuOpen = false;
	menu_status.maxMenuIndex = 0;
	menu_status.menuIndex = 0;
	menu_status.currentMenu = -1;
}

void menuHandler() {
	switch (menu_status.currentMenu) {
	case GLOBAL_MENU:
		switch (menu_status.menuIndex) {
		case 0:
			pokemonMenu_status.pokemonMenuOpen = true;
			pokemonMenu_status.currentIndex = 0;
			break;
		case 1:
			bagUI_status.bagUIOpen = true;
			bagUI_status.currentMenu = 0;
			bagUI_status.currentIndex = 0;
			bagUI_status.lastIndex = 5;
			break;
		case 2:
			// SFX_SAVE
			soundHandler(302);
			environmentSave(userNo, 0);
			closeMenu();
			conversation_status.currentConvs = SAVE_SUCCESS_CONVERSATION;
			conversation_status.maxIndex = 1;
			conversation_status.convsOpen = true;
			break;
		case 3: // EXIT
			closeMenu();
			break;
		}
		break;
	case POKEBALL_00_MENU:
		switch (menu_status.menuIndex) {
		case 0:
			catchingPokemon(createPokemon(POKEMON_Bulbasaur,5));
			objectPosition[GAME_STAGE][0][4] = 0;
			objectPosition[GAME_STAGE][1][4] = 0;
			objectPosition[GAME_STAGE][2][4] = 0;
			init_terrain(_map[mapOffset[GAME_STAGE][0]]);
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		case 1:
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		}
		break;
	case POKEBALL_01_MENU:
		switch (menu_status.menuIndex) {
		case 0:
			catchingPokemon(createPokemon(POKEMON_Charmander,5));
			objectPosition[GAME_STAGE][0][4] = 0;
			objectPosition[GAME_STAGE][1][4] = 0;
			objectPosition[GAME_STAGE][2][4] = 0;
			init_terrain(_map[mapOffset[GAME_STAGE][0]]);
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		case 1:
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		}
		break;
	case POKEBALL_02_MENU:
		switch (menu_status.menuIndex) {
		case 0:
			catchingPokemon(createPokemon(POKEMON_Squirtle,5));
			objectPosition[GAME_STAGE][0][4] = 0;
			objectPosition[GAME_STAGE][1][4] = 0;
			objectPosition[GAME_STAGE][2][4] = 0;
			init_terrain(_map[mapOffset[GAME_STAGE][0]]);
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		case 1:
			closeMenu();
			closeConversation();
			closePokemonThumb();
			break;
		}
		break;
	}
}