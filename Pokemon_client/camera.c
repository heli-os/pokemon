#include "cameara.h"
float camera_get_position(char type, float type_pos, int player_idx)
{
	float position = 0.0f;
	switch (type) {
	case 'x':
		position = -(GAME_WIDTH / 2) + (type_pos + (player_idx / 2));
		if (position < 0) position = 0;

		if (position >= (GAME_MAP_WIDTH - (GAME_WIDTH)))
			position = GAME_MAP_WIDTH - (GAME_WIDTH);
		break;
	case 'y':
		position = -(GAME_HEIGHT / 2) + (type_pos + (player_idx / 2));
		if (position < 0) position = 0;

		if (position >= (GAME_MAP_HEIGHT - (GAME_HEIGHT)))
			position = GAME_MAP_HEIGHT - (GAME_HEIGHT);
		break;
	}

	return position;
}

void transformScreen() {
	al_set_target_bitmap(world_map);

	for (float alpha = 1.0; alpha > 0.0; alpha -= 0.1)
	{
		al_draw_filled_rectangle(55, 55, 60, 60, al_map_rgb(255, 0, 0));
		al_draw_filled_rectangle(50, 50, 100, 100, al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha));
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_rest(0.1);
	}
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}