#include "ScreenManager.h"


ScreenManager* ScreenManager::instance = NULL;


ScreenManager* ScreenManager::getInstance()
{
	if (instance == NULL)
		instance = new ScreenManager();

	return instance;
}


void ScreenManager::init(GameScreen* screen)
{
	currentScreen = screen;
}

void ScreenManager::destroy()
{
	delete instance;
}


//navigate and push the old current screen onto the stack
void ScreenManager::navigate(GameScreen* screen)
{
	screenStack.push(currentScreen);
	setScreen(screen);
}

//navigate and replace the current screen
void ScreenManager::navigateAndReplace(GameScreen* screen)
{
	setScreen(screen);
}

//navigate and delete all previous screens
void ScreenManager::navigateAndClear(GameScreen* screen)
{
	setScreen(screen);
	screenStack.empty(); 	//TODO: make sure this doesn't cause a memory leak
}

//navigate back one screen
void ScreenManager::back()
{
	setScreen(screenStack.top());
	screenStack.pop();		//TODO: make sure this doesn't cause a memory leak
}


void ScreenManager::update()
{
	currentScreen->update();
}

void ScreenManager::render()
{
	currentScreen->render();
}


void ScreenManager::setScreen(GameScreen* screen)
{
	*currentScreen = *screen;
}