#include "nginx_framework.h"
#include "player.h"
#include "map.h"
#include "object.h"
#include "screen.h"
#include "sock_client_framework.h"
#include "collision.h"
#include "portal.h"
#include "bush.h"
#include "chat.h"
#include "book.h"
#include "menu.h"
#include <stdio.h>
#include <time.h>
#include "conversation.h"
#include "environment.h"

int GAME_SPEED = 1;
int GAME_STAGE = 0;

player user_player = { NULL, "", 0,1,0,0,false,0,0 };
pokemon myPokemonList[6] = {
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL },
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL },
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL },
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL },
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL },
	 { -1,"",0,0,0,0,0,0,0, NULL,NULL,NULL }
};

menuStatus menu_status = { false, -1, 0 ,0 };
conversationStatus conversation_status = { false, -1, 0,0 };
pokemonThumbStatus pokemonThumb_status = { false, -1 };
pokemonMenuStatus pokemonMenu_status = { false, -1 };

// player_bitmap*, action_bitmap*, name, action_type, player_direction, action_idx, pos_x, pos_y, hp, armor, buf
extern ALLEGRO_BITMAP* _map[3] = { NULL };
ALLEGRO_BITMAP* _object = NULL;


extern ALLEGRO_USTR* chatInput;
extern bool onChat;


void update()
{
	if (pokemonMenu_status.pokemonMenuOpen) {
		if (is_key_pressed(ALLEGRO_KEY_UP) || is_key_pressed(ALLEGRO_KEY_LEFT)) {
			if (pokemonMenu_status.currentIndex > 0) {
				pokemonMenu_status.currentIndex--;
				if (myPokemonList[pokemonMenu_status.currentIndex].no == -1)
					pokemonMenu_status.currentIndex = 0;
			}
			else
				pokemonMenu_status.currentIndex = 6;
		}
		if (is_key_pressed(ALLEGRO_KEY_DOWN) || is_key_pressed(ALLEGRO_KEY_RIGHT)) {
			if (pokemonMenu_status.currentIndex < 6) {
				pokemonMenu_status.currentIndex++;
				if (myPokemonList[pokemonMenu_status.currentIndex].no == -1)
					pokemonMenu_status.currentIndex = 6;
			}
			else
				pokemonMenu_status.currentIndex = 0;
		}
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
			switch (pokemonMenu_status.currentIndex) {
			case 6:
				closePokemonMenu();
				break;
			}
		}
		if (is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			closePokemonMenu();
		}
	}
	else if (menu_status.menuOpen) {
		if (is_key_pressed(ALLEGRO_KEY_UP)) {
			if (menu_status.menuIndex > 0)
				menu_status.menuIndex--;
			else
				menu_status.menuIndex = menu_status.maxMenuIndex - 1;
		}
		if (is_key_pressed(ALLEGRO_KEY_DOWN)) {
			if (menu_status.menuIndex < menu_status.maxMenuIndex - 1)
				menu_status.menuIndex++;
			else
				menu_status.menuIndex = 0;
		}
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER)) {
			menuHandler();
		}

		if (is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			closeMenu();
			closeConversation();
			closePokemonThumb();
		}
	}
	else if (conversation_status.convsOpen) {
		if (is_key_pressed(ALLEGRO_KEY_Z) || is_key_pressed(ALLEGRO_KEY_ENTER) || is_key_pressed(ALLEGRO_KEY_ESCAPE) || is_key_pressed(ALLEGRO_KEY_X)) {
			closeConversation();
		}
	}
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
		}
		if (is_key_pressed(ALLEGRO_KEY_ENTER)) {
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
				fadeOut();
				init_terrain(_map[mapOffset[GAME_STAGE][0]]);
				user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
				user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
				updateCamera(user_player);
				fadeIn();
				clear_key_buffered();
				initCollision();
			}

			if (GAME_STAGE == 2 || GAME_STAGE == 5) {
				int bushJoins = isBush(user_player);
				if (bushJoins != -4) {
					printf("on bush(ID:%d)\n", bushJoins);
					//fadeOut();

					//init_terrain(_map[mapOffset[GAME_STAGE][0]]);
					//user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
					//user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
					//updateCamera(user_player);

					//fadeIn();
				}
			}
			user_player.bMoveFlag = false;

			sendPlayerStatus("PLAYER", user_player);
		}
	}

	updateCamera(user_player);


	//if (is_key_pressed(ALLEGRO_KEY_ENTER))
	//{
	//	if (onChat && chatInput->slen > 0)
	//	{
	//		const char* txt = al_cstr(chatInput);
	//		json_t* pHeader = json_array();
	//		json_t* pData = json_array();
	//		json_array_append_new(pHeader, json_string("CHAT"));
	//		json_array_append_new(pData, json_string(user_player.cName));
	//		json_array_append_new(pData, json_string(txt));

	//		json_t* pMessage = htonJson(pHeader, pData);

	//		sendMessage(pMessage);
	//		chatInput = al_ustr_new("");
	//	}
	//	onChat = !onChat;
	//}

	//showChat(camera_position_x, camera_position_y + (GAME_HEIGHT - 120));
}

int move_tick = 0;
void render()
{
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
	showConversation(conversation_status.currentConvs);
	showPokemonThumb(pokemonThumb_status.currentThumb);
	showPoekmonMenu();
}

int main(int argc, char* argv[])
{
	//gets_s(user_player.cName, sizeof(user_player.cName));
	bind_sock_clnt();

	// must be called first!l
	init_framework("Pokemon By JupiterFlow.com", GAME_WIDTH, GAME_HEIGHT, false);

	_map[0] = al_load_bitmap("gfx/Pallet_Town_Interiors.png");
	_map[1] = al_load_bitmap("gfx/Pallet_Town_Full.png");
	_map[2] = al_load_bitmap("gfx/Gym_Inner.png");
	for (int i = 0; i < 3; i++)
	{
		if (_map[i] == NULL)
			printf("%d _map not load\n", i);
	}
	menuFrame = al_load_bitmap("gfx/MenuFrame.png");
	if(menuFrame == NULL)
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
	// 디버깅용, 스테이지 임의 이동
	//user_player.iPos_x = mapOffset[GAME_STAGE][1] + mapOffset[GAME_STAGE][7] * GAME_SCALE;
	//user_player.iPos_y = mapOffset[GAME_STAGE][2] + mapOffset[GAME_STAGE][8] * GAME_SCALE - 16;
	
	world_map = al_create_bitmap(GAME_MAP_WIDTH, GAME_MAP_HEIGHT);

	initPokemonThumb();

	environmentLoad();

	init_terrain(_map[mapOffset[GAME_STAGE][0]]);
	initCollision();

	

	sendPlayerStatus("JOIN_GAME", user_player);

	// the game loop runs until we call quit()
	run_game_loop(update, render);
	return 0;
}