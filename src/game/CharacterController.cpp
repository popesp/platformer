#include "CharacterController.h"
#include "Player.h"
#include <iostream>

CharacterController::CharacterController()
{
}

CharacterController::CharacterController(Player* player)
{
	this->player = player;
	EventManager::subscribe(this);
}

CharacterController::~CharacterController()
{

}

void CharacterController::notify(Event* event)
{
	KeyEvent* keyEvent = dynamic_cast<KeyEvent*> (event);
	if (keyEvent != NULL)
		handleKeyEvent(keyEvent);
}

void CharacterController::handleKeyEvent(KeyEvent* keyEvent)
{
	if (keyEvent->action == GLFW_PRESS)
	{
		if (keyEvent->key == GLFW_KEY_A)
			moveLeft = true;
		else if (keyEvent->key == GLFW_KEY_D)
			moveRight = true;
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
	vec2f accR = { 1, 0 };
	vec2f accL = { -1, 0 };
	if (moveRight)
		vec2f_add(player->acc, accR);
	else if (moveLeft)
		vec2f_add(player->acc, accL);
}