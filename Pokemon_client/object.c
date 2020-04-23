#include "object.h"
#include "menu.h"
#include "conversation.h"
#include "book.h"

int objectPosition[8][3][5] = {
	{ // 집 2층
		{0}
	},
	{ // 집 1층(1)
		{0}
	},
	{ // 마을(1)
		{0}
	},
	{ // 집1층(2)
		{0}
	},
	{ // 오박사 연구실
		{1,LAB_POKEBALL_0, 524,285, 1},
		{1,LAB_POKEBALL_1, 588,285, 1},
		{1,LAB_POKEBALL_2, 652,285, 1},
	},
	{ // 마을(2)
		{0}
	},
	{ // 체육관
		{0}
	},
	{ // 마을(3)
		{0}
	},

};

extern menuStatus menu_status;
extern conversationStatus conversation_status;
extern pokemonThumbStatus pokemonThumb_status;
void createObject(objectBox* objBox, int objId, int iPosX, int iPosY, int iWidth, int iHeight) {
	objBox->type = objId;
	objBox->sx = iPosX;
	objBox->sy = iPosY;
	objBox->sw = iWidth;
	objBox->sh = iHeight;
}

void initObject(ALLEGRO_BITMAP* object) {
	const int objBoxLength = (sizeof(objectPosition[GAME_STAGE]) / (sizeof(objectPosition[GAME_STAGE][0]) / sizeof(int))) / sizeof(int);

	objBoxes = (objectBox*)malloc(sizeof(objectPosition) * objBoxLength);

	if (objBoxes == NULL)
		return;

	for (int i = 0; i < objBoxLength; i++) {
		if (objectPosition[GAME_STAGE][i][4] == 1) {
			int objectTarget = objectPosition[GAME_STAGE][i][0];
			if (objectTarget == 0)
				continue;

			createObject(&objBoxes[i], objectPosition[GAME_STAGE][i][1], 500 + objectPosition[GAME_STAGE][i][2], 500 + objectPosition[GAME_STAGE][i][3], objectItem[objectTarget][2] * GAME_SCALE, objectItem[objectTarget][3] * GAME_SCALE);

			ALLEGRO_BITMAP* objectBitmap = al_clone_bitmap(object);
			al_convert_mask_to_alpha(objectBitmap, al_map_rgb(0, 128, 0));
			al_draw_tinted_scaled_rotated_bitmap_region(objectBitmap, objectItem[objectTarget][0], objectItem[objectTarget][1], objectItem[objectTarget][2], objectItem[objectTarget][3], al_map_rgb(255, 255, 255), 0, 0, objBoxes[i].sx, objBoxes[i].sy, GAME_SCALE, GAME_SCALE, 0, 0);
		}
	}
}


int isObject(const player _player) {
	const int objBoxLength = (sizeof(objectPosition[GAME_STAGE]) / (sizeof(objectPosition[GAME_STAGE][0]) / sizeof(int))) / sizeof(int);

	int i = 0;
	for (i = 0; i < objBoxLength; i++) {
		int tx = _player.iPos_x;
		int ty = _player.iPos_y;
		int tw = PLAYER_WIDTH * GAME_SCALE;
		int th = PLAYER_HEIGHT * GAME_SCALE;

		switch (_player.iPlayer_direction)
		{
		case CHARACTER_DOWN:
			ty += PLAYER_HEIGHT * GAME_SCALE;
			break;
		case CHARACTER_RIGHT:
			tx += PLAYER_WIDTH * GAME_SCALE;
			break;
		case CHARACTER_UP:
			ty -= PLAYER_HEIGHT * GAME_SCALE / 2;
			break;
		case CHARACTER_LEFT:
			tx -= PLAYER_WIDTH * GAME_SCALE / 2;
			break;
		}

		if (GAME_MODE == GAME_ENV_DEVELOPMENT)
			al_draw_rectangle(tx, ty, tx + tw, ty + th, al_map_rgb(255,0,0), 3);

		int ox = objBoxes[i].sx;
		int oy = objBoxes[i].sy;
		int ow = objBoxes[i].sw;
		int oh = objBoxes[i].sh;
		int ot = objBoxes[i].type;

		if (GAME_MODE == GAME_ENV_DEVELOPMENT)
			al_draw_rectangle(ox, oy, ox + ow, oy + oh, al_map_rgb(110, 110, 110), 3);


		if (!((tx + PLAYER_WIDTH / 2 > ox + ow) ||
			(ty + PLAYER_HEIGHT > oy + oh) ||
			(ox > tx - PLAYER_WIDTH / 2 + tw) ||
			(oy > ty - PLAYER_HEIGHT / 2 + th))) {
			return ot;
		}
	}

	return -1;
}

void interactObject(int objId) {
	switch(objId) {
	case LAB_POKEBALL_0:
		menu_status.currentMenu = POKEBALL_00_MENU;
		menu_status.menuOpen = true;
		
		conversation_status.currentConvs = POKEBALL_00_CONVERSATION;
		conversation_status.maxIndex = 2;
		conversation_status.convsOpen = true;

		pokemonThumb_status.currentThumb = POKEMON_Bulbasaur;
		pokemonThumb_status.thumbOpen = true;
		break;
	case LAB_POKEBALL_1:
		menu_status.currentMenu = POKEBALL_01_MENU;
		menu_status.menuOpen = true;

		conversation_status.currentConvs = POKEBALL_01_CONVERSATION;
		conversation_status.maxIndex = 2;
		conversation_status.convsOpen = true;

		pokemonThumb_status.currentThumb = POKEMON_Charmander;
		pokemonThumb_status.thumbOpen = true;
		break;
	case LAB_POKEBALL_2:
		menu_status.currentMenu = POKEBALL_02_MENU;
		menu_status.menuOpen = true;

		conversation_status.currentConvs = POKEBALL_02_CONVERSATION;
		conversation_status.maxIndex = 2;
		conversation_status.convsOpen = true;

		pokemonThumb_status.currentThumb = POKEMON_Squirtle;
		pokemonThumb_status.thumbOpen = true;
		break;
	}
}