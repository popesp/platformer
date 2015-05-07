#include "CharacterController.h"

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
	EventManager::unsubscribe(this);
}

void CharacterController::notify(Event* event)
{
	KeyEvent* keyEvent = dynamic_cast<KeyEvent*> (event);
	if (keyEvent != NULL)
	{
		moveLeft = true;//do stuff
	}
}

//void CharacterController::update(float deltaTime)
//{
//
//}