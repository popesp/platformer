#include "ScreenManager.h"
ScreenManager* ScreenManager::instance = NULL;


ScreenManager* ScreenManager::getInstance()
{
	if (instance == NULL)
		instance = new ScreenManager();

	return instance;
}


void ScreenManager::init()
{

}

void ScreenManager::destroy()
{
	delete instance;
}


//navigate and push the old current screen onto the stack
void ScreenManager::navigate(GameScreen* screen)
{
	if (currentScreen != NULL)
		screenStack.push(currentScreen);

	currentScreen = screen;
}

//navigate and replace the current screen
void ScreenManager::navigateAndReplace(GameScreen* screen)
{
	if (currentScreen != NULL)
		delete currentScreen;

	currentScreen = screen;
}

//navigate and delete all previous screens
void ScreenManager::navigateAndClear(GameScreen* screen)
{
	if (currentScreen != NULL)
		delete currentScreen;

	currentScreen = screen;
	screenStack.empty(); 	//TODO: make sure this doesn't cause a memory leak
}

//navigate back one screen
void ScreenManager::back()
{
	if (screenStack.size() > 0)
	{
		if (currentScreen != NULL)
			delete currentScreen;

		currentScreen = screenStack.top();
		screenStack.pop();
	}
}


void ScreenManager::update()
{
	currentScreen->update();
}

void ScreenManager::render()
{
	currentScreen->render();
}

ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{
	delete currentScreen;
}