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
#include "computer.h"

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

extern int objectPosition[8][6][5];

extern int userNo;

extern inventoryItem inventorySlots[2][6];
extern player user_player;
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

	// 컴퓨터 시스템인 경우 포켓몬 아이콘 출력 및 세부 메뉴 출력
	if (menuId == COMPUTER_SYSTEM_MENU_RELEASE || menuId == COMPUTER_SYSTEM_MENU_TAKE) {
		for (int pokeIdx = 0; pokeIdx < sizeof(computerSystemList) / sizeof(pokemon); pokeIdx++) {
			if (computerSystemList[pokeIdx].no != -1) {
				int index_0_icon_pos_x = camera_position_x + 8 * GAME_SCALE + 26 * (pokeIdx % 7) * GAME_SCALE;
				int index_0_icon_pos_y = camera_position_y + 26 * (pokeIdx / 7) * GAME_SCALE;
				if (pokeIdx == menu_status.menuIndex) {
					static pokeIconIdx = 0;
					pokeIconIdx++;
					if (pokeIconIdx % 4 == 0) {
						al_draw_bitmap(computerSystemList[pokeIdx].icon[0], index_0_icon_pos_x, index_0_icon_pos_y, 0);
					}
					else {
						al_draw_bitmap(computerSystemList[pokeIdx].icon[1], index_0_icon_pos_x, index_0_icon_pos_y, 0);
					}
					if (pokeIconIdx == 8) {
						pokeIconIdx = 0;
					}
				}
				else
					al_draw_bitmap(computerSystemList[pokeIdx].icon[0], index_0_icon_pos_x, index_0_icon_pos_y, 0);
			}
		}
	}
	// 컴퓨터 시스템이 아닌 경우 메뉴 텍스트 출력
	else {
		// 메시지 출력
		for (int mChar = 0; mChar < menu_status.maxMenuIndex; mChar++)
			al_draw_text(get_menuPirnt_font(), al_map_rgb(90, 90, 90), thumbX + 15 * GAME_SCALE, menuY + 8 * GAME_SCALE + (43 * mChar), ALLEGRO_ALIGN_LEFT, mapMenuChar[menuId][mChar]);
		
		// 플레이어 골드 출력
		if (menuId == ITEM_MARKET_LIST_00 || menuId == ITEM_MARKET_LIST_01) {
			menuId = PLAYER_GOLD_MENU;
			thumbX = camera_position_x + 16;
			menuY = camera_position_y + 16;

			menuCol = mapMenu[menuId][1];
			menuRow = mapMenu[menuId][2];

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

			// 골드 출력
			al_draw_text(get_menuPirnt_font(), al_map_rgb(90, 90, 90), thumbX + 8 * GAME_SCALE, menuY + 8 * GAME_SCALE, ALLEGRO_ALIGN_LEFT, mapMenuChar[menuId][0]);
			char goldtxt[255] = { 0 };
			sprintf_s(goldtxt, sizeof(goldtxt), "%d", user_player.iGold);
			al_draw_text(get_menuPirnt_font(), al_map_rgb(90, 90, 90), thumbX + 8 * GAME_SCALE, menuY + 8 * GAME_SCALE + 43, ALLEGRO_ALIGN_LEFT, goldtxt);
		}
		// 선택 화살표
		al_draw_tinted_scaled_rotated_bitmap_region(menuBitmap, 0, 21, 6, 8, al_map_rgb(255, 255, 255), 0, 0, thumbX + 7 * GAME_SCALE, menuY + 8 * GAME_SCALE + (43 * menu_status.menuIndex), GAME_SCALE, GAME_SCALE, 0, 0);
	}
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
			catchingPokemon(createPokemon(POKEMON_Bulbasaur, 5));
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
			catchingPokemon(createPokemon(POKEMON_Charmander, 5));
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
			catchingPokemon(createPokemon(POKEMON_Squirtle, 5));
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
	case ITEM_MARKET_LIST_00:
	case ITEM_MARKET_LIST_01:
	{
		inventoryItem* item = &inventorySlots[menu_status.currentMenu - ITEM_MARKET_LIST_00][menu_status.menuIndex];
		if (user_player.iGold >= item->itemPrice) {
			item->itemStock++;
			user_player.iGold -= item->itemPrice;
			printf("gold:%d\n", user_player.iGold);
			//closeMenu();
			//closeConversation();
			//closePokemonThumb();
		}
		else {
			conversation_status.currentConvs = ITEM_BUY_FAIL_CONVERSATION;
			conversation_status.maxIndex = 2;
		}
		break;
	}
	case COMPUTER_SYSTEM_POPUP:
		switch (menu_status.menuIndex) {
		case 0:
			menu_status.currentMenu = COMPUTER_SYSTEM_MENU_RELEASE;
			menu_status.menuIndex = 0;
			break;
		case 1:
			menu_status.currentMenu = COMPUTER_SYSTEM_MENU_TAKE;
			menu_status.menuIndex = 0;
			break;
		case 2:
			printf("CCC\n");
			break;
		case 3:
			closeMenu();
			break;
		}
		break;
	case COMPUTER_SYSTEM_MENU_RELEASE:
		printf("selected Pokemon:%s\n", computerSystemList[menu_status.menuIndex].displayName);
		computerSystemList[menu_status.menuIndex].no = -1;
		for (int i = 0; i < 34; i++) {
			if (computerSystemList[i].no == -1) {
				computerSystemList[i] = computerSystemList[i + 1];
				computerSystemList[i + 1].no = -1;
			}
		}
		//menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
		//menu_status.menuIndex = 0;
		break;
	case COMPUTER_SYSTEM_MENU_TAKE:
		printf("selected Pokemon:%s\n", computerSystemList[menu_status.menuIndex].displayName);
		break;
	break;
	}
}