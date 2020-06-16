#include "screen.h"
float camera_position_x;
float camera_position_y;
ALLEGRO_TRANSFORM camera;

// 카메라 기준 위치를 반환하는 함수
float camera_get_position(char type, float type_pos, int player_idx) {
	float position = 0.0f;
	switch (type) {
	case 'x':
		position = -(GAME_WIDTH / 2) + (type_pos + (player_idx / 2));
		if (position < 0) position = 0;

		if (position >= (GAME_MAP_WIDTH - (GAME_WIDTH)))
			position = GAME_MAP_WIDTH - (GAME_WIDTH);
		break;
	case 'y':
		position = -(GAME_HEIGHT / 2) + (type_pos + (player_idx / 2));
		if (position < 0) position = 0;

		if (position >= (GAME_MAP_HEIGHT - (GAME_HEIGHT)))
			position = GAME_MAP_HEIGHT - (GAME_HEIGHT);
		break;
	}

	return position;
}

// 플레이어 좌표에 대해 카메라 위치를 갱신하는 함수
void updateCamera(player _player) {
	camera_position_x = camera_get_position('x', _player.iPos_x, 16);
	camera_position_y = camera_get_position('y', _player.iPos_y, 32);
	al_identity_transform(&camera);
	al_translate_transform(&camera, -camera_position_x, -camera_position_y);
	al_use_transform(&camera);
}

// 화면이 밝게 전환되는 효과
void fadeOut(double seconds) {
	// alpha 값을 0.0에서 1.0까지 전환, 
	// 각 전환시 seconds 만큼 대기
	for (float alpha = 0.0; alpha <= 1.0; alpha += 0.1)
	{
		al_draw_filled_rectangle(0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT, al_map_rgba_f(0, 0, 0, alpha));
		al_flip_display();

		//al_clear_to_color(al_map_rgb(0, 0, 0));
		//al_clear_to_color(al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha));

		al_rest(seconds);
	}
}

// 화면이 어둡게 전환되는 효과
void fadeIn(double seconds) {
	// alpha 값을 1.0에서 0.0까지 전환
	// 각 전환시 seconds 만큼 대기
	for (float alpha = 1.0; alpha >= 0.0; alpha -= 0.1)
	{
		al_draw_filled_rectangle(0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT, al_map_rgba_f(0, 0, 0, alpha));
		al_flip_display();


		render();

		//al_clear_to_color(al_map_rgb(255, 255, 255));
		//al_clear_to_color(al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha));

		al_rest(seconds);
	}
}