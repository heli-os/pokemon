#include "conversation.h"

extern conversationStatus conversation_status;
extern float camera_position_x;
extern float camera_position_y;
extern ALLEGRO_FONT* get_convsPirnt_font();

void showConversation(int convsId) {
	if (convsId == -1) return;

	int col = 0, row = 0;
	ALLEGRO_BITMAP* convBitmap = al_clone_bitmap(menuFrame);
	al_convert_mask_to_alpha(convBitmap, al_map_rgb(112, 200, 160));

	int convsX = camera_position_x + 2 * GAME_SCALE;
	int convsY = camera_position_y + (GAME_HEIGHT - 42*GAME_SCALE) - 2 * GAME_SCALE;

	int menuCol = 26;
	int menuRow = 4;


	// 상단
	al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 0, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX, convsY, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < menuCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 7, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 14, 0, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY, GAME_SCALE, GAME_SCALE, 0, 0);

	// 중단
	for (row = 0; row < menuRow; row++) {
		al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 0, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		for (col = 0; col < menuCol; col++)
			al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 7, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
		al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 14, 7, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	}
	// 하단
	al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 0, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	for (col = 0; col < menuCol; col++)
		al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 7, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(convBitmap, 14, 14, 7, 7, al_map_rgb(255, 255, 255), 0, 0, convsX + (col + 1) * 7 * GAME_SCALE, convsY + (row + 1) * 7 * GAME_SCALE, GAME_SCALE, GAME_SCALE, 0, 0);

	for (int mChar = 0; mChar < conversation_status.maxIndex; mChar++)
		al_draw_text(get_convsPirnt_font(), al_map_rgb(90, 90, 90), convsX + 15 * GAME_SCALE, convsY + 9 * GAME_SCALE + (52 * mChar), ALLEGRO_ALIGN_LEFT, mapConversationChar[convsId][mChar]);

}
void closeConversation() {
	conversation_status.convsOpen = false;
	conversation_status.maxIndex = 0;
	conversation_status.index = 0;
	conversation_status.currentConvs = -1;
}
void conversationHandler() {

}