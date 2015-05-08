#include "PlayScreen.h"

#include	"levels/levels.h"


PlayScreen::PlayScreen()
{
	player = new Player(0);
}

PlayScreen::~PlayScreen()
{
	delete player;
}

void PlayScreen::render()
{
	Renderer::getInstance()->render(LevelManager::getInstance()->levels[player->getLevel()]);
	player->render();
}

void PlayScreen::update()
{
	player->update();
}