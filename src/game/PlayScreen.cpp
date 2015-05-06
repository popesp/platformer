#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	vec2f pos = {100.f, 100.f};
	sprite = new Sprite(pos, 100, 100, "assets/test.bmp");
}

PlayScreen::~PlayScreen()
{

}

void PlayScreen::render()
{
	Renderer::getInstance()->render(sprite);
}

void PlayScreen::update()
{

}