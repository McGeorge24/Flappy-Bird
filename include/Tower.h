#pragma once
#include <raylib.h>
#include "Settings.h"

class Tower
{
public:
	Tower(int height, int x, Texture2D* shared_sprite, float scale);
	void update(double dt);
	void render();
	Rectangle hitbox;

private:
	Texture2D* sprite;

	float scale;
	Vector2 position;
};

