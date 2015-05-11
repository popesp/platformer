#include "CharacterController.h"
#include "Player.h"
#include <iostream>

CharacterController::CharacterController()
{
}

CharacterController::CharacterController(Player* player)
{
	this->player = player;

	std::vector<Event::Type> events;
	events.push_back(Event::Type::KEY_EVENT);
	EventManager::subscribe(this, events);
}

CharacterController::~CharacterController()
{

}

void CharacterController::notify(Event* event)
{
	if (event->getType() == Event::KEY_EVENT)
		handleKeyEvent((KeyEvent*) event);
}

void CharacterController::handleKeyEvent(KeyEvent* keyEvent)
{
	if (keyEvent->action == GLFW_PRESS)
	{
		if (keyEvent->key == GLFW_KEY_A)
			moveLeft = true;
		else if (keyEvent->key == GLFW_KEY_D)
			moveRight = true;
		else if (keyEvent->key == GLFW_KEY_SPACE)
			jumping = true;
	}
	else if (keyEvent->action == GLFW_RELEASE)
	{
		if (keyEvent->key == GLFW_KEY_A)
			moveLeft = false;
		else if (keyEvent->key == GLFW_KEY_D)
			moveRight = false;
	}
}

void CharacterController::update()
{
	if (moveRight)
		player->old[X] -= player->moveSpeed;
	if (moveLeft)
		player->old[X] += player->moveSpeed;
	if (jumping)
	{
		player->old[Y] += player->moveSpeed;
		jumping = false;
	}
}