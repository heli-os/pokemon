#include "chat.h"
extern ALLEGRO_FONT* get_default_font();
ALLEGRO_USTR* chatInput;
bool onChat = false;

void showChat(float cx, float cy) {
	if (onChat)
		if (chatInput->slen>0)
			al_draw_ustr(get_default_font(), al_map_rgb(255, 0, 0), cx, cy, 0, chatInput);
}