#pragma once
#include <raylib.h>
#include <stdio.h>
#include "Settings.h"

class Flappy
{
public:
	Flappy(const char* sprite_path, float scale);
	~Flappy();
	void update(double dt, int height);
	void render();
	bool check_colision(Rectangle tower);

private:
	Texture2D sprite;
	Rectangle hitbox;

	float scale;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
};

