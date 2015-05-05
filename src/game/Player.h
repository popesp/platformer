#pragma once
#include "../math/vec2f.h"
#include "../render/Sprite.h"

class Player
{
public:
	Player();
	~Player();

	vec2f position;
	Sprite sprite;
};

