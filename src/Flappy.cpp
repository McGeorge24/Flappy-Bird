#include "Flappy.h"

Flappy::Flappy(const char* sprite_path, float scale_p)
{
	sprite = LoadTexture(sprite_path);
	hitbox = { (float)(UNIT_WIDTH*scale_p), (float)(7*UNIT_HEIGHT*scale_p), (float)FLAPPY_WIDTH * scale_p, (float)FLAPPY_HEIGHT * scale_p};
	this->scale = scale_p;

	position = { hitbox.x, hitbox.y };
	velocity = { 0.0f, 0.0f };
	acceleration = { 0.0f, 0.0f };
}

Flappy::~Flappy()
{
	UnloadTexture(sprite);

}

void Flappy::update(double dt, int height)
{
	acceleration.y = 800.0f;

	if (IsKeyPressed(KEY_SPACE)) {
		acceleration.y = -25000.0f;
		velocity.y = 0;
	}

	if (position.y >= (15*UNIT_HEIGHT - FLAPPY_HEIGHT) * scale)
		position.y = (15 * UNIT_HEIGHT - FLAPPY_HEIGHT-1) * scale;
	if (position.y <= 0.0f)
		position.y = 0.0f;
	if ((position.y <= 0.0f) || (position.y >= float(height))) 
		velocity.y *= -0.9f;

	velocity.y += acceleration.y*dt;
	position.y += velocity.y*dt;
	hitbox.y = position.y;
}

void Flappy::render()
{
	DrawRectangleRec(hitbox, RED);
	DrawTextureEx(sprite, position, 0, scale, WHITE);
}

bool Flappy::check_colision(Rectangle tower)
{	
	return CheckCollisionRecs(hitbox, tower);
}
