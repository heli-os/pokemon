#include "my_awesome_system.h"

int main()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* display = al_create_display(3000, 2000);

	ALLEGRO_FONT* _font =  al_load_ttf_font("fonts/Roboto-Medium.ttf",50, ALLEGRO_TTF_NO_KERNING);
	ALLEGRO_COLOR _color = al_map_rgb(255, 0, 0);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_textf(_font, _color, al_get_display_width(display) / 2, al_get_display_height(display) / 2, ALLEGRO_ALIGN_CENTRE, "Hello World");
	al_destroy_font(_font);

	al_flip_display();

	while (1)
	{
		printf("A");
	}
	al_rest(5.0);
		
	return 0;
}

