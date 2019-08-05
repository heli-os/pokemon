#include "collision.h"
void createCollision(collisionBox* colBox, int iPosX, int iPosY, int iWidth, int iHeight) {
	colBox->sx = iPosX;
	colBox->sy = iPosY;
	colBox->width = iWidth;
	colBox->height = iHeight;
}
void initCollision() {
	const int colBoxLength = sizeof(colBoxArray) / 4 / sizeof(int);

	colBoxes = (collisionBox*)malloc(sizeof(collisionBox) * colBoxLength);

	if (colBoxes == NULL)
		return;

	int i;
	for (i = 0; i < colBoxLength; i++)
		createCollision(&colBoxes[i], 500 + colBoxArray[i][0] * GAME_SCALE, 500 + colBoxArray[i][1] * GAME_SCALE, colBoxArray[i][2] * GAME_SCALE, colBoxArray[i][3] * GAME_SCALE);

}

// Bounding Box(BB) Algorithm
bool isCollision(player_status _player)
{

	
	const int colBoxLength = sizeof(colBoxArray) / 4 / sizeof(int);
	
	int i = 0;
	bool _status = false;
	for (i = 0; i < colBoxLength; i++) {
		int px = _player.iPos_x;
		int py = _player.iPos_y;
		int pw = PLAYER_WIDTH * GAME_SCALE;
		int ph = PLAYER_HEIGHT * GAME_SCALE;

		int ox = colBoxes[i].sx;
		int oy = colBoxes[i].sy;
		int ow = colBoxes[i].width;
		int oh = colBoxes[i].height;
		al_draw_rectangle(ox, oy, ox + ow, oy + oh, al_map_rgb(255, 0, 0), 3);

		//printf("%d,%d,%d,%d\n%d,%d,%d,%d\n", px, py, pw, ph, ox, oy, ow, oh);

		if ((px + PLAYER_WIDTH / 2 > ox + ow) ||
			(py + PLAYER_HEIGHT > oy + oh) ||
			(ox > px - PLAYER_WIDTH / 2 + pw) ||
			(oy > py - PLAYER_HEIGHT / 2 + ph))
			_status = false;
		else
			return true;
	}
	
	return _status;
}