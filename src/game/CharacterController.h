#pragma once


#include "../core/input/EventListener.h"
#include"../core/input/EventManager.h"
#include "Player.h"


class Player;


class CharacterController : public EventListener
{
public:
	CharacterController();
	CharacterController(Player* player);
	~CharacterController();
	void notify(Event* event);
	//void update(float deltaTime);

private:
	Player* player;
	bool moveLeft, moveRight, jumping, wallSliding, running, dashing;
};

