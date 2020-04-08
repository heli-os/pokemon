#include "chat.h"
extern ALLEGRO_FONT* get_default_font();
extern ALLEGRO_FONT* get_chatInput_font();
extern ALLEGRO_FONT* get_chatText_font();
ALLEGRO_USTR* chatInput;
char messages[5][256] = { 0, };

bool onChat = false;

void showChat(float cx, float cy) 
{	
	
	if (onChat)
	{
		al_draw_filled_rounded_rectangle(cx,  (onChat?-22:0) + cy, cx + GAME_WIDTH, cy + 120, 5, 5, al_map_rgba(128, 128, 128, 190));
		if (chatInput->slen > 0)
			al_draw_ustr(get_chatInput_font(), al_map_rgb(0, 0, 0), cx, 5+88+cy, 0, chatInput);
	}
	int i;
	for (i = 0; i < 5; i++)
		al_draw_ustr(get_chatText_font(), al_map_rgb(0, 0, 0), cx, (onChat?-22:0)+ 5+ cy +i*22, 0, al_ustr_new(&messages[i][0]));
	
}