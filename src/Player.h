#pragma once
#include "math/Vector2.h"
#include "render/Sprite.h"

class Player
{
public:
	Player();
	~Player();

	Vector2 position;
	Sprite sprite;
};

