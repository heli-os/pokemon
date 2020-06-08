#ifndef _POKEMON_SOUND_HEADER_
#define _POKEMON_SOUND_HEADER_
#include "nginx_common.h"

ALLEGRO_SAMPLE_INSTANCE* sounds[16];

static char* soundPath[16] = {
	"sounds/bgm_town.ogg",
	"sounds/bgm_oak.ogg",
	"sounds/bgm_battle(wild).ogg",
	"sounds/bgm_gym.ogg",
	"sounds/bgm_battle(gym).ogg",
	"sounds/bgm_victory(gym).ogg",
	"sounds/bgm_evolution.ogg",
	"sounds/bgm_heal.ogg",
	"sounds/catchSuccess.wav",
	"sounds/catchFail.wav",
	"sounds/damageSound.wav",
	"sounds/openMenu.wav",
	"sounds/pokeballBounce.wav",
	"sounds/save.wav",
	"sounds/talk.wav",
	"sounds/useItem.wav"
};

enum SOUNDLIST {
	BGM_TOWN,
	BGM_OAK_LAB,
	BGM_BATTLE_WILD,
	BGM_BATTLE,
	BGM_BATTLE_GYM,
	BGM_BATTLE_GYM_WIN,
	BGM_EVOLUTION,
	SFX_HEAL,
	SFX_CATCH_SUCCESS,
	SFX_CATCH_FAIL,
	SFX_DAMAGE,
	SFX_OPEN_MENU,
	SFX_BALL_BOUNCE,
	SFX_SAVE,
	SFX_TALK,
	SFX_USE_ITEM
};

void initSound();
void soundHandler(int GAME_STAGE);
#endif