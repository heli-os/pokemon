#include "collision.h"
void createCollision(collisionBox* colBox, int iPosX, int iPosY, int iWidth, int iHeight) {
	colBox->sx     = iPosX;
	colBox->sy	   = iPosY;
	colBox->width  = iWidth;
	colBox->height = iHeight;
}
void initCollision() {
	const int colBoxLength = sizeof(colBoxArray)/4/sizeof(int);

	colBoxes = (collisionBox*)malloc(sizeof(collisionBox) * colBoxLength);

	if (colBoxes == NULL)
		return;

	int i;
	for(i=0;i< colBoxLength;i++)
		createCollision(&colBoxes[i], colBoxArray[i][0], colBoxArray[i][1], colBoxArray[i][2], colBoxArray[i][3]);

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
		int pw = PLAYER_WIDTH  * GAME_SCALE;
		int ph = PLAYER_HEIGHT * GAME_SCALE;

		int ox = colBoxes[i].sx - pw/2;
		int oy = colBoxes[i].sy - ph/2 ;
		int ow = colBoxes[i].width + pw;
		int oh = colBoxes[i].height + ph;
		
		//printf("%d,%d,%d,%d\n%d,%d,%d,%d\n", px, py, pw, ph, ox, oy, ow, oh);
		
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

bool isHit(player_status _player, player_status user_list[], int player_idx) {
	int i;
	for (i = 0; i < player_idx; i++) {
		if (strcmp(_player.cName, user_list[i].cName) == 0) continue;

		int px = _player.iPos_x;
		int py = _player.iPos_y;
		int pw = PLAYER_WIDTH * GAME_SCALE;
		int ph = PLAYER_HEIGHT * GAME_SCALE;
		
		int ox = user_list[i].iPos_x;
		int oy = user_list[i].iPos_y;
		int ow = PLAYER_WIDTH * GAME_SCALE;
		int oh = PLAYER_HEIGHT * GAME_SCALE;
		 
		printf("%d,%d::%d,%d\n", px,py,ox,oy);

		const int attackRange = 4;
		switch (_player.iPlayer_direction) {
		case  CHARACTER_DOWN:
			py -= attackRange;
			break;
		case  CHARACTER_RIGHT:
			px += 10;
			break;
		case CHARACTER_UP:
			py += attackRange;
			break;
		case CHARACTER_LEFT:
			px -= attackRange;
			break;
		}
		printf("%d,%d::%d,%d\n", px, py, ox, oy);

		// 1. CARACTER_RIGHT 기준 약식 알고리즘.
		if ((px<ox+ow)&&
			(px+pw>ox)&&
			(py<oy+oh)&&
			(py+ph>oy))
		{
			user_list[i].iHp -= 5;
			sendPlayerStatus("PLAYER", user_list[i]);
			return true;
		}
	}
	return false;
}