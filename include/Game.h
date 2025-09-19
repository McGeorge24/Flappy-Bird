#pragma once
#include "Flappy.h"
#include "Tower.h"
#include <raygui.h>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>


class Game
{
public:
	Game();
	~Game();
	void run();

private:
	Flappy * flappy;
	std::deque<Tower*> towers;
	Texture2D shared_tower_texture;


	int monitor;
	int monitor_height;
	int monitor_width;

	int window_height;
	int window_width;

	float default_scale = 3.0f;
	float scale = 1.0f;
	Font font;

	int score;
	int is_game_over;

	void reset_game();
	void generate_tower();
	void DrawScore();
	void game_over_screen();
};

