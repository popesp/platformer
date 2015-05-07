#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	vec2f pos = {200.f, 100.f};
	vec2f dim = {100.f, 100.f};
	sprite = new Sprite(pos, dim, "res/images/test.png");
}

PlayScreen::~PlayScreen()
{
	delete sprite;
}

void PlayScreen::render()
{
	sprite->updateTransform();
	Renderer::getInstance()->render(sprite);
}

void PlayScreen::update()
{
	sprite->rotation += 0.01f;
	sprite->pos[X] += 1.f;
}