#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	vec2f pos = {200.f, 100.f};
	vec2f dim = {100.f, 100.f};
	sprite = new Sprite(pos, dim, "assets/test.bmp");
}

PlayScreen::~PlayScreen()
{

}

void PlayScreen::render()
{
	sprite->updateTransform();
	Renderer::getInstance()->render(sprite);
}

void PlayScreen::update()
{

}