#include "nginx_framework.h"


void update()
{
	if (is_key_down(ALLEGRO_KEY_ESCAPE)) {
		quit();
	}
}

void render()
{
	al_draw_textf(get_default_font(), al_map_rgb(rand()%256, rand() % 256, rand() % 256), al_get_display_width(al_get_current_display())/2.0, al_get_display_height(al_get_current_display())/2.0,ALLEGRO_ALIGN_CENTER,"Hello World");
}

int main(int argc, char* argv[])
{
	// must be called first!
	init_framework("nginx", 640, 480, false);

	// the game loop runs until we call quit()
	run_game_loop(update, render);

	return 0;
}