#include "conversation.h"
#include "book.h"
#include "screen.h"
#include "battle.h"
#include "catching.h"

extern conversationStatus conversation_status;
extern pokemonMenuStatus pokemonMenu_status;
extern battleUIStatus battleUI_status;
extern float camera_position_x;
extern float camera_position_y;
extern ALLEGRO_FONT* get_convsPirnt_font();

extern pokemon enemy;

// Conversation을 렌더링하는 함수
void showConversation(int convsId) {
	// ConvsID가 -1이라면 비정상적이므로 렌더링하지 않는다.
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

	// 메시지
	for (int mChar = 0; mChar < conversation_status.maxIndex; mChar++)
		al_draw_text(get_convsPirnt_font(), al_map_rgb(90, 90, 90), convsX + 15 * GAME_SCALE, convsY + 9 * GAME_SCALE + (52 * mChar), ALLEGRO_ALIGN_LEFT, mapConversationChar[convsId][mChar]);

}

// Conversation 닫기
void closeConversation() {
	//if (conversation_status.currentConvs == 5 || conversation_status.currentConvs == 6 || conversation_status.currentConvs == 7)
	//	return;

	conversation_status.convsOpen = false;
	conversation_status.maxIndex = 0;
	conversation_status.index = 0;
	conversation_status.currentConvs = -1;

	// 만약 포켓몬 메뉴가 열려있다면, 포켓몬 메뉴도 닫는다.
	if (pokemonMenu_status.pokemonMenuOpen) {
		pokemonMenu_status.pokemonMenuOpen = false;
		pokemonMenu_status.currentIndex = 0;
	}
}