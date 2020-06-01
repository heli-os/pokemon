#include "sound.h"

void initSound() {
	al_reserve_samples(1);

	for (int i = 0; i < 15; i++) {
		sounds[i] = al_create_sample_instance(al_load_sample(soundPath[i]));
		al_attach_sample_instance_to_mixer(sounds[i], al_get_default_mixer());
	}
	
}

unsigned int lastSec = 0;
void stopAllSound() {
	lastSec = 0;
	for (int i = 0; i < 15; i++) {
		al_stop_sample_instance(sounds[i]);
	}
}

// 101: 임시로 사용하는 배틀 페이즈(WILD) 식별자
// 202: SFX_BALL_BOUNCE
// 203: SFX_CATCH_SUCCESS
// 204: SFX_CATCH_FAIL

void soundHandler(int GAME_STAGE) {
	// 마을
	if (GAME_STAGE == 2 || GAME_STAGE == 5 || GAME_STAGE == 7) {
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], false);
		al_set_sample_instance_playing(sounds[BGM_OAK_LAB], false);
		if (!al_get_sample_instance_playing(sounds[BGM_TOWN]))
			al_set_sample_instance_playing(sounds[BGM_TOWN], true);
	}
	// 집
	else if (GAME_STAGE == 0 || GAME_STAGE == 1 || GAME_STAGE == 3) {
		if (!al_get_sample_instance_playing(sounds[BGM_TOWN]))
			al_set_sample_instance_playing(sounds[BGM_TOWN], true);
	}
	// 체육관
	else if (GAME_STAGE == 6) {
		stopAllSound();
	}
	// 오박사 연구실
	else if (GAME_STAGE == 4) {
		stopAllSound();
		al_set_sample_instance_playing(sounds[BGM_OAK_LAB], true);
		al_set_sample_instance_playmode(sounds[BGM_BATTLE_WILD], ALLEGRO_PLAYMODE_LOOP);
	}
	// 야생 배틀
	else if (GAME_STAGE == 101) {
		al_set_sample_instance_playing(sounds[BGM_TOWN], false);
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], true);
		al_set_sample_instance_playmode(sounds[BGM_BATTLE_WILD], ALLEGRO_PLAYMODE_LOOP);
		al_set_sample_instance_position(sounds[BGM_BATTLE_WILD], lastSec);
	}
	// 볼 바운스
	else if (GAME_STAGE == 202) {
		if(al_get_sample_instance_playing(sounds[BGM_BATTLE_WILD]))
			lastSec = al_get_sample_instance_position(sounds[BGM_BATTLE_WILD]);
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], false);
		al_set_sample_instance_playing(sounds[SFX_BALL_BOUNCE], true);
	}
	// 포획 성공
	else if (GAME_STAGE == 203)
		al_set_sample_instance_playing(sounds[SFX_CATCH_SUCCESS], true);
	// 포획 실패
	else if (GAME_STAGE == 204)
		al_set_sample_instance_playing(sounds[SFX_CATCH_FAIL], true);

}