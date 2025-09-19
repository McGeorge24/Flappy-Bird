#include "Game.h"
#include "stdio.h"

Game::Game()
{
	SetTargetFPS(60);
	InitWindow(600, 675, "Flappy bird");

	monitor = GetCurrentMonitor();
	monitor_height = GetMonitorHeight(monitor);
	monitor_width = GetMonitorWidth(monitor);

	window_height = 0.8 * monitor_height;
	window_width = 0.8 * window_height;
	SetWindowSize(window_width, window_height);
	SetWindowPosition((monitor_width-window_width)/2, window_height/10);

	scale = (float)window_height / DEFAULT_HEIGHT;
	scale *= DEFAULT_SCALE;

	//font = LoadFont("resources/fonts/jupiter_crash.png");

	flappy = new Flappy("assets/bunny2.png", scale);
	shared_tower_texture = LoadTexture("assets/tower.png");

	reset_game();
}

Game::~Game()
{	
	towers.clear();
	CloseWindow();
}

void Game::run()
{
	double dt;
	int i;

	while (!WindowShouldClose()) {

		//update
		switch (is_game_over)
		{
		case false:
			dt = GetFrameTime();

			flappy->update(dt, window_height);
			for (i = 0; i < towers.size(); i++)
				towers[i]->update(dt);
			generate_tower();

			if (flappy->check_colision(towers[0]->hitbox)) {
				is_game_over = true;
			}
			if (flappy->check_colision(towers[1]->hitbox)) {
				is_game_over = true;
			}

			break;

		case true:
			if (IsKeyDown(KEY_SPACE))
				reset_game();
			break;
		}


		//render
		BeginDrawing();
		ClearBackground(BLACK);

		flappy->render();

		for (i = 0; i < towers.size(); i++)
			towers[i]->render();

		//display score
		DrawScore();

		if (is_game_over)
			game_over_screen();

		EndDrawing();
	}
}

void Game::reset_game()
{	
	towers.clear();
	int last_x = UNIT_WIDTH * scale;

	for (int i = 0; i < 3; i++)
	{
		int height = rand() % (UNIT_HEIGHT*10*(int)scale);

		last_x += 5 * UNIT_WIDTH * scale;

		towers.push_back(new Tower(height, last_x, &shared_tower_texture, scale));
		towers.push_back(new Tower(-12*UNIT_HEIGHT*(int)scale+height, last_x, &shared_tower_texture, scale));
	}

	score = 0;
	is_game_over = false;
}

void Game::generate_tower()
{
	//printf("called\n");
	if (towers.front()->hitbox.x < -UNIT_WIDTH) {

		delete towers.front(); towers.pop_front();
		delete towers.front(); towers.pop_front();

		int height = (rand() % (UNIT_HEIGHT * 10) + UNIT_HEIGHT) * (int)scale;
		int last_x = towers.back()->hitbox.x;
		last_x += 5 * UNIT_WIDTH * scale;

		towers.push_back(new Tower(height, last_x, &shared_tower_texture, scale));
		towers.push_back(new Tower(-12 * UNIT_HEIGHT * (int)scale + height, last_x, &shared_tower_texture, scale));

		score++;
	}
}

void Game::DrawScore() // can only be called between begindrawing and enddrawing
{
	char buffer[20];
	sprintf_s(buffer, "Score: %d", score);
	DrawText(buffer, 50, 50, 70, WHITE);
}

void Game::game_over_screen() // can only be called between begindrawing and enddrawing
{
	DrawRectangle(0, 0, window_width, window_height, { 0, 0, 0, 100 });
	DrawTextEx(font, "GAME OVER", { 0.06f*window_width, (float)(window_height / 2 - 25) }, 0.15f*window_width, 0.01f*window_width, SKYBLUE);
}

	
