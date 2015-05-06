#pragma once
#include <iostream>
#include "../render/renderer.h"

class GameScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	virtual void init();
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void pause();
	virtual void destroy();
};

