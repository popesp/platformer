#pragma once
#include "GameScreen.h"
class PlayScreen :	public GameScreen
{
public:
	PlayScreen();
	~PlayScreen();
	void render();
	void update();
};

