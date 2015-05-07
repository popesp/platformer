#pragma once
#include "Event.h"
class KeyEvent : public Event
{
public:
	KeyEvent(int key, int scancode, int action, int mods);
	~KeyEvent();
private:
	int key;
	int scancode;
	int action;
	int mods;
};

