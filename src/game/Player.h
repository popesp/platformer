#pragma once


#include "../math/vec2f.h"
#include "../render/Sprite.h"
#include "../core/geometry/Shape.h"
#include "../core/geometry/Rectangle.h"
#include "../game/CharacterController.h"

class Player
{
public:
	friend CharacterController;

	Player(unsigned levelIndex);

	unsigned getLevel();

	void update();
	void render();

private:
	vec2f pos;
	vec2f old;
	vec2f acc;
	float moveSpeed;

	unsigned levelIndex;
	Sprite* sprite;
	CharacterController* controller;
};