#include "nginx_screen.h"
void create_window(int width, int height, int flags) {
	if (!flags)
		al_set_new_display_flags(flags);
	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
}