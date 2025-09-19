#include "Tower.h"


Tower::Tower(int height, int x, Texture2D* shared_sprite, float scale)
{
	this->scale = scale;
	sprite = shared_sprite;

	if (height < 0) {
		position.x = x;
		position.y = -(UNIT_HEIGHT * 10 * scale) - height;
		hitbox.width = UNIT_WIDTH*scale;
		hitbox.height = (UNIT_HEIGHT * 10 * scale);	
	}
	else {

		position.x = x;
		position.y = (UNIT_HEIGHT * 15 * scale) - height;
		hitbox.width = UNIT_WIDTH*scale;
		hitbox.height = (UNIT_HEIGHT * 10 * scale);
	}
	hitbox.x = position.x;
	hitbox.y = position.y;
}

void Tower::update(double dt)
{
	position.x -= dt * GAME_SPEED;
	hitbox.x = position.x;
}

void Tower::render()
{
	DrawRectangleRec(hitbox, BLUE);
	DrawTextureEx(*sprite, position, 0, scale, {255, 255, 0, 63});
}
