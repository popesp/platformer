#pragma once


#include "../core/input/EventListener.h"
#include"../core/input/EventManager.h"

class Player;
class CharacterController : public EventListener
{
public:
	CharacterController();
	CharacterController(Player* player);
	~CharacterController();
	void notify(Event* event);
	void update();
	void handleKeyEvent(KeyEvent* keyEvent);

private:
	Player* player;
	bool moveLeft, moveRight, jumping, wallSliding, running, dashing;
};

