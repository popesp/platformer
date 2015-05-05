#pragma once
#include <stack>
#include "GameScreen.h"

class ScreenManager
{
public:
	static ScreenManager* getInstance();

	void init(GameScreen* screen);
	void navigate(GameScreen* screen);
	void navigateAndReplace(GameScreen* screen);
	void navigateAndClear(GameScreen* screen);
	void back();
	void destroy();

	GameScreen* getScreen();

private:
	static ScreenManager* instance;
	GameScreen* currentScreen;
	std::stack<GameScreen*> screenStack;

	ScreenManager();
	void setScreen(GameScreen* screen);
};

