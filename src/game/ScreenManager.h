#pragma once
#include <stack>
#include "GameScreen.h"

class ScreenManager
{
public:
	static ScreenManager* getInstance();

	void init();
	void destroy();

	void navigate(GameScreen* screen);
	void navigateAndReplace(GameScreen* screen);
	void navigateAndClear(GameScreen* screen);
	void back();

	void update();
	void render();

private:
	ScreenManager();
	~ScreenManager();

	static ScreenManager* instance;

	GameScreen* currentScreen;
	std::stack<GameScreen*> screenStack;
};