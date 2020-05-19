#include "bag.h"
#include "battle.h"

extern float camera_position_x;
extern float camera_position_y;

extern bagUIStatus bagUI_status;
void drawBagUI() {
	if (!bagUI_status.bagUIOpen) return;

	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, 0, 0, 240, 160, al_map_rgb(255, 255, 255), 0, 0, camera_position_x, camera_position_y, 3.3333333, GAME_SCALE, 0, 0);

	// 가방 오프셋(X) Y는 163 가로 58 높이 63
	int bagSprite_offsetX = -1;
	// 렌더링 위치
	int bagSprite_posX = 11;
	int bagSprite_posY = 40;

	// 메뉴 오프셋(Y), X는 0으로 고정
	int itemMenuSprite_offsetY = -1;


	switch (bagUI_status.currentMenu) {
	case 0:
		itemMenuSprite_offsetY = 163;
		bagSprite_offsetX = 105;
		break;
	case 1:
		itemMenuSprite_offsetY = 195;
		bagSprite_offsetX = 167;
		break;
	}

	// 가방
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, bagSprite_offsetX, 163, 58, 63, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + bagSprite_posX * 3.3333333, camera_position_y + bagSprite_posY * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);
	
	// 메뉴
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, 0, itemMenuSprite_offsetY, 77, 29, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + 3 * 3.3333333, camera_position_y + 1 * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);

	// 하단 대화창 아이콘 렌더링 위치
	int bottomIcon_posX = 10;
	int bottomIcon_posY = 126;
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, 80, 181, 20, 20, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + bottomIcon_posX * 3.3333333, camera_position_y + bottomIcon_posY * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);

	// 가로 9 세로14
	// 메뉴 좌우 화살표(적색) 오프셋, Y는 163고정
	int redArrow_Left_offsetX = 80;
	int redArrow_Right_offsetX = 92;

	// 메뉴 좌우 화살표(적색) 렌더링 위치, Y는 4 고정
	int redArrow_Left_posX = 3;
	int redArrow_Right_posX = 68;

	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, redArrow_Left_offsetX, 163, 9, 14, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + redArrow_Left_posX * 3.3333333, camera_position_y + 70 * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, redArrow_Right_offsetX, 163, 9, 14, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + redArrow_Right_posX * 3.3333333, camera_position_y + 70 * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);

	// 메뉴 선택 화살표(흑색) 렌더링 위치, X는 90 고정
	int blackArrow_posY = bagUI_status.currentIndex * 15.5 + 13;

	// 메뉴 선택 화살표(흑색) 오프셋 위치
	int blackArrow_offsetX = 81;
	int blackArrow_offsetY = 204;
	al_draw_tinted_scaled_rotated_bitmap_region(bagUIBitmap, blackArrow_offsetX, blackArrow_offsetY, 6, 10, al_map_rgb(255, 255, 255), 0, 0, camera_position_x + 90 * 3.3333333, camera_position_y + blackArrow_posY * GAME_SCALE, 3.3333333, GAME_SCALE, 0, 0);
}

extern battleUIStatus battleUI_status;
void closeBagMenu() {
	if (battleUI_status.battleUIOpen) {
		battleUI_status.battleUIConv = false;
		battleUI_status.currentIndex = battleUI_status.currentMenu - 1;
		battleUI_status.currentMenu = 0;
	}
	bagUI_status.currentIndex = -1;
	bagUI_status.lastIndex = -1;
	bagUI_status.bagUIOpen = false;
}