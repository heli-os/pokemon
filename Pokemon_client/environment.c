#include "environment.h"
#include "player.h"
#include "book.h"
#include "bag.h"

extern player user_player;
extern int GAME_STAGE;
extern pokemon myPokemonList[6];
extern int objectPosition[8][3][5];
extern pokemon pokemonBook[15];
extern inventoryItem inventorySlots[2][6];
/*
JSON 형태로 저장
저장되어야할 데이터
	1. Player Status
	2. 게임 스테이지
	3. 포켓몬 리스트
	4. 오브젝트 포지션
	5. 인벤토리 슬롯
*/
void environmentSave() {
	// 플레이어 정보 추출
	json_t* playerData = json_object();
	json_object_set_new(playerData, "cName", json_string(user_player.cName));
	json_object_set_new(playerData, "iAction_type", json_integer(user_player.iAction_type));
	json_object_set_new(playerData, "iPlayer_direction", json_integer(user_player.iPlayer_direction));
	json_object_set_new(playerData, "iAction_idx", json_integer(user_player.iAction_idx));
	json_object_set_new(playerData, "iPos_x", json_integer(user_player.iPos_x));
	json_object_set_new(playerData, "iPos_y", json_integer(user_player.iPos_y));

	// myPokemonList 추출
	json_t* pokemonListDataArray = json_array();
	for (int i = 0; i < 6; i++) {
		json_t* pokemonListData = json_object();
		json_object_set_new(pokemonListData, "no", json_integer(myPokemonList[i].no));
		json_object_set_new(pokemonListData, "displayName", json_string(myPokemonList[i].displayName));
		json_object_set_new(pokemonListData, "type", json_integer((long long)myPokemonList[i].type));
		json_object_set_new(pokemonListData, "level", json_integer(myPokemonList[i].level));
		json_object_set_new(pokemonListData, "exp", json_integer(myPokemonList[i].exp));
		json_object_set_new(pokemonListData, "crt_hp", json_integer(myPokemonList[i].crt_hp));
		json_object_set_new(pokemonListData, "max_hp", json_integer(myPokemonList[i].max_hp));
		json_object_set_new(pokemonListData, "dmg", json_integer(myPokemonList[i].dmg));
		json_object_set_new(pokemonListData, "def", json_integer(myPokemonList[i].def));
		json_object_set_new(pokemonListData, "spd", json_integer(myPokemonList[i].spd));

		json_t* pokemonSkillDataArray = json_array();
		for (int j = 0; j < 4; j++) {
			json_t* pokemonSkillData = json_object();
			json_object_set_new(pokemonSkillData, "no", json_integer(myPokemonList[i].skill[j].no));
			json_object_set_new(pokemonSkillData, "displayName", json_string(myPokemonList[i].skill[j].displayName));
			json_object_set_new(pokemonSkillData, "type", json_integer((long long)myPokemonList[i].skill[j].type));
			json_object_set_new(pokemonSkillData, "dmg_cf", json_real(myPokemonList[i].skill[j].dmg_cf));
			json_object_set_new(pokemonSkillData, "acc", json_real(myPokemonList[i].skill[j].acc));
			json_object_set_new(pokemonSkillData, "crt_pp", json_integer(myPokemonList[i].skill[j].crt_pp));
			json_object_set_new(pokemonSkillData, "max_pp", json_integer(myPokemonList[i].skill[j].max_pp));
			json_object_set_new(pokemonSkillData, "level_condition", json_integer(myPokemonList[i].skill[j].level_condition));
			json_object_set_new(pokemonSkillData, "own", json_boolean(myPokemonList[i].skill[j].own));

			json_array_append_new(pokemonSkillDataArray, pokemonSkillData);
		}
		json_object_set_new(pokemonListData, "skill", pokemonSkillDataArray);

		json_array_append_new(pokemonListDataArray, pokemonListData);
	}

	// objectPosition 추출
	int depth_1_index = sizeof(objectPosition) / sizeof(objectPosition[0]);
	int depth_2_index = sizeof(objectPosition[0]) / sizeof(objectPosition[0][0]);
	int depth_3_index = sizeof(objectPosition[0][0]) / sizeof(int);
	json_t* objectPositionDataArray = json_array();
	for (int i = 0; i < depth_1_index; i++) {
		json_t* dept2_DataArray = json_array();
		for (int j = 0; j < depth_2_index; j++) {
			json_t* dept3_DataArray = json_array();
			for (int k = 0; k < depth_3_index; k++) {
				json_array_append_new(dept3_DataArray, json_integer(objectPosition[i][j][k]));
			}
			json_array_append_new(dept2_DataArray, dept3_DataArray);
		}
		json_array_append_new(objectPositionDataArray, dept2_DataArray);
	}

	// inventorySlots 추출
	json_t* inventorySlotsDataArray = json_array();
	for (int i = 0; i < 2; i++) {
		json_t* depth2_DataArray = json_array();
		for (int j = 0; j < 6; j++) {
			json_t* inventorySlotsData = json_object();
			json_object_set_new(inventorySlotsData, "itemType", json_integer(inventorySlots[i][j].itemType));
			json_object_set_new(inventorySlotsData, "itemStock", json_integer(inventorySlots[i][j].itemStock));
			json_object_set_new(inventorySlotsData, "itemName", json_string(inventorySlots[i][j].itemName));
			json_t* itemDescArray = json_array();
			for (int k = 0; k < 3; k++)
				json_array_append_new(itemDescArray, json_string(inventorySlots[i][j].itemDesc[k]));
			json_object_set_new(inventorySlotsData, "itemDesc", itemDescArray);
			json_array_append_new(depth2_DataArray, inventorySlotsData);
		}
		json_array_append_new(inventorySlotsDataArray, depth2_DataArray);
	}

	json_t* pMessage = json_object();
	// 플레이어 정보 저장
	json_object_set_new(pMessage, "PLAYER", playerData);
	// 게임 스테이지 저장
	json_object_set_new(pMessage, "GAME_STAGE", json_integer(GAME_STAGE));
	// pokemonList 저장
	json_object_set_new(pMessage, "POKEMON_LIST", pokemonListDataArray);
	// objectPosition 저장
	json_object_set_new(pMessage, "OBJECT_POSITION", objectPositionDataArray);

	// inventorySlots 저장
	json_object_set_new(pMessage, "INVENTORY_SLOTS", inventorySlotsDataArray);

	int rc = json_dump_file(pMessage, "./profile.pkms", 0);
	if (rc)
		fprintf(stderr, "cannot save json to file\n");
}
void environmentLoad() {
	json_error_t* jerror = NULL;

	json_t* pData = json_load_file("./profile.pkms", 0, jerror);

	json_t* playerData = json_object_get(pData, "PLAYER");
	strcpy_s(user_player.cName, sizeof(user_player.cName), json_string_value(json_object_get(playerData, "cName")));

	user_player.iAction_type = json_integer_value(json_object_get(playerData, "iAction_type"));
	user_player.iPlayer_direction = json_integer_value(json_object_get(playerData, "iPlayer_direction"));
	user_player.iAction_idx = json_integer_value(json_object_get(playerData, "iAction_idx"));
	user_player.iPos_x = json_integer_value(json_object_get(playerData, "iPos_x"));
	user_player.iPos_y = json_integer_value(json_object_get(playerData, "iPos_y"));

	GAME_STAGE = json_integer_value(json_object_get(pData, "GAME_STAGE"));

	for (int i = 0; i < 6; i++) {
		json_t* tmpData = json_array_get(json_object_get(pData, "POKEMON_LIST"), i);
		myPokemonList[i].no = json_integer_value(json_object_get(tmpData, "no"));

		myPokemonList[i].displayName = (char*)json_string_value(json_object_get(tmpData, "displayName"));

		myPokemonList[i].type = json_integer_value(json_object_get(tmpData, "type"));
		myPokemonList[i].level = json_integer_value(json_object_get(tmpData, "level"));
		myPokemonList[i].exp = json_integer_value(json_object_get(tmpData, "exp"));
		myPokemonList[i].crt_hp = json_integer_value(json_object_get(tmpData, "crt_hp"));
		myPokemonList[i].max_hp = json_integer_value(json_object_get(tmpData, "max_hp"));
		myPokemonList[i].dmg = json_integer_value(json_object_get(tmpData, "dmg"));
		myPokemonList[i].def = json_integer_value(json_object_get(tmpData, "def"));
		myPokemonList[i].spd = json_integer_value(json_object_get(tmpData, "spd"));


		if (myPokemonList[i].no == -1) continue;
		for (int j = 0; j < 4; j++) {
			json_t* tmpSkilData = json_array_get(json_object_get(tmpData, "skill"), j);
			myPokemonList[i].skill[j].no = json_integer_value(json_object_get(tmpSkilData, "no"));
			myPokemonList[i].skill[j].displayName = (char*)json_string_value(json_object_get(tmpSkilData, "displayName"));
			myPokemonList[i].skill[j].type = json_integer_value(json_object_get(tmpSkilData, "type"));
			myPokemonList[i].skill[j].dmg_cf = json_number_value(json_object_get(tmpSkilData, "dmg_cf"));
			myPokemonList[i].skill[j].acc = json_number_value(json_object_get(tmpSkilData, "acc"));
			myPokemonList[i].skill[j].crt_pp = json_integer_value(json_object_get(tmpSkilData, "crt_pp"));
			myPokemonList[i].skill[j].max_pp = json_integer_value(json_object_get(tmpSkilData, "max_pp"));
			myPokemonList[i].skill[j].level_condition = json_integer_value(json_object_get(tmpSkilData, "level_condition"));
			myPokemonList[i].skill[j].own = json_boolean_value(json_object_get(tmpSkilData, "own"));
		}

		myPokemonList[i].front = al_create_bitmap(64 * GAME_SCALE, 64 * GAME_SCALE);
		myPokemonList[i].back = al_create_bitmap(64 * GAME_SCALE, 64 * GAME_SCALE);
		myPokemonList[i].icon[0] = al_create_bitmap(32 * GAME_SCALE, 32 * GAME_SCALE);
		myPokemonList[i].icon[1] = al_create_bitmap(32 * GAME_SCALE, 32 * GAME_SCALE);

		myPokemonList[i].front = al_clone_bitmap(pokemonBook[myPokemonList[i].no - 1].front);
		myPokemonList[i].back = al_clone_bitmap(pokemonBook[myPokemonList[i].no - 1].back);
		myPokemonList[i].icon[0] = al_clone_bitmap(pokemonBook[myPokemonList[i].no - 1].icon[0]);
		myPokemonList[i].icon[1] = al_clone_bitmap(pokemonBook[myPokemonList[i].no - 1].icon[1]);
	}

	json_t* tmpObjPosition = json_object_get(pData, "OBJECT_POSITION");
	for (int i = 0; i < json_array_size(tmpObjPosition); i++) {
		json_t* tmpObjPosition_depth2 = json_array_get(tmpObjPosition, i);
		for (int j = 0; j < json_array_size(tmpObjPosition_depth2); j++) {
			json_t* tmpObjPosition_depth3 = json_array_get(tmpObjPosition_depth2, j);
			for (int k = 0; k < json_array_size(tmpObjPosition_depth3); k++) {
				objectPosition[i][j][k] = json_integer_value(json_array_get(tmpObjPosition_depth3, k));
			}
		}
	}

	json_t* tmpInventorySlot = json_object_get(pData, "INVENTORY_SLOTS");
	for (int i = 0; i < json_array_size(tmpInventorySlot); i++) {
		json_t* tmpInventorySlot_depth2 = json_array_get(tmpInventorySlot, i);
		for (int j = 0; j < json_array_size(tmpInventorySlot_depth2); j++) {
			json_t* tmpItem = json_array_get(tmpInventorySlot_depth2, j);
			inventorySlots[i][j].itemType = json_integer_value(json_object_get(tmpItem, "itemType"));
			inventorySlots[i][j].itemStock = json_integer_value(json_object_get(tmpItem, "itemStock"));
			inventorySlots[i][j].itemName = (char*)json_string_value(json_object_get(tmpItem, "itemName"));

			json_t* tmpItemDesc = json_object_get(tmpItem, "itemDesc");
			for (int k = 0; k < json_array_size(tmpItemDesc); k++) {
				inventorySlots[i][j].itemDesc[k] = (char*)json_string_value(json_array_get(tmpItemDesc, k));
			}
		}
	}
}