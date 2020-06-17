#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nginx_framework.h"
#include "sock_client_framework.h"
#include "player.h"
#include "map.h"
#include "catching.h"
#include "object.h"
#include "screen.h"
#include "collision.h"
#include "portal.h"
#include "bush.h"
#include "book.h"
#include "menu.h"
#include "battle.h"
#include "bag.h"
#include "otherUtils.h"
#include "conversation.h"
#include "environment.h"
#include "sound.h"
#include "computer.h"

// 게임 속도와 스테이지를 저장하는 전역 변수
int GAME_SPEED = 1;
int GAME_STAGE = 0;

/// <summary>
/// 플레이어 정보를 저장하는 전역 변수( player 구조체 )
/// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y
/// </summary>
player user_player = { NULL, "PLAYER", 0,1,0,0,false, 820, 868, 0 };

/// <summary>
/// 보유 포켓몬을 저장하는 구조체 배열로 6마리까지 저장한다.
/// </summary>
pokemon myPokemonList[6] = {
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0}
};

/// <summary>
/// 체육관 관장의 포켓몬을 저장하는 구조체 배열로 6마리까지 저장한다.
/// </summary>
pokemon gymLeaderPokemonList[6] = {
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0}
};

/// <summary>
/// 메뉴 상태를 저장하는 전역 변수
/// </summary>
menuStatus menu_status = { false, -1, 0 ,0 };

/// <summary>
/// 하단 대화창 상태를 저장하는 전역 변수
/// </summary>
conversationStatus conversation_status = { false, -1, 0,0 };

/// <summary>
/// 포켓몬 썸네일(최초 포켓몬 획득시) 상태를 저장하는 전역 변수
/// </summary>
pokemonThumbStatus pokemonThumb_status = { false, -1 };

/// <summary>
/// 포켓몬 목록 메뉴 상태를 저장하는 전역 변수
/// </summary>
pokemonMenuStatus pokemonMenu_status = { false, -1 };

/// <summary>
/// 배틀 UI 상태를 저장하는 전역 변수
/// </summary>
battleUIStatus battleUI_status = { false, false, false, false, false, -1, -1, 0, 0, 1, false , false };

/// <summary>
/// 가방 UI 상태를 저장하는 전역 변수
/// </summary>
bagUIStatus bagUI_status = { false, false, -1, -1, -1 };

/// <summary>
/// map.c에 선언된 전역 변수를 가르키는 extern 변수
/// map 배경 이미지를 저장하는 비트맵 배열(집, 마을, 연구실)
/// </summary>
extern ALLEGRO_BITMAP* _map[3] = { NULL };

/// <summary>
/// object 관련 bitmap을 저장하는 비트맵
/// </summary>
ALLEGRO_BITMAP* _object = NULL;

/// <summary>
/// 배틀 중 적의 상태와 비트맵 등을 저장하는 변수
/// </summary>
pokemon enemy;

/// <summary>
/// computer.c에 선언된 전역 변수를 가리키는 extern 변수
/// ALLEGRO5 라이브러리의 USTR(UTF-8 encoded Strings) 타입으로 되어있다.
/// </summary>
extern ALLEGRO_USTR* transferUserNickInput;

/// <summary>
/// book.c에 선언된 전역 변수를 가리키는 extern 변수
/// 15마리의 포켓몬에 대한 고유 정보를 저장하고 있다.
/// </summary>
extern pokemon pokemonBook[15];

/// <summary>
/// LOAD는 비동기적으로 작동하며, 그 작동이 끝나면(sock_client_framework.c 에서 LOAD_COMPLETE 헤더를 수신) flag를 true로 변경한다.
/// </summary>
bool loadCompleteFlag = false;

/// <summary>
/// 유저 식별 고유 번호로 사용되는 userNo를 저장하는 전역 변수
/// </summary>
int userNo = -1;

void update() {
	/*
	일반 메뉴(글로벌 메뉴) 혹은 컴퓨터 시스템일 때 작동하는 인터랙션(4가지 조건을 충족하는 경우)
	1. 가방이 열려있지 않음
	2. 포켓몬 메뉴가 열려있지 않음.
	3. 메뉴가 열려있음
	4. 하단 Conversation이 ITEM 구매 실패 메시지가 아님.(이 경우 메뉴에 대한 인터랙션이 아니라 Conversation에 대한 인터랙션을 진행)
	*/
	if (!bagUI_status.bagUIOpen && !pokemonMenu_status.pokemonMenuOpen && menu_status.menuOpen && conversation_status.currentConvs != ITEM_BUY_FAIL_CONVERSATION) {
		/*
		[일반메뉴]
		방향키 (상)을 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_UP)) {
			// SFX_TALK 사운드 재생
			soundHandler(1000);

			/*
			만약 컴퓨터 시스템 메뉴인 경우
			1. 메뉴 = COMPUTER_SYSTEM_MENU_RELEASE
			2. 메뉴 = COMPUTER_SYSTEM_MENU_TAKE
			3. 메뉴 = COMPUTER_SYSTEM_MENU_TRANSFER
			*/
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				// 한 행에 7마리씩 표현되므로 현재 인덱스 - 7(이전 행)의 인덱스가 유효하며 포켓몬이 존재한다면, 해당 행으로 이동
				if ((menu_status.menuIndex - 7) >= 0 && computerSystemList[menu_status.menuIndex - 7].no != -1) {
					menu_status.menuIndex -= 7;
				}
			}
			// 컴퓨터 시스템 외 메뉴에서의 작동(글로벌 메뉴)
			else {
				// 메뉴 인덱스가 0을 초과한다면 인덱스를 1빼준다.
				if (menu_status.menuIndex > 0)
					menu_status.menuIndex--;
				// 만약 그렇지 않다면 메뉴 인덱스를 최대  인덱스 - 1로 지정해준다. 최대 메뉴 인덱스는 1부터 시작하므로 1을 뺀다.
				else
					menu_status.menuIndex = menu_status.maxMenuIndex - 1;
			}
		}
		/*
		[일반메뉴]
		방향키 (하)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_DOWN)) {
			// SFX_TALK 사운드 재생
			soundHandler(1000);

			/*
			만약 컴퓨터 시스템 메뉴인 경우
			1. 메뉴 = COMPUTER_SYSTEM_MENU_RELEASE
			2. 메뉴 = COMPUTER_SYSTEM_MENU_TAKE
			3. 메뉴 = COMPUTER_SYSTEM_MENU_TRANSFER
			*/
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				// 한 행에 7마리씩 표현되므로 현재 인덱스 + 7(다음 행)의 인덱스가 유효하며 포켓몬이 존재한다면, 해당 행으로 이동
				if ((menu_status.menuIndex + 7) < 35 && computerSystemList[menu_status.menuIndex + 7].no != -1) {
					menu_status.menuIndex += 7;
				}
			}
			// 컴퓨터 시스템 외 메뉴에서의 작동
			else {
				// 메뉴 인덱스가 최대 인덱스 - 1보다 작다면 인덱스를 1 더해준다. 최대 메뉴 인덱스는 1부터 시작하므로 1을 뺀다.
				if (menu_status.menuIndex < menu_status.maxMenuIndex - 1)
					menu_status.menuIndex++;
				// 만약 그렇지 않다면 첫번째 인덱스로 지정해준다.
				else
					menu_status.menuIndex = 0;
			}
		}

		/*
		[일반메뉴]
		방향키 (좌)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_LEFT)) {
			// SFX_TALK 사운드 재생
			soundHandler(1000);

			/*
			현재 메뉴가 회복제 구매 메뉴일 때 작동
			메뉴를 포켓볼 구매 메뉴로 변경
			*/
			if (menu_status.currentMenu == ITEM_MARKET_LIST_00) {
				menu_status.currentMenu = ITEM_MARKET_LIST_01;
				menu_status.menuIndex = 0;
			}
			/*
			현재 메뉴가 포켓볼 구매 메뉴일 때 작동
			메뉴를 회복제 구매 메뉴로 변경
			*/
			else if (menu_status.currentMenu == ITEM_MARKET_LIST_01) {
				menu_status.currentMenu = ITEM_MARKET_LIST_00;
				menu_status.menuIndex = 0;
			}
			// 만약 컴퓨터 시스템 메뉴인 경우
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				/*
				현재 메뉴 인덱스가 행의 첫 번째 요소인 경우(0을 포함한 7의 배수)
				현재 행의 가장 마지막 요소를 선택
				*/
				if (menu_status.menuIndex % 7 == 0) {
					int tmpIndex = menu_status.menuIndex;
					for (int i = 0; i < 7; i++) {
						if (computerSystemList[tmpIndex + i].no != -1)
							menu_status.menuIndex = tmpIndex + i;
					}
				}
				// 첫 번째 요소가 아니라면 이전 요소를 선택
				else {
					menu_status.menuIndex--;
				}
			}
		}

		/*
		[일반메뉴]
		방향키 (우)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			soundHandler(1000);
			/*
			현재 메뉴가 포켓볼 구매 메뉴일 때 작동
			메뉴를 회복제 구매 메뉴로 변경
			*/
			if (menu_status.currentMenu == ITEM_MARKET_LIST_00) {
				menu_status.currentMenu = ITEM_MARKET_LIST_01;
				menu_status.menuIndex = 0;
			}
			/*
			현재 메뉴가 포켓볼 구매 메뉴일 때 작동
			메뉴를 회복제 구매 메뉴로 변경
			*/
			else if (menu_status.currentMenu == ITEM_MARKET_LIST_01) {
				menu_status.currentMenu = ITEM_MARKET_LIST_00;
				menu_status.menuIndex = 0;
			}
			// 만약 컴퓨터 시스템 메뉴인 경우
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				// 현재 행의 다음 요소가 유효하지 않다면, 현재 행의 첫번째 요소를 선택
				if (menu_status.menuIndex + 1 < 35 && computerSystemList[menu_status.menuIndex + 1].no == -1) {
					menu_status.menuIndex = menu_status.menuIndex / 7 * 7;
				}
				// 현재 요소가 마지막 요소라면, 현재 행의 첫번째 요소를 선택
				else if ((menu_status.menuIndex + 1) % 7 == 0) {
					menu_status.menuIndex -= 6;
				}
				// 그렇지 않다면 다음 요소를 선택
				else {
					menu_status.menuIndex++;
				}
			}
		}
		/*
		[일반메뉴]
		키보드 (Z)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_Z)) {
			// 포켓몬 전송을 위한 닉네임을 입력중이라면 무시, 그렇지 않다면 세부 로직 진행
			if (menu_status.currentMenu != COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT) {
				// SFX_TALK
				soundHandler(1000);
				// 메뉴 핸들러 호출(menu.c)
				menuHandler();
			}
		}

		/*
		[일반메뉴]
		키보드 (ENTER)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_TALK
			soundHandler(1000);
			// 메뉴 핸들러 호출(menu.c)
			menuHandler();
		}

		/*
		[일반메뉴]
		키보드 (ESC)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE)) {
			// SFX_TALK
			soundHandler(1000);

			// 현재 메뉴에 따라 다르게 진행한다.
			switch (menu_status.currentMenu) {
				// 컴퓨터 시스템(포켓몬 놓아주기) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_RELEASE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 0;
				break;
				// 컴퓨터 시스템(포켓몬 꺼내기) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_TAKE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 1;
				break;
				// 컴퓨터 시스템(포켓몬 보관) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_STORE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 2;
				break;
				// 컴퓨터 시스템(포켓몬 전송) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_TRANSFER:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 3;
				break;
				// 컴퓨터 시스템(포켓몬 전송 대상 닉네임 입력) 메뉴라면, 메뉴를 컴퓨터 시스템(포켓몬 전송) 메뉴로 변경, 대상 저장 버퍼를 초기화
			case COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT:
				menu_status.currentMenu = COMPUTER_SYSTEM_MENU_TRANSFER;
				transferUserNickInput = al_ustr_new("");
				break;
				// 모두 해당하지 않는다면(현재의 경우 일반 메뉴인 경우) 메뉴, 대화창, 썸네일을 닫는다
			default:
				closeMenu();
				closeConversation();
				closePokemonThumb();
				break;
			}
		}
		/*
		[일반메뉴]
		키보드 (X)를 입력할 경우
		*/
		if (is_key_pressed(ALLEGRO_KEY_X)) {
			// SFX_TALK
			soundHandler(1000);
			// 현재 메뉴에 따라 다르게 진행한다.
			switch (menu_status.currentMenu) {
				// 컴퓨터 시스템(포켓몬 놓아주기) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_RELEASE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 0;
				break;
				// 컴퓨터 시스템(포켓몬 꺼내기) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_TAKE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 1;
				break;
				// 컴퓨터 시스템(포켓몬 보관) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_STORE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 2;
				break;
				// 컴퓨터 시스템(포켓몬 전송) 메뉴라면, 메뉴를 컴퓨터 시스템 초기 팝업 메뉴로 변경
			case COMPUTER_SYSTEM_MENU_TRANSFER:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 3;
				break;
				// 컴퓨터 시스템(포켓몬 전송 대상 닉네임 입력) 메뉴라면, 별다른 인터랙션을 수행하지 않는다.
			case COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT:
				break;
				// 모두 해당하지 않는다면(현재의 경우 일반 메뉴인 경우) 메뉴, 대화창, 썸네일을 닫는다
			default:
				closeMenu();
				closeConversation();
				closePokemonThumb();
				break;
			}
		}
	}
	/*
	[대화창]이 열려있다면
	*/
	else if (conversation_status.convsOpen) {
		// Z, ENTER, ESCAPE, X 입력 시 인터랙션
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER) || is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			// 만약 현재 Conversation이 아이템 구매 실패 Conversation이라면, 아이템 마켓 Conversation으로 변경
			if (conversation_status.currentConvs == ITEM_BUY_FAIL_CONVERSATION) {
				conversation_status.currentConvs = ITEM_MARKET_CONVERSATION;
			}
			// 그렇지 않다면
			else {
				// 만약 포켓몬 회복 Conversation이라면, Dr.Oak's LAB BGM 재생
				if (conversation_status.currentConvs == POKEMON_HEALING_CONVERSATION) {
					soundHandler(GAME_STAGE);
				}
				// 모든 Conversation 다 ㄷ기
				closeConversation();
			}
		}
	}
	/*
	[포켓몬 메뉴]가 열려있다면
	*/
	else if (pokemonMenu_status.pokemonMenuOpen) {
		/*
		[포켓몬 메뉴]
		방향키 (상) 혹은 (좌)를 클릭했다면
		*/
		if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
			// SFX_TALK
			soundHandler(1000);
			// 현재 포켓몬 메뉴 인덱스가 0을 초과한다면
			if (pokemonMenu_status.currentIndex > 0) {
				// 인덱스를 감소시킨다.
				pokemonMenu_status.currentIndex--;
				// 인덱스 0부터 현재 인덱스 중 유효한 인덱스를 검출한다.
				int lastIdx = -1;
				for (int i = 0; i <= pokemonMenu_status.currentIndex; i++) {
					if (myPokemonList[i].no != -1)
						lastIdx = i;
				}
				// 포켓몬 인덱스를 유효한 마지막 인덱스로 변경한다.
				pokemonMenu_status.currentIndex = lastIdx;
			}
			// 아니라면(현재 인덱스가 0이라면) 인덱스를 6으로 변경한다.(Cancel 버튼)
			else
				pokemonMenu_status.currentIndex = 6;
		}
		/*
		[포켓몬 메뉴]
		방향키 (하) 혹은 (우)를 클릭했다면
		*/
		if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			// SFX_TALK
			soundHandler(1000);
			// 현재 포켓몬 메뉴 인덱스가 6 미만이라면
			if (pokemonMenu_status.currentIndex < 6) {
				// 인덱스를 1증가시킨다.
				pokemonMenu_status.currentIndex++;
				// 만약 해당 인덱스가 유효하지 않다면, 마지막 인덱스로 변경한다.(Cancel 버튼)
				if (myPokemonList[pokemonMenu_status.currentIndex].no == -1)
					pokemonMenu_status.currentIndex = 6;
			}
			// 아니라면(현재 인덱스가 6이라면) 인덱스를 0으로 변경한다.(첫번째 포켓몬)
			else
				pokemonMenu_status.currentIndex = 0;
		}

		/*
		[포켓몬 메뉴]
		키보드 (Z) 혹은 (ENTER)를 입력했다면
		*/
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_TALK
			soundHandler(1000);

			// 현재 포켓몬 메뉴 인덱스에 따라 다르게 진행
			switch (pokemonMenu_status.currentIndex) {
				// 0~5라면(포켓몬 영역)
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			{
				/*
				[포켓몬 메뉴]
				가방이 열려있다면 아이템 사용 인터랙션이다.
				*/
				if (bagUI_status.bagUIOpen) {
					// SFX_USE_ITEM 사운드 재생
					soundHandler(303);

					// 아이템 사용에 따른 interactItem 함수 호출(bag.c)
					interactItem(bagUI_status.currentIndex + 3, &myPokemonList[pokemonMenu_status.currentIndex]);
				}
				/*
				[포켓몬 메뉴]
				포켓몬 보관 인터랙션
				*/
				else if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_STORE) {
					/*
					1. 컴퓨터 구조체 배열 전체를 순환
					2. 빈 공간에 포켓몬을 넣는다.
					3. 보유 포켓몬 리스트를 비운다.
					*/
					for (int i = 0; i < 35; i++) {
						if (computerSystemList[i].no == -1) {
							computerSystemList[i] = myPokemonList[pokemonMenu_status.currentIndex];
							myPokemonList[pokemonMenu_status.currentIndex].no = -1;
						}
					}
					// 보유 포켓몬 리스트를 정렬한다.
					for (int i = 0; i < 5; i++) {
						if (myPokemonList[i].no == -1) {
							myPokemonList[i] = myPokemonList[i + 1];
							myPokemonList[i + 1].no = -1;
						}
					}
					// 컴퓨터 시스템 관련 인터랙션이 끝나면 무조건 데이터를 저장한다.
					environmentSave(userNo, 0);
				}
				/*
				[포켓몬 메뉴]
				그 외(배틀 중이거나 일반 포켓몬 메뉴)인 경우 포켓몬을 교체하는 인터랙션이다.
				*/
				else {
					// 선택한 포켓몬의 HP가 0이라면(사망했다면) 입력 취소(break)
					if (myPokemonList[pokemonMenu_status.currentIndex].crt_hp == 0)
						break;
					// 그렇지 않다면 첫 번째 포켓몬과 선택한 포켓몬의 위치를 변경한다.
					pokemon tmp = myPokemonList[0];
					myPokemonList[0] = myPokemonList[pokemonMenu_status.currentIndex];
					myPokemonList[pokemonMenu_status.currentIndex] = tmp;
					// 배틀 메뉴가 열려있다면 포켓몬 메뉴를 닫아 배틀로 전환한다.
					if (battleUI_status.battleUIOpen) {
						closePokemonMenu();
						battleUI_status.currentIndex = 0;
					}
				}
			}
			break;
			case 6:
				if (battleUI_status.battleUISkill)
					break;
				closePokemonMenu();
				break;
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			// SFX_TALK
			soundHandler(1000);
			if (!battleUI_status.battleUISkill)
				closePokemonMenu();
		}
	}
	// 가방 메뉴
	else if (bagUI_status.bagUIOpen) {
		if (is_key_pressed(ALLEGRO_KEY_UP)) {
			// SFX_TALK
			soundHandler(1000);
			if (bagUI_status.currentIndex > 0)
				bagUI_status.currentIndex--;
			else
				bagUI_status.currentIndex = bagUI_status.lastIndex;
		}
		if (is_key_pressed(ALLEGRO_KEY_DOWN)) {
			// SFX_TALK
			soundHandler(1000);
			if (bagUI_status.currentIndex < bagUI_status.lastIndex)
				bagUI_status.currentIndex++;
			else
				bagUI_status.currentIndex = 0;
		}
		if (is_key_pressed(ALLEGRO_KEY_LEFT) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			// SFX_TALK
			soundHandler(1000);
			bagUI_status.currentMenu = bagUI_status.currentMenu == 0 ? 1 : 0;
			bagUI_status.lastIndex = bagUI_status.currentMenu == 0 ? 5 : 3;
			bagUI_status.currentIndex = 0;
		}
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_TALK
			soundHandler(1000);
			interactInventory();
		}
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			// SFX_TALK
			soundHandler(1000);
			closeBagMenu();
		}
	}
	// 배틀메뉴 초기화면(4개 메뉴)
	else if (battleUI_status.battleUIOpen) {
		// Battle Converstation
		if (battleUI_status.battleUIConv) {
			if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER) || is_key_pressed(ALLEGRO_KEY_X)) {
				static int gymLeaderPokemonIdx = 0;
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.battleUIConv = false;
				// 포켓몬 포획에 성공했을 시 currentMenu는 11이 된다.
				if (battleUI_status.currentMenu == 11) {
					// 사운드 핸들러를 호출
					soundHandler(GAME_STAGE);
					// 적 포켓몬을 포획
					catchingPokemon(enemy);
					// 배틀 UI를 닫고 원래 화면으로 전환
					fadeOut(0.05);
					battleUI_status.battleUIOpen = false;
					battleUI_status.currentMenu = -1;
					battleUI_status.currentIndex = -1;
					battleUI_status.currentPokemonIdx = -1;
					battleUI_status.battleUICatching = false;
					battleUI_status.catchingResult = false;
					battleUI_status.catchingIdx = 1;
					fadeIn(0.05);
				}
				// 4 : RUN
				// 5 : 배틀 종료
				else if (battleUI_status.currentMenu == 4 || battleUI_status.currentMenu == 5) {
					battleUI_status.battleUIOpen = false;
					battleUI_status.currentMenu = -1;
					battleUI_status.currentIndex = -1;
					battleUI_status.currentPokemonIdx = -1;
					battleUI_status.battleUICatching = false;
					battleUI_status.catchingResult = false;
					battleUI_status.catchingIdx = 1;
					battleUI_status.battleIsGym = false;
					gymLeaderPokemonIdx = 0;
					// 만약 포켓몬이 남아있다면 승리하거나 도망친것이기에 맵 사운드 핸들러 호출
					if (remainPokemon()) {
						soundHandler(GAME_STAGE);
						fadeOut(0.05);
						fadeIn(0.05);
					}
					// 만약 포켓몬이 모두 사망했다면 패배한 것이기에 Dr.Oak`s LAB으로 이동한다.(포켓몬 회복 유도)
					else {
						GAME_STAGE = 4;

						soundHandler(GAME_STAGE);

						fadeOut(0.05);
						init_terrain(_map[mapOffset[GAME_STAGE][0]]);
						user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
						user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
						updateCamera(user_player);
						fadeIn(0.05);
						clear_key_buffered();
						initCollision();
					}
				}
				/*
				1. 플레이어 공격 종료시 수행
				2. 적 포켓몬 상황 확인
				*/
				else if (battleUI_status.currentMenu == 6) {
					// 만약 적이 사망했다면
					if (isDead(&enemy)) {
						// 배틀을 종료한다.
						battleUI_status.battleUISkill = false;
						battleUI_status.currentMenu = 0;
						battleUI_status.currentIndex = 0;
						// 체육관 관장과의 배틀이라면 관장의 다음 포켓몬을 출전시킨다.
						if (battleUI_status.battleIsGym) {
							gymLeaderPokemonList[gymLeaderPokemonIdx++].crt_hp = 0;
							for (int i = 0; i < 6; i++) {
								printf("HP: %d\n", gymLeaderPokemonList[i].crt_hp);
								if (!isDead(&gymLeaderPokemonList[i])) {
									enemy = gymLeaderPokemonList[i];
									battleUI_status.enemyPokemonIdx = enemy.no - 1;
									break;
								}
							}
							// 체육관 관장의 포켓몬이 모두 사망했다면 골드 증가, 배틀 종료
							if (!gymLeaderRemainPokemon()) {
								printf("WINN!!!!!\n");
								user_player.iGold += 7500;
								if (user_player.iGold > 1000000) user_player.iGold = 1000000;
								printf("GOLD:%d\n", user_player.iGold);
								battleUI_status.battleUIEnd = true;
							}
						}
						// 체육관 관장과의 배틀이 아니라면(야생 배틀) 배틀 즉시 종료
						else {
							int pokemon_grade = enemy.no == 14 ? 3 : ((enemy.no == 1) || (enemy.no == 4) || (enemy.no == 7)) ? 2 : 1;
							user_player.iGold += 500 * pokemon_grade;
							if (user_player.iGold > 1000000) user_player.iGold = 1000000;
							printf("GOLD:%d\n", user_player.iGold);

							battleUI_status.battleUIEnd = true;
						}
					}
					// 적이 사망하지 않았다면 적의 공격 프로세스 수행
					else {
						CPUattackProcess();
						battleUI_status.battleUIConv = true;
						battleUI_status.currentMenu = 7;
						battleUI_status.currentIndex = 0;
					}
				}
				// 적의 공격이 끝났다면(currentMenue = 7)
				else if (battleUI_status.currentMenu == 7) {
					if (isDead(&myPokemonList[battleUI_status.currentPokemonIdx])) {
						// 플레이어의 포켓몬이 사망했고 남은 포켓몬이 있다면 포켓몬 교체 메뉴 Open
						if (remainPokemon()) {
							pokemonMenu_status.pokemonMenuOpen = true;
							pokemonMenu_status.currentIndex = 0;
							battleUI_status.currentMenu = 3;
						}
						// 플레이어의 포켓몬이 사망했고 남은 포켓몬이 없다면 배틀 종료
						else {
							battleUI_status.battleUIEnd = true;
							battleUI_status.battleUISkill = false;
							battleUI_status.currentMenu = 0;
							battleUI_status.currentIndex = 0;

						}
					}
					// 플레이어의 모켓몬이 살아있다면 배틀 정상 진행(스킬 메뉴 선택 초기화)
					else {
						battleUI_status.battleUISkill = false;
						battleUI_status.currentMenu = 0;
						battleUI_status.currentIndex = 0;
					}
				}
				// 그 외에는 초기 메뉴 렌더링
				else {
					battleUI_status.currentIndex = battleUI_status.currentMenu - 1;
					battleUI_status.currentMenu = 0;
				}
			}
		}
		/*
		[스킬 선택 메뉴]
		*/
		else if (battleUI_status.battleUISkill) {
			// 방향키 (상) 혹은 (좌) 입력 시
			if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
				// SFX_TALK
				soundHandler(1000);
				// 인덱스가 유효하며, 이전 스킬 또한 유효하다면 스킬 인덱스를 1 감소
				if (battleUI_status.currentIndex > 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex - 1].own == true)
					battleUI_status.currentIndex--;
				// 그렇지 않다면 유효한 스킬 중 마지막 스킬을 선택
				else {
					for (int i = 3; i >= 1; i--) {
						if (myPokemonList[battleUI_status.currentPokemonIdx].skill[i].own == true) {
							battleUI_status.currentIndex = i;
							break;
						}
					}
				}
			}
			// 방향키 (하) 혹은 (우) 입력 시
			if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
				// SFX_TALK
				soundHandler(1000);
				// 인덱스가 유효하며, 다음 스킬 또한 유요하다면 스킬 인덱스를 1 증가
				if (battleUI_status.currentIndex < 3 && myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex + 1].own == true)
					battleUI_status.currentIndex++;
				// 그렇지 않다면 첫 번째 스킬을 선택
				else
					battleUI_status.currentIndex = 0;
			}

			/*
			[스킬 선택 메뉴]
			키보드 (Z) 혹은 (ENTER) 입력시(스킬 선택시 사용)
			*/
			if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
				// SFX_TALK
				soundHandler(1000);
				// 선택한 스킬을 임시로 복사한다.
				pokemonSkill* attackerSkill = &myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex];
				// 선택한 스킬의 pp가 0이 넘는다면 공격 프로세스 수행
				if (attackerSkill->crt_pp > 0) {
					// attackProcess(battle.c) 호출
					attackProcess(&myPokemonList[battleUI_status.currentPokemonIdx], &enemy, attackerSkill);

					printf("AFTER ATTACK PROCESS:: ENEMY HP:%d\n", enemy.crt_hp);
					printf("select Skill's displayName : %s\n", myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex].displayName);

					// 배틀 Conversation 출력 및 currentMenu를 6으로 수정(플레이어 공격 종료)
					battleUI_status.battleUIConv = true;
					battleUI_status.currentMenu = 6;
					battleUI_status.currentIndex = 0;
				}
			}

			/*
			[스킬 선택 메뉴]
			키보드 (X) 혹은 (ESC) 입력 시 스킬 선택 종료
			*/
			if (is_key_pressed(ALLEGRO_KEY_X) || is_key_pressed(ALLEGRO_KEY_ESCAPE)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.battleUISkill = false;
				battleUI_status.currentMenu = 0;
				battleUI_status.currentIndex = 0;
			}
		}
		// 배틀이 종료 되었을 경우 Conversation을 띄운다.
		else if (battleUI_status.battleUIEnd) {
			battleUI_status.battleUIEnd = false;
			battleUI_status.battleUIConv = true;
			battleUI_status.currentMenu = 5;
		}
		// 그 외
		else {
			// 방향키 (상) 혹은 (좌) 입력시 배틀 메뉴 전환
			if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex > 0)
					battleUI_status.currentIndex--;
				else
					battleUI_status.currentIndex = 3;
			}
			// 방향키 (하) 혹은 (우) 입력시 배틀 메뉴 전환
			if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex < 3)
					battleUI_status.currentIndex++;
				else
					battleUI_status.currentIndex = 0;
			}
			// 키보드 (Z) 혹은 (ENTER) 입력시 배틀 메뉴 선택(스킬, 가방, 포켓몬, 도망)
			if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.currentMenu = battleUI_status.currentIndex + 1;
				switch (battleUI_status.currentMenu) {
				case 1:
					// 스킬 메뉴 선택에 따른 인터랙션
					battleUI_status.battleUISkill = true;
					battleUI_status.currentIndex = 0;
					break;
				case 2:
					// 가방 메뉴 선택에 따른 인터랙션
					bagUI_status.bagUIOpen = true;
					bagUI_status.currentMenu = 0;
					bagUI_status.currentIndex = 0;
					bagUI_status.lastIndex = 5;
					break;
				case 3:
					// 포켓몬 메뉴 선택에 따른 인터랙션
					pokemonMenu_status.pokemonMenuOpen = true;
					pokemonMenu_status.currentIndex = 0;
					break;
				case 4:
					// 도망 메뉴 선택에 따른 인터랙션
					battleUI_status.battleUIConv = true;
					break;
				}
			}
			// 키보드 (X) 입력 시 초기 메뉴 렌더링
			if (battleUI_status.currentMenu != -1 && is_key_pressed(ALLEGRO_KEY_X)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.currentMenu = 0;
				battleUI_status.currentIndex = 0;
			}
		}
	}
	/*
	[플레이어 이동]
	어떠한 메뉴도 열려있지 않을 때
	*/
	else {
		// ESC를 눌렀을 경우 quit() 함수 호출, 클라이언트 종료
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
			quit();

		/*
		[플레이어 이동]
		@@bMoveFlag가 false인 경우@@
		bMoveFlag를 true로 변경
		> 방향키 (하) => 아래쪽으로 이동
		> 방향키 (우) => 우측으로 이동
		> 방향키 (상) => 위쪽으로 이동
		> 방향키 (좌) => 왼쪽으로 이동
		> 키보드 (Z)  => 플레이어 앞에 Object가 있는지 확인, isObject 함수
		*/
		if (user_player.bMoveFlag == false) {
			if (is_key_down(ALLEGRO_KEY_DOWN)) {
				user_player.bMoveFlag = true;
				user_player.iAction_type = 1;
				user_player.iPlayer_direction = CHARACTER_DOWN;
			}
			if (is_key_down(ALLEGRO_KEY_RIGHT)) {
				user_player.bMoveFlag = true;
				user_player.iAction_type = 1;
				user_player.iPlayer_direction = CHARACTER_RIGHT;
			}
			if (is_key_down(ALLEGRO_KEY_UP)) {
				user_player.bMoveFlag = true;
				user_player.iAction_type = 1;
				user_player.iPlayer_direction = CHARACTER_UP;
			}
			if (is_key_down(ALLEGRO_KEY_LEFT)) {
				user_player.bMoveFlag = true;
				user_player.iAction_type = 1;
				user_player.iPlayer_direction = CHARACTER_LEFT;
			}

			if (is_key_pressed(ALLEGRO_KEY_Z)) {
				int objId = isObject(user_player);
				if (objId != -1)
					interactObject(objId);
			}
			//printf("X:%d, Y:%d\n", user_player.iPos_x, user_player.iPos_y);
		}

		/*
		[플레이어 이동]
		키보드 (ENTER) => 글로벌 메뉴 OPEN
		*/
		if (is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_OPEN_MENU
			soundHandler(301);
			menu_status.currentMenu = GLOBAL_MENU;
			menu_status.menuOpen = true;
		}
	}

	/*
	[플레이어 이동]
	만약 bMoveFlag가 true라면, 플레이어 위치를 갱신
	*/
	if (user_player.bMoveFlag) {
		/*
		> 상하좌우 이동
		> 만약 이동한 위치가 접근 불가 위치라면, 이동 위치로 변경
		*/
		user_player.iAction_idx++;
		switch (user_player.iPlayer_direction)
		{
		case CHARACTER_DOWN:
			user_player.iPos_y += GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_y -= GAME_MOVE_TICK * GAME_SCALE;
			break;
		case CHARACTER_RIGHT:
			user_player.iPos_x += GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_x -= GAME_MOVE_TICK * GAME_SCALE;
			break;
		case CHARACTER_UP:
			user_player.iPos_y -= GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_y += GAME_MOVE_TICK * GAME_SCALE;
			break;
		case CHARACTER_LEFT:
			user_player.iPos_x -= GAME_MOVE_TICK * GAME_SCALE;
			if (isCollision(user_player))
				user_player.iPos_x += GAME_MOVE_TICK * GAME_SCALE;
			break;
		}

		/*
		1. 플레이어 이동은 16프레임으로 이루어진다.(iAction_idx)
		2-1. 만약 16 이상이라면, 해당 위치가 portal인지 확인
			> 해당하는 맵으로 이동
		2-2. 만약 16 이상이라면, 해당 위치가 bush인지 확인
			> 포켓몬 출몰(랜덤)
		*/
		if (user_player.iAction_idx >= 16)
		{
			user_player.iAction_type = 0;
			user_player.iAction_idx = 0;
			user_player.iAction_mode = user_player.iAction_mode == 1 ? 2 : 1;

			int stageChanges = isPortal(user_player);
			/*
			isPortal 함수의 반환 값에 따라 인터랙션 처리.
			-4라면 포탈이 아니다. -4가 아니라면 포탈이다.
			*/ 
			if (stageChanges != -4) {
				// 포탈에 대응하는 스테이지로 변환, 이동
				GAME_STAGE = stageChanges;
				printf("main.c->GAME_STAGE%d\n", GAME_STAGE);

				soundHandler(GAME_STAGE);

				fadeOut(0.05);
				init_terrain(_map[mapOffset[GAME_STAGE][0]]);
				user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
				user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
				updateCamera(user_player);
				fadeIn(0.05);
				clear_key_buffered();
				initCollision();
				sendPlayerStatus("PLAYER", user_player);
			}

			// 마을이라면(2,5,7) 부쉬인지 확인한다.
			if (GAME_STAGE == 2 || GAME_STAGE == 5 || GAME_STAGE == 7) {
				int bushJoins = isBush(user_player);
				/*
				isBush 함수의 반환 값에 따라 인터랙션 처리
				-4라면 Bush가 아니다. -4가 아니라면 Bush이다.
				*/
				if (bushJoins != -4) {
					printf("Bush IN\n");
					// 생존 포켓몬이 없다면 Dr.Oak's LAB으로 이동시킨다.
					if (!remainPokemon()) {
						GAME_STAGE = 4;

						soundHandler(GAME_STAGE);

						fadeOut(0.05);
						init_terrain(_map[mapOffset[GAME_STAGE][0]]);
						user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
						user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
						updateCamera(user_player);
						fadeIn(0.05);
						clear_key_buffered();
						initCollision();
					}
					// 생존 포켓몬이 있어 배틀이 가능하다면
					else {
						/*
						> 랜덤 값을 가져와 포켓몬 등장 확률과 비교한다.
							1. 포켓몬 등장 확률 비교
							2-1. 최고 등급 포켓몬 (GRADE_3) 비교
							2-2. 중간 등급 포켓몬 (GRADE_2) 비교
							2-3. 최하 등급 포켓몬 (GRADE_1) 비교
						> 이에 따른 포켓몬 배틀 페이즈 전환.
						*/
						double randItem = ((double)rand() / RAND_MAX * 1.0);
						if (randItem <= TOTAL_APPEAR_RATE) {
							// 101: 임시로 사용하는 배틀 페이즈(WILD) 식별자
							soundHandler(101);
							// HP 회복 임시
							//healingPokemon();

							fadeOut(0.02);
							fadeIn(0.02);
							fadeOut(0.02);
							fadeIn(0.02);
							fadeOut(0.02);

							battleUI_status.battleUIOpen = true;
							battleUI_status.currentMenu = 0;
							battleUI_status.currentIndex = 0;
							battleUI_status.currentPokemonIdx = 0;

							randItem = ((double)rand() / RAND_MAX * 1.0);
							if (randItem <= GRADE_3_APPEAR_RATE) {
								int idxArr[] = { 13 };
								int randIdx = rand() % (sizeof(idxArr) / sizeof(int));
								battleUI_status.enemyPokemonIdx = idxArr[randIdx];
							}
							else if (randItem <= GRADE_3_APPEAR_RATE + GRADE_2_APPEAR_RATE) {
								int idxArr[] = { 0,3,6 };
								int randIdx = rand() % (sizeof(idxArr) / sizeof(int));
								battleUI_status.enemyPokemonIdx = idxArr[randIdx];
							}
							else if (randItem <= GRADE_3_APPEAR_RATE + GRADE_2_APPEAR_RATE + GRADE_1_APPEAR_RATE) {
								int idxArr[] = { 9, 12 };
								int randIdx = rand() % (sizeof(idxArr) / sizeof(int));
								battleUI_status.enemyPokemonIdx = idxArr[randIdx];
							}
							int levelRange = 0;
							int myPokemonCnt = 0;
							for (int i = 0; i < 6; i++) {
								if (myPokemonList[i].no != -1) {
									levelRange += myPokemonList[i].level;
									myPokemonCnt++;
								}
							}
							// 상대 포켓몬 레벨은 플레이어 보유 포켓몬의 (평균 레벨 - 2) ~ (평균 레벨 + 3) 범위에서 등장한다.
							levelRange /= myPokemonCnt;
							levelRange = rand() % 5 + levelRange - 3;
							if (levelRange < 5) levelRange = 5;
							enemy = createPokemon(battleUI_status.enemyPokemonIdx, levelRange);
							isEvolution(&enemy);
							isEvolution(&enemy);
							showBattleUI();
							fadeIn(0.03);
							clear_key_buffered();
						}
					}
				}
			}
			user_player.bMoveFlag = false;
		}
	}

	updateCamera(user_player);
}

int move_tick = 0;
void render() {
	// 배경을 가장 먼저 렌더링한다.
	al_draw_bitmap(world_map, 0, 0, 0);

	/*
	player의 action_type에 따라 다른 인터랙션 수행
	> type==0 then 가만히 있는 상태
	> type==1 then 움직이고 있는 상태
	*/
	switch (user_player.iAction_type)
	{
	case 0:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_mode, user_player.iAction_idx);
		break;
	case 1:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_mode, user_player.iAction_idx / 8);
		break;
	}
	// 메뉴를 출력한다.(내부적으로 메뉴 상태에 따라 처리)
	showMenu(menu_status.currentMenu);
	// 배틀 UI를 출력한다. (내부적으로 배틀 UI 상태에 따라 처리)
	showBattleUI();
	// 가방 UI를 출력한다. (내부적으로 가방 UI 상태에 따라 처리)
	drawBagUI();
	// 포켓몬 메뉴를 출력한다. (내부적으로 포켓몬 메뉴 상태에 따라 처리)
	showPokemonMenu();
	// Conversation을 출력한다. (내부적으로 Coversation 상태에 따라 처리)
	showConversation(conversation_status.currentConvs);
	// Pokemon썸네일을 출력한다. (내부적으로 PokemomThumb 상태에 따라 처리)
	showPokemonThumb(pokemonThumb_status.currentThumb);
}

int main(int argc, char* argv[]) {
	// argument가 없다면 프로그램 종료
	// argument로 GameLauncher로부터 인증 Token을 전달 받는다.
	if (argc != 2) {
		quit();
	}

	// GameLauncher로부터 전달 받은 값은 user 식별코드로 사용된다.
	userNo = atoi(argv[1]);
	srand((unsigned int)time(NULL));

	// 서버 접속
	bind_sock_clnt();

	// 그래픽 프레임워크 초기화
	init_framework("Pokemon By JupiterFlow.com", GAME_WIDTH, GAME_HEIGHT, false);

	/*
	비트맵 초기화
	1. map
	2. menuFrame
	3. pokemonBitmap
	4. pokemonMenuBitmap
	5. user_player
	6. battleUI
	7. bagUI
	8. objectBitmap
	*/
	_map[0] = al_load_bitmap("gfx/Pallet_Town_Interiors.png");
	_map[1] = al_load_bitmap("gfx/Pallet_Town_Full.png");
	_map[2] = al_load_bitmap("gfx/Gym_Inner.png");
	for (int i = 0; i < 3; i++) {
		if (_map[i] == NULL)
			printf("%d _map not load\n", i);
	}
	menuFrame = al_load_bitmap("gfx/MenuFrame.png");
	if (menuFrame == NULL)
		printf("menuFrame not load\n");
	pokemonBitmap = al_load_bitmap("gfx/pokemonBook.png");
	if (pokemonBitmap == NULL)
		printf("pokemonBitmap not load\n");
	pokemonMenuBitmap = al_load_bitmap("gfx/pokemonMenu.png");
	al_convert_mask_to_alpha(pokemonMenuBitmap, al_map_rgb(0, 128, 0));
	if (pokemonMenuBitmap == NULL)
		printf("pokemonMenuBitmap not load\n");
	user_player._player = al_load_bitmap("gfx/Hero&Heroine.png");
	al_convert_mask_to_alpha(user_player._player, al_map_rgb(255, 200, 106));

	battleUIBitmap = al_load_bitmap("gfx/BattleUI.png");
	al_convert_mask_to_alpha(battleUIBitmap, al_map_rgb(163, 73, 164));
	if (battleUIBitmap == NULL)
		printf("battleUIBitmap not load\n");

	bagUIBitmap = al_load_bitmap("gfx/BagUI.png");
	al_convert_mask_to_alpha(bagUIBitmap, al_map_rgb(201, 237, 188));
	if (bagUIBitmap == NULL)
		printf("bagUIBitmap not load\n");

	objectBitmap = al_load_bitmap("gfx/Object.png");
	al_convert_mask_to_alpha(objectBitmap, al_map_rgb(0, 120, 192));
	if (objectBitmap == NULL)
		printf("objectBitmap not load\n");

	// 디버깅용, 스테이지 임의 이동
	//user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
	//user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;

	/*
	각종 요소 초기화
	1. 포켓몬 썸네일
	2. 포켓몬 스킬
	3. 컴퓨터 시스템 리스트
	4. 사운드
	*/
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);
	initPokemonThumb();
	initPokemonSkill();
	initComputerSystemList();
	initSound();

	// 세이브 파일 로드
	environmentLoad(userNo);

	// LOAD_COMPLETE가 수신될 때까지 대기
	while (!loadCompleteFlag) { printf("%s\n", loadCompleteFlag ? "A" : "B"); }

	// 사운드 재생
	soundHandler(GAME_STAGE);

	// 지형 및 충돌 영역 초기화
	init_terrain(_map[mapOffset[GAME_STAGE][0]]);
	initCollision();

	/*
	포켓몬 6마리 임시 생성
	*/
	if (userNo == 1) {
		for (int i = 0; i < 6; i++)
			myPokemonList[i].no = -1;
		myPokemonList[0] = createPokemon(5, 65);
		myPokemonList[1] = createPokemon(2, 65);
		myPokemonList[2] = createPokemon(8, 65);
		myPokemonList[3] = createPokemon(11, 65);
		myPokemonList[4] = createPokemon(12, 65);
		myPokemonList[5] = createPokemon(14, 65);
	}


	// the game loop runs until we call quit()

	// game_loop 수행(update, render는 함수 포인터)
	run_game_loop(update, render);
	return 0;
}