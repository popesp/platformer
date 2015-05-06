#pragma once
#include "../math/vec2f.h"
#include "../render/Sprite.h"
#include "../core/geometry/Shape.h"
#include "../core/geometry/Rectangle.h"

class Player
{
public:
	Player();
	~Player();

private:
	vec2f position;
	Sprite sprite;
	Shape boundingBox;
};

