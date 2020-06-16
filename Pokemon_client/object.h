#ifndef _POKEMON_OBJECT_HEADER_
#define _POKEMON_OBJECT_HEADER_
#include "nginx_common.h"
#include "player.h"
static int objectItem[][4] = {
	{0},
	// 상처약
	{0,0,17,23},
	// 좋은상처약
	{17,0,17,23},
	// 고급상처약
	{34,0,17,23},
	// 풀회복약
	{51,0,17,23},
	// PP에이드
	{68,0,17,23},
	// 기력의조각
	{85,0,17,23},
	// 포켓몬볼
	{0,23,12,12},
	// 그레이트볼
	{16,23,12,12},
	// 울트라볼
	{32,23,12,12},
	// 마스터볼
	{48,23,12,12},
	// 체육관 관장
	{68, 24, 14, 20}
};

enum OBJECT_ID {
	LAB_POKEBALL_0,			// 연구실 포켓볼_0
	LAB_POKEBALL_1,			// 연구실 포켓볼_1
	LAB_POKEBALL_2,			// 연구실 포켓볼_2
	COMMON_POTION,			// 상처약
	COMMON_SUPER_POTION,	// 좋은 상처약
	COMMON_HYPER_POTION,	// 고급상처약
	COMMON_MAX_POTION,		// 풀회복약
	COMMON_ETHER,			// PP에이드
	COMMON_REVIVE,			// 기력의조각
	COMMON_POKEBALL,		// 포켓몬볼
	COMMON_GREATBALL,		// 그레이트볼
	COMMON_ULTRABALL,		// 울트라볼
	COMMON_MASTERBALL,		// 마스터볼
	GYM_LEADER,				// 체육관 관장
	HEALNG_MACHINE,			// 힐링 머신
	ITEM_MARKET,			// 아이템 마켓
	COMPUTER_SYSTEM,		// 컴퓨터 시스템
};

/*
Object 상태를 저장하는 함수
	int btmId;
	int type;
	int sx;
	int sy;
	int sw;
	int sh;
*/
typedef struct _OBJEECT_BOX {
	int btmId;
	int type;
	int sx;
	int sy;
	int sw;
	int sh;
}objectBox;

static objectBox* objBoxes = NULL;
ALLEGRO_BITMAP* objectBitmap;

/// <summary>
/// Object를 초기화하는 함수
/// </summary>
/// <param name="object"></param>
void initObject(ALLEGRO_BITMAP* object);

/// <summary>
/// 플레이어 앞에 오브젝트가 있는지 여부 확인
/// </summary>
/// <param name="_player"></param>
/// <returns></returns>
int isObject(const player _player);

/// <summary>
/// 오브젝트에 따른 오브젝트 인터랙션을 처리하는 핸들러 함수
/// </summary>
/// <param name="objId"></param>
void interactObject(int objId);
#endif