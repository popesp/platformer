#include "Player.h"

#include	"../math/physics2f.h"
#include	"../render/renderer.h"
#include	"levels/levels.h"


#define	PLAYER_WIDTH						16.f
#define	PLAYER_HEIGHT						16.f


Player::Player(unsigned levelIndex)
{
	vec2f_copy(pos, *LevelManager::getInstance()->levels[levelIndex]->getSpawn());
	vec2f_copy(old, pos);

	vec2f_set(acc, 0.f, 0.25f);

	vec2f dim = {PLAYER_WIDTH, PLAYER_HEIGHT};
	sprite = new Sprite(pos, dim, "res/images/player.png");

	controller = new CharacterController(this);
}


unsigned Player::getLevel()
{
	return levelIndex;
}


void Player::update()
{	
	controller->update();
	
	// update player with verlet integration
	physics2f_verlet(pos, old, acc);
	vec2f_copy(sprite->pos, pos);
	vec2f_set(acc, 0, 0);
}

void Player::render()
{
	Renderer::getInstance()->render(sprite);
}