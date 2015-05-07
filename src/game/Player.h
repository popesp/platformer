#pragma once


#include "../math/vec2f.h"
#include "../render/Sprite.h"
#include "../core/geometry/Shape.h"
#include "../core/geometry/Rectangle.h"
#include "CharacterController.h"


class Player
{
public:
	Player();
	~Player();
	//void update(float deltaTime);

private:
	vec2f position;
	Sprite* sprite;
	Rectangle boundingBox;
	//CharacterController controller;
};