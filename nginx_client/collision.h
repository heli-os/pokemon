#include "nginx_common.h"
#include "player.h"

//    sx,   sy, width, height
// X좌표, Y좌표, 너비, 높이
// 기준 선분에서
// 좌-우 : 좌(8px) 우(8px)
// 상-하 : 상() 하()
static int colBoxArray[][4] =
{
	{0,0,32,288},     //좌상단 나무
	{32,0,1,288},     //좌상단 언덕 좌측 1px
	{270,0,1,288},    //좌상단 언덕 우측 1px
	{32,238,48,50},   //좌상단 언덕 좌측 절벽
	{80,230,1,16},    //좌상단 언덕 좌측 절벽 위 16px
	{112,238,158,50}, //좌상단 언덕 우측 절벽
	{112,230,1,16},   //좌상단 언덕 우측 절벽 위 16px
	
};

typedef struct _COLLISION_BOX {
	int sx;
	int sy;
	int	width;
	int height;
}collisionBox;
static collisionBox* colBoxes = NULL;

bool isCollision(player_status _player);
void createCollision(collisionBox* colBox, int iPosX,int iPosY, int iWidth, int iHeight);
void initCollision();

bool isHit(player_status _player, player_status user_list[], int player_idx);


