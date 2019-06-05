#include "nginx_screen.h"
#include "nginx_font.h"

ALLEGRO_DISPLAY* display;
void init_nginx() {
	al_init();
	create_window(800, 600, ALLEGRO_WINDOWED);
	init_font();
}
int main()
{
	init_nginx();

	draw_text(al_map_rgb(255, 0,0),al_get_display_width(display)/2.0,al_get_display_height(display)/2.0,"Hello World", ALLEGRO_ALIGN_CENTRE);
	

	while (1)
	{
		printf("A");
	}
	al_rest(5.0);

	return 0;
}

