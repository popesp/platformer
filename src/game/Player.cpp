#include "Player.h"


Player::Player()
{
	position[X] = 0.f;
	position[Y] = 0.f;

	sprite = new Sprite(position, 10.f, 10.f, "blah");
}


Player::~Player()
{
}
