#include "nginx_framework.h"

static ALLEGRO_FONT* default_font;
void init_font();
void draw_text(ALLEGRO_COLOR _color, float x, float y, char* msg, int flags);