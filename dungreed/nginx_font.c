#include "nginx_font.h"
void init_font() {
	al_init_font_addon();
	al_init_ttf_addon();
	default_font = al_load_ttf_font("fonts/Roboto-Medium.ttf", 50, ALLEGRO_TTF_NO_KERNING);
}

void draw_text(ALLEGRO_COLOR _color,float x, float y,char* msg, int flags) {
	al_draw_textf(default_font, _color, x, y, flags, msg);
	al_flip_display();
}