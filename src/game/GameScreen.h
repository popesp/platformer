#pragma once
#include <iostream>

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void init();
	virtual void render(float dt) = 0;
	virtual void update(float dt) = 0;
	virtual void pause();
	virtual void destroy();
	int a = 0;
};

