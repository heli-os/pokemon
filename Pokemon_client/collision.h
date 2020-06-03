﻿#ifndef _POKEMON_COLLISION_HEADER_
#define _POKEMON_COLLISION_HEADER_
#include "nginx_common.h"
#include "player.h"

//    sx,   sy, width, height
// X좌표, Y좌표, 너비, 높이
// 기준 선분에서
// 좌-우 : 좌(8px) 우(8px)
// 상-하 : 상() 하()
// 가로 한칸 16px
// 세로 한칸 16px
static int colBoxArray[][26][4] = {
	{ // 집 2층
		{0,0,176,32},
		{0,0,1,144},
		{175,0,1,144},
		{0,142,176,2},
		{79,62,18,34},
		{111,31,2,31},
		{111,56,34,8}
	},
	{ // 집 1층(1)
		{0,0,176,32},
		{0,0,1,144},
		{175,0,1,144},
		{0,142,48,2},
		{64,142,112,2},
		{79,62,34,34},
		{159,47,16,1},
		{0,94,17,34}
	},
	{ // 마을(1)
		{0,43,384,1},
		{32,41,1,600},
		{351,41,1,600},
		{32,202,161,98},
		{223,202,161,98},
		{32,570,65,64},
		{287,570,65,64},
		{96,586,190,1},
		{111,538,66,48},
		{207,522,98,16},
		{79,442,82,18},
		//건물 시작(주인공 집)
		{223,314,17,82},
		{239,314,17,17},
		{255,314,50,82},
		//건물 끝(주인공 집)
		{207,378,18,18},
		{79,490,18,18},
		//건물 시작(오박사 집)
		{207,410,114,14},
		{207,424,48,68},
		{273,424,48,68},
		//건물 끝(오박사 집)
		//건물 시작(체육관)
		{48,300,49,48},
		{111,300,50,48},
		{79,348,18,16},
		{111,348,18,16},
		{32,348,17,16},
		//건물 끝(체육관)
		//언덕
		{32,122,65,18},
		{143,122,209,18}
	},
	{ // 집 1층(2)
		{0,0,176,32},
		{0,0,1,144},
		{175,0,1,144},
		{0,142,48,2},
		{64,142,112,2},
		{79,62,34,34},
		{159,47,16,1},
		{0,94,17,34}
	},
	{ // 오박사 연구실
		{0,31,210,1},
		{0,31,1,176},
		{207,31,1,176},
		{0,206,90,1},
		{118,206,90,1},
		{127,62,50,18},
		{0,110,81,34},
		{127,110,81,34}
	},
	{ // 마을(2)
		{0,43,384,1},
		{32,41,1,600},
		{351,41,1,600},
		{32,202,161,98},
		{223,202,161,98},
		{32,570,65,64},
		{287,570,65,64},
		{96,586,190,1},
		{111,538,66,48},
		{207,522,98,16},
		{79,442,82,18},
		//건물 시작(주인공 집)
		{223,314,17,82},
		{239,314,17,17},
		{255,314,50,82},
		//건물 끝(주인공 집)
		{207,378,18,18},
		{79,490,18,18},
		//건물 시작(오박사 집)
		{207,410,114,14},
		{207,424,48,68},
		{273,424,48,68},
		//건물 끝(오박사 집)
		//건물 시작(체육관)
		{48,300,49,48},
		{111,300,50,48},
		{79,348,18,16},
		{111,348,18,16},
		{32,348,17,16},
		//건물 끝(체육관)
		//언덕
		{32,122,65,18},
		{143,122,209,18}
	},
	{ // 체육관
		{32,50,184,1},
		{32,50,1,192},
		{207,50,1,192},
		{32, 241,76,1},
		{132, 241,76,1},
		{111, 81, 18, 18}
	},
	{ // 마을(3)
		{0,43,384,1},
		{32,41,1,600},
		{351,41,1,600},
		{32,202,161,98},
		{223,202,161,98},
		{32,570,65,64},
		{287,570,65,64},
		{96,586,190,1},
		{111,538,66,48},
		{207,522,98,16},
		{79,442,82,18},
		//건물 시작(주인공 집)
		{223,314,17,82},
		{239,314,17,17},
		{255,314,50,82},
		//건물 끝(주인공 집)
		{207,378,18,18},
		{79,490,18,18},
		//건물 시작(오박사 집)
		{207,410,114,14},
		{207,424,48,68},
		{273,424,48,68},
		//건물 끝(오박사 집)
		//건물 시작(체육관)
		{48,300,49,48},
		{111,300,50,48},
		{79,348,18,16},
		{111,348,18,16},
		{32,348,17,16},
		//건물 끝(체육관)
		//언덕
		{32,122,65,18},
		{143,122,209,18}
	}
};

typedef struct _COLLISION_BOX {
	int sx;
	int sy;
	int width;
	int height;
}collisionBox;
static collisionBox* colBoxes = NULL;

bool isCollision(player _player);
void createCollision(collisionBox* colBox, int iPosX, int iPosY, int iWidth, int iHeight);
void initCollision();
#endif