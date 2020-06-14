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
#include "chat.h"
#include "book.h"
#include "menu.h"
#include "battle.h"
#include "bag.h"
#include "otherUtils.h"
#include "conversation.h"
#include "environment.h"
#include "sound.h"
#include "computer.h"

int GAME_SPEED = 1;
int GAME_STAGE = 0;

// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y
player user_player = { NULL, "PLAYER", 0,1,0,0,false, 820, 868, 0 };
pokemon myPokemonList[6] = {
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0}
};

pokemon gymLeaderPokemonList[6] = {
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0},
	 { -1,"",0,0,0,0,0,0,0,0}
};

menuStatus menu_status = { false, -1, 0 ,0 };
conversationStatus conversation_status = { false, -1, 0,0 };
pokemonThumbStatus pokemonThumb_status = { false, -1 };
pokemonMenuStatus pokemonMenu_status = { false, -1 };
battleUIStatus battleUI_status = { false, false, false, false, false, -1, -1, 0, 0, 1, false , false };
bagUIStatus bagUI_status = { false, false, -1, -1, -1 };

extern ALLEGRO_BITMAP* _map[3] = { NULL };
ALLEGRO_BITMAP* _object = NULL;

pokemon enemy;

extern ALLEGRO_USTR* transferUserNickInput;

extern pokemon pokemonBook[15];
bool loadCompleteFlag = false;
int userNo = -1;
void update() {
	// 일반 메뉴
	if (!bagUI_status.bagUIOpen && !pokemonMenu_status.pokemonMenuOpen && menu_status.menuOpen && conversation_status.currentConvs != ITEM_BUY_FAIL_CONVERSATION) {
		if (is_key_pressed(ALLEGRO_KEY_UP)) {
			// SFX_TALK
			soundHandler(1000);
			// 컴퓨터 시스템에서의 작동
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				if ((menu_status.menuIndex - 7) >= 0 && computerSystemList[menu_status.menuIndex - 7].no != -1) {
					menu_status.menuIndex -= 7;
				}
			}
			// 컴퓨터 시스템 외 메뉴에서의 작동
			else {
				if (menu_status.menuIndex > 0)
					menu_status.menuIndex--;
				else
					menu_status.menuIndex = menu_status.maxMenuIndex - 1;
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_DOWN)) {
			// SFX_TALK
			soundHandler(1000);
			// 컴퓨터 시스템에서의 작동
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				if ((menu_status.menuIndex + 7) < 35 && computerSystemList[menu_status.menuIndex + 7].no != -1) {
					menu_status.menuIndex += 7;
				}
			}
			// 컴퓨터 시스템 외 메뉴에서의 작동
			else {
				if (menu_status.menuIndex < menu_status.maxMenuIndex - 1)
					menu_status.menuIndex++;
				else
					menu_status.menuIndex = 0;
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_LEFT)) {
			soundHandler(1000);
			// 마켓 리스트 0일때의 작동
			if (menu_status.currentMenu == ITEM_MARKET_LIST_00) {
				menu_status.currentMenu = ITEM_MARKET_LIST_01;
				menu_status.menuIndex = 0;
			}
			// 마켓 리스트 1일때의 작동
			else if (menu_status.currentMenu == ITEM_MARKET_LIST_01) {
				menu_status.currentMenu = ITEM_MARKET_LIST_00;
				menu_status.menuIndex = 0;
			}
			// 컴퓨터 시스템에서의 작동
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				if (menu_status.menuIndex % 7 == 0) {
					int tmpIndex = menu_status.menuIndex;
					for (int i = 0; i < 7; i++) {
						if (computerSystemList[tmpIndex + i].no != -1)
							menu_status.menuIndex = tmpIndex + i;
					}
				}
				else {
					menu_status.menuIndex--;
				}
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			soundHandler(1000);
			// 마켓 리스트 0일때의 작동
			if (menu_status.currentMenu == ITEM_MARKET_LIST_00) {
				menu_status.currentMenu = ITEM_MARKET_LIST_01;
				menu_status.menuIndex = 0;
			}
			// 마켓 리스트 1일때의 작동
			else if (menu_status.currentMenu == ITEM_MARKET_LIST_01) {
				menu_status.currentMenu = ITEM_MARKET_LIST_00;
				menu_status.menuIndex = 0;
			}
			// 컴퓨터 시스템에서의 작동
			if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_RELEASE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TAKE || menu_status.currentMenu == COMPUTER_SYSTEM_MENU_TRANSFER) {
				if (menu_status.menuIndex + 1 < 35 && computerSystemList[menu_status.menuIndex + 1].no == -1) {
					menu_status.menuIndex = menu_status.menuIndex / 7 * 7;
				}
				else if ((menu_status.menuIndex + 1) % 7 == 0) {
					menu_status.menuIndex -= 6;
				}
				else {
					menu_status.menuIndex++;
				}
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_Z)) {
			if (menu_status.currentMenu != COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT) {
				// SFX_TALK
				soundHandler(1000);
				menuHandler();
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_TALK
			soundHandler(1000);
			menuHandler();
		}


		if (is_key_pressed(ALLEGRO_KEY_ESCAPE)) {
			// SFX_TALK
			soundHandler(1000);
			switch (menu_status.currentMenu) {
			case COMPUTER_SYSTEM_MENU_RELEASE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 0;
				break;
			case COMPUTER_SYSTEM_MENU_TAKE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 1;
				break;
			case COMPUTER_SYSTEM_MENU_STORE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 2;
				break;
			case COMPUTER_SYSTEM_MENU_TRANSFER:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 3;
				break;
			case COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT:
				menu_status.currentMenu = COMPUTER_SYSTEM_MENU_TRANSFER;
				transferUserNickInput = al_ustr_new("");
				break;
			default:
				closeMenu();
				closeConversation();
				closePokemonThumb();
				break;
			}
		}

		if (is_key_pressed(ALLEGRO_KEY_X)) {
			// SFX_TALK
			soundHandler(1000);
			switch (menu_status.currentMenu) {
			case COMPUTER_SYSTEM_MENU_RELEASE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 0;
				break;
			case COMPUTER_SYSTEM_MENU_TAKE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 1;
				break;
			case COMPUTER_SYSTEM_MENU_STORE:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 2;
				break;
			case COMPUTER_SYSTEM_MENU_TRANSFER:
				menu_status.currentMenu = COMPUTER_SYSTEM_POPUP;
				menu_status.menuIndex = 3;
				break;
			case COMPUTER_SYSTEM_MENU_TRANSFER_NICK_INPUT:
				break;
			default:
				closeMenu();
				closeConversation();
				closePokemonThumb();
				break;
			}
		}
	}
	// 대화창
	else if (conversation_status.convsOpen) {
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER) || is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			if (conversation_status.currentConvs == ITEM_BUY_FAIL_CONVERSATION) {
				conversation_status.currentConvs = ITEM_MARKET_CONVERSATION;
			}
			else {
				if (conversation_status.currentConvs == POKEMON_HEALING_CONVERSATION) {
					soundHandler(GAME_STAGE);
				}
				closeConversation();
			}
		}
	}
	// 포켓몬 메뉴
	else if (pokemonMenu_status.pokemonMenuOpen) {
		if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
			// SFX_TALK
			soundHandler(1000);
			if (pokemonMenu_status.currentIndex > 0) {
				pokemonMenu_status.currentIndex--;
				int lastIdx = -1;
				for (int i = 0; i <= pokemonMenu_status.currentIndex; i++) {
					if (myPokemonList[i].no != -1)
						lastIdx = i;
				}
				pokemonMenu_status.currentIndex = lastIdx;
			}
			else
				pokemonMenu_status.currentIndex = 6;
		}
		if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			// SFX_TALK
			soundHandler(1000);
			if (pokemonMenu_status.currentIndex < 6) {
				pokemonMenu_status.currentIndex++;
				if (myPokemonList[pokemonMenu_status.currentIndex].no == -1)
					pokemonMenu_status.currentIndex = 6;
			}
			else
				pokemonMenu_status.currentIndex = 0;
		}
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_TALK
			soundHandler(1000);
			switch (pokemonMenu_status.currentIndex) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			{
				// 아이템 사용
				if (bagUI_status.bagUIOpen) {
					// SFX_USE_ITEM
					soundHandler(303);
					interactItem(bagUI_status.currentIndex + 3, &myPokemonList[pokemonMenu_status.currentIndex]);
				}
				// 포켓몬 보관 인터랙션
				else if (menu_status.currentMenu == COMPUTER_SYSTEM_MENU_STORE) {
					for (int i = 0; i < 35; i++) {
						if (computerSystemList[i].no == -1) {
							computerSystemList[i] = myPokemonList[pokemonMenu_status.currentIndex];
							myPokemonList[pokemonMenu_status.currentIndex].no = -1;
						}
					}
					for (int i = 0; i < 5; i++) {
						if (myPokemonList[i].no == -1) {
							myPokemonList[i] = myPokemonList[i + 1];
							myPokemonList[i + 1].no = -1;
						}
					}
					environmentSave(userNo, 0);
				}
				else {
					// 배틀, 일반
					if (myPokemonList[pokemonMenu_status.currentIndex].crt_hp == 0)
						break;
					pokemon tmp = myPokemonList[0];
					myPokemonList[0] = myPokemonList[pokemonMenu_status.currentIndex];
					myPokemonList[pokemonMenu_status.currentIndex] = tmp;
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
				// 포켓몬 포획 성공
				if (battleUI_status.currentMenu == 11) {
					soundHandler(GAME_STAGE);
					catchingPokemon(enemy);
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
					if (remainPokemon()) {
						soundHandler(GAME_STAGE);
						fadeOut(0.05);
						fadeIn(0.05);
					}
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
				// 플레이어 공격 종료 및 적 포켓몬 사망 확인
				else if (battleUI_status.currentMenu == 6) {
					if (isDead(&enemy)) {
						battleUI_status.battleUISkill = false;
						battleUI_status.currentMenu = 0;
						battleUI_status.currentIndex = 0;
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
							if (!gymLeaderRemainPokemon()) {
								printf("WINN!!!!!\n");
								user_player.iGold += 7500;
								if (user_player.iGold > 1000000) user_player.iGold = 1000000;
								printf("GOLD:%d\n", user_player.iGold);
								battleUI_status.battleUIEnd = true;
							}
						}
						else {
							int pokemon_grade = enemy.no == 14 ? 3 : ((enemy.no == 1) || (enemy.no == 4) || (enemy.no == 7)) ? 2 : 1;
							user_player.iGold += 500 * pokemon_grade;
							if (user_player.iGold > 1000000) user_player.iGold = 1000000;
							printf("GOLD:%d\n", user_player.iGold);

							battleUI_status.battleUIEnd = true;
						}
					}
					else {
						CPUattackProcess();
						battleUI_status.battleUIConv = true;
						battleUI_status.currentMenu = 7;
						battleUI_status.currentIndex = 0;
					}
				}
				// 플레이어 포켓몬 사망 확인
				else if (battleUI_status.currentMenu == 7) {
					if (isDead(&myPokemonList[battleUI_status.currentPokemonIdx])) {
						if (remainPokemon()) {
							/*battleUI_status.battleUISkill = false;*/
							pokemonMenu_status.pokemonMenuOpen = true;
							pokemonMenu_status.currentIndex = 0;
							battleUI_status.currentMenu = 3;
						}
						else {
							battleUI_status.battleUIEnd = true;
							battleUI_status.battleUISkill = false;
							battleUI_status.currentMenu = 0;
							battleUI_status.currentIndex = 0;

						}
					}
					else {
						battleUI_status.battleUISkill = false;
						battleUI_status.currentMenu = 0;
						battleUI_status.currentIndex = 0;
					}
				}
				else {
					battleUI_status.currentIndex = battleUI_status.currentMenu - 1;
					battleUI_status.currentMenu = 0;
				}
			}
		}
		// 스킬 선택 메뉴
		else if (battleUI_status.battleUISkill) {
			if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex > 0 && myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex - 1].own == true)
					battleUI_status.currentIndex--;
				else {
					for (int i = 3; i >= 1; i--) {
						if (myPokemonList[battleUI_status.currentPokemonIdx].skill[i].own == true) {
							battleUI_status.currentIndex = i;
							break;
						}
					}
				}
			}
			if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex < 3 && myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex + 1].own == true)
					battleUI_status.currentIndex++;
				else
					battleUI_status.currentIndex = 0;
			}

			// 스킬 선택
			if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
				// SFX_TALK
				soundHandler(1000);
				pokemonSkill* attackerSkill = &myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex];
				if (attackerSkill->crt_pp > 0) {
					attackProcess(&myPokemonList[battleUI_status.currentPokemonIdx], &enemy, attackerSkill);
					printf("AFTER ATTACK PROCESS:: ENEMY HP:%d\n", enemy.crt_hp);
					printf("select Skill's displayName : %s\n", myPokemonList[battleUI_status.currentPokemonIdx].skill[battleUI_status.currentIndex].displayName);
					battleUI_status.battleUIConv = true;
					battleUI_status.currentMenu = 6;
					battleUI_status.currentIndex = 0;
				}
			}

			if (is_key_pressed(ALLEGRO_KEY_X) || is_key_pressed(ALLEGRO_KEY_ESCAPE)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.battleUISkill = false;
				battleUI_status.currentMenu = 0;
				battleUI_status.currentIndex = 0;
			}
		}
		// 배틀 종료
		else if (battleUI_status.battleUIEnd) {
			battleUI_status.battleUIEnd = false;
			battleUI_status.battleUIConv = true;
			battleUI_status.currentMenu = 5;
		}
		// 그 외
		else {
			if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex > 0)
					battleUI_status.currentIndex--;
				else
					battleUI_status.currentIndex = 3;
			}
			if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
				// SFX_TALK
				soundHandler(1000);
				if (battleUI_status.currentIndex < 3)
					battleUI_status.currentIndex++;
				else
					battleUI_status.currentIndex = 0;
			}
			if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.currentMenu = battleUI_status.currentIndex + 1;
				switch (battleUI_status.currentMenu) {
				case 1:
					battleUI_status.battleUISkill = true;
					battleUI_status.currentIndex = 0;
					break;
				case 2:
					bagUI_status.bagUIOpen = true;
					bagUI_status.currentMenu = 0;
					bagUI_status.currentIndex = 0;
					bagUI_status.lastIndex = 5;
					break;
				case 3:
					pokemonMenu_status.pokemonMenuOpen = true;
					pokemonMenu_status.currentIndex = 0;
					break;
				case 4:
					battleUI_status.battleUIConv = true;
					break;
				}
			}
			if (battleUI_status.currentMenu != -1 && is_key_pressed(ALLEGRO_KEY_X)) {
				// SFX_TALK
				soundHandler(1000);
				battleUI_status.currentMenu = 0;
				battleUI_status.currentIndex = 0;
			}
		}
	}
	// 기타(아무것도 안함)
	else {
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE))
			quit();
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
		if (is_key_pressed(ALLEGRO_KEY_ENTER)) {
			// SFX_OPEN_MENU
			soundHandler(301);
			menu_status.currentMenu = GLOBAL_MENU;
			menu_status.menuOpen = true;
		}
	}


	if (user_player.bMoveFlag) {
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

		if (user_player.iAction_idx >= 16)
		{
			user_player.iAction_type = 0;
			user_player.iAction_idx = 0;
			user_player.iAction_mode = user_player.iAction_mode == 1 ? 2 : 1;

			int stageChanges = isPortal(user_player);
			if (stageChanges != -4) {
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
			}

			if (GAME_STAGE == 2 || GAME_STAGE == 5 || GAME_STAGE == 7) {
				int bushJoins = isBush(user_player);
				if (bushJoins != -4) {
					printf("Bush IN\n");
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
					else {
						// 101: 임시로 사용하는 배틀 페이즈(WILD) 식별자
						soundHandler(101);
						double randItem = ((double)rand() / RAND_MAX * 1.0);
						if (randItem <= TOTAL_APPEAR_RATE) {
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
							levelRange /= myPokemonCnt;
							levelRange = rand() % 5 + levelRange - 3;
							if (levelRange < 5) levelRange = 5;
							enemy = createPokemon(battleUI_status.enemyPokemonIdx, levelRange);
							showBattleUI();
							fadeIn(0.03);
							clear_key_buffered();
						}
					}
				}
			}
			user_player.bMoveFlag = false;

			sendPlayerStatus("PLAYER", user_player);
		}
	}

	updateCamera(user_player);


	//showChat(camera_position_x, camera_position_y + (GAME_HEIGHT - 120));
}

int move_tick = 0;
void render() {
	al_draw_bitmap(world_map, 0, 0, 0);
	switch (user_player.iAction_type)
	{
	case 0:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_mode, user_player.iAction_idx);
		break;
	case 1:
		movement_character(user_player._player, user_player.iPos_x, user_player.iPos_y, user_player.iPlayer_direction, user_player.iAction_mode, user_player.iAction_idx / 8);
		break;
	}
	showMenu(menu_status.currentMenu);
	showBattleUI();
	drawBagUI();

	showPokemonMenu();

	showConversation(conversation_status.currentConvs);
	showPokemonThumb(pokemonThumb_status.currentThumb);

	//al_draw_tinted_scaled_rotated_bitmap_region(objectBitmap, 0, 0, 102, 73, al_map_rgb(255, 255, 255), 0, 0, /*screenWidth/2-88*GAME_SCALE*/500, /*screenHeight / 2 - 72 * GAME_SCALE*/500, GAME_SCALE, GAME_SCALE, 0, 0);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		exit(1);
	}

	userNo = atoi(argv[1]);
	srand((unsigned int)time(NULL));
	//gets_s(user_player.cName, sizeof(user_player.cName));
	bind_sock_clnt();

	// must be called first!l
	init_framework("Pokemon By JupiterFlow.com", GAME_WIDTH, GAME_HEIGHT, false);

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

	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);


	initPokemonThumb();
	initPokemonSkill();
	initComputerSystemList();
	initSound();

	// 세이브 파일 로드
	environmentLoad(userNo);
	//GAME_STAGE = 4;
	while (!loadCompleteFlag) {}

	soundHandler(GAME_STAGE);

	init_terrain(_map[mapOffset[GAME_STAGE][0]]);
	initCollision();

	/*
	포켓몬 6마리 임시 생성
	*/
	//for (int i = 0; i < 6; i++)
	//	myPokemonList[i].no = -1;
	//myPokemonList[0] = createPokemon(5, 65);
	//myPokemonList[1] = createPokemon(2, 65);
	//myPokemonList[2] = createPokemon(8, 65);
	//myPokemonList[3] = createPokemon(11, 65);
	//myPokemonList[4] = createPokemon(12, 65);
	//myPokemonList[5] = createPokemon(14,65);


	// the game loop runs until we call quit()
	run_game_loop(update, render);
	return 0;
}