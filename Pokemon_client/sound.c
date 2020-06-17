#include "sound.h"

// 사운드를 초기화하는 함수
void initSound() {
	al_reserve_samples(1);

	for (int i = 0; i < 16; i++) {
		sounds[i] = al_create_sample_instance(al_load_sample(soundPath[i]));
		al_attach_sample_instance_to_mixer(sounds[i], al_get_default_mixer());
	}
	
}

// 모든 사운드 재생을 일시정지하는 함수
void stopAllSound() {
	for (int i = 0; i < 16; i++) {
		al_set_sample_instance_playing(sounds[i], false);
	}
}

// 101: 임시로 사용하는 배틀 페이즈(WILD) 식별자
// 202: SFX_BALL_BOUNCE
// 203: SFX_CATCH_SUCCESS
// 204: SFX_CATCH_FAIL
// 301: SFX_OPEN_MENU
// 302: SFX_SAVE
// 303: SFX_USE_ITEM
// 400: SFX_DAMAGE
// 500: SFX_HEAL
// 1000: SFX_TALK

void soundHandler(int GAME_STAGE) {
	// 마을
	if (GAME_STAGE == 2 || GAME_STAGE == 5 || GAME_STAGE == 7) {
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], false);
		al_set_sample_instance_playing(sounds[BGM_BATTLE_GYM], false);
		al_set_sample_instance_playing(sounds[BGM_OAK_LAB], false);
		if (!al_get_sample_instance_playing(sounds[BGM_TOWN])) {
			al_set_sample_instance_playing(sounds[BGM_TOWN], true);
			al_set_sample_instance_playmode(sounds[BGM_TOWN], ALLEGRO_PLAYMODE_LOOP);
			al_set_sample_instance_gain(sounds[BGM_TOWN], 0.2);
		}
	}
	// 집
	else if (GAME_STAGE == 0 || GAME_STAGE == 1 || GAME_STAGE == 3) {
		if (!al_get_sample_instance_playing(sounds[BGM_TOWN])) {
			al_set_sample_instance_playing(sounds[BGM_TOWN], true);
			al_set_sample_instance_playmode(sounds[BGM_TOWN], ALLEGRO_PLAYMODE_LOOP);
			al_set_sample_instance_gain(sounds[BGM_TOWN], 0.2);
		}
	}
	// 체육관
	else if (GAME_STAGE == 6) {
		stopAllSound();
		al_set_sample_instance_playing(sounds[BGM_BATTLE_GYM], true);
		al_set_sample_instance_gain(sounds[BGM_BATTLE_GYM], 0.2);
		al_set_sample_instance_playmode(sounds[BGM_BATTLE_GYM], ALLEGRO_PLAYMODE_LOOP);
	}
	// 오박사 연구실
	else if (GAME_STAGE == 4) {
		stopAllSound();
		al_set_sample_instance_playing(sounds[BGM_OAK_LAB], true);
		al_set_sample_instance_gain(sounds[BGM_OAK_LAB], 0.2);
		al_set_sample_instance_playmode(sounds[BGM_OAK_LAB], ALLEGRO_PLAYMODE_LOOP);
	}
	// 야생 배틀
	else if (GAME_STAGE == 101) {
		al_set_sample_instance_playing(sounds[BGM_TOWN], false);
		al_set_sample_instance_playing(sounds[BGM_BATTLE_GYM], false);
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], true);
		al_set_sample_instance_gain(sounds[BGM_BATTLE_WILD], 0.2);
		al_set_sample_instance_playmode(sounds[BGM_BATTLE_WILD], ALLEGRO_PLAYMODE_LOOP);
	}
	// 포켓볼 바운스
	else if (GAME_STAGE == 202) {
		al_set_sample_instance_playing(sounds[SFX_BALL_BOUNCE], true);
	}
	// 포획 성공
	else if (GAME_STAGE == 203) {
		al_set_sample_instance_playing(sounds[BGM_BATTLE_WILD], false);
		al_set_sample_instance_playing(sounds[SFX_CATCH_SUCCESS], true);
		al_set_sample_instance_gain(sounds[SFX_CATCH_SUCCESS], 2.0);
	}
	// 포획 실패
	else if (GAME_STAGE == 204) {
		al_set_sample_instance_playing(sounds[SFX_CATCH_FAIL], true);
		al_set_sample_instance_gain(sounds[SFX_CATCH_FAIL], 3.0);
	}
	// 메뉴 오픈
	else if (GAME_STAGE == 301)
		al_set_sample_instance_playing(sounds[SFX_OPEN_MENU], true);
	// 저장
	else if (GAME_STAGE == 302)
		al_set_sample_instance_playing(sounds[SFX_SAVE], true);
	// 아이템 사용
	else if(GAME_STAGE == 303)
		al_set_sample_instance_playing(sounds[SFX_USE_ITEM], true);
	// 공격
	else if (GAME_STAGE == 400) {
		if (al_get_sample_instance_playing(sounds[SFX_DAMAGE]))
			al_set_sample_instance_playing(sounds[SFX_DAMAGE], false);
		al_set_sample_instance_playing(sounds[SFX_DAMAGE], true);
	}
	// 인터랙션
	else if (GAME_STAGE == 1000) {
		if (al_get_sample_instance_playing(sounds[SFX_TALK]))
			al_set_sample_instance_playing(sounds[SFX_TALK], false);
		al_set_sample_instance_playing(sounds[SFX_TALK], true);
	}
	// 회복
	else if (GAME_STAGE == 500) {
		if (al_get_sample_instance_playing(sounds[SFX_HEAL]))
			al_set_sample_instance_playing(sounds[SFX_HEAL], false);
		al_set_sample_instance_playing(sounds[SFX_HEAL], true);
		al_set_sample_instance_playing(sounds[BGM_OAK_LAB], false);
	}
}