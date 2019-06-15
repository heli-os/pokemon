#include "collision.h"

// Bounding Box(BB) Algorithm
bool isCollision(player_status _player)
{
	int i = 0;
	bool _status = false;
	for (i = 0; i < OBJECT_COUNT; i++) {
		float px = _player.fPos_x;
		float py = _player.fPos_y;
		float pw = PLAYER_WIDTH  * GAME_SCALE;
		float ph = PLAYER_HEIGHT * GAME_SCALE;

		float ox = object_list[i].dx;
		float oy = object_list[i].dy;
		float ow = object_list[i].sw * GAME_SCALE;
		float oh = object_list[i].sh * GAME_SCALE;
		printf("%lf,%lf,%lf,%lf\n%lf,%lf,%lf,%lf\n", px, py, pw, ph, ox, oy, ow, oh);
		if ((px + PLAYER_WIDTH/2 > ox + ow) ||
			(py + PLAYER_HEIGHT > oy + oh) ||
			(ox > px-PLAYER_WIDTH/2 + pw ) ||
			(oy > py-PLAYER_HEIGHT/2 + ph ))
			_status = false;
		else
			return true;
	}
	return _status;
}
