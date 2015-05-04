#pragma once
#include <stack>
#include "GameScreen.h"

class ScreenManager
{
public:
	static GameScreen* currentScreen;
	static std::stack<GameScreen> screenStack;

	static void navigate(GameScreen* screen);
	static void navigateAndReplace(GameScreen* screen);
	static void navigateAndClear(GameScreen* screen);
	static void back();
	static void destroy();
};

