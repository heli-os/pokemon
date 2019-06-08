#include "cameara.h"
float camera_get_position(char type,float type_pos, int player_idx)
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
