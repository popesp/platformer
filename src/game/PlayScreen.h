#pragma once


#include "GameScreen.h"
#include	"Player.h"


class PlayScreen :	public GameScreen
{
public:
	PlayScreen();
	~PlayScreen();
	void render();
	void update();

	Player* player;
};

