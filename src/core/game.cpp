#include "Game.h"
#include "../ScreenManager.h"
bool Game::running = false;

Game::Game()
{	
	// init
	player = Player();

}

void Game::mainloop()
{
	running = true;
	//ScreenManager::navigate(new SplashScreen);

	while (running)
	{
		//poll events
		//Window::poll();

		//update 
		//ScreenManager::update(deltaTime);

		//render
		//ScreenManager::render(deltaTime);

		//display
		//Window::display();
	}
}

Game::~Game()
{
	// destroy
	//ScreenManager::destroy();
}