#pragma once
#include "GameScreen.h"
#include "../render/Sprite.h"

class PlayScreen :	public GameScreen
{
public:
	PlayScreen();
	~PlayScreen();
	void render();
	void update();

	Sprite* sprite;
};

