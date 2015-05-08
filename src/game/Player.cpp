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

	vec2f_set(acc, 0.f, 0.01f);
	vec2f_set(damping, 0.9f, 0.99f);

	vec2f dim = {PLAYER_WIDTH, PLAYER_HEIGHT};
	sprite = new Sprite(pos, dim, "res/images/player.png");

	controller = new CharacterController(this);
	moveSpeed = 1.f;
}


unsigned Player::getLevel()
{
	return levelIndex;
}


void Player::update()
{
	controller->update();
	
	// update player with verlet integration
	physics2f_verlet(pos, old, acc, damping);
	vec2f_copy(sprite->pos, pos);
}

void Player::render()
{
	Renderer::getInstance()->render(sprite);
}