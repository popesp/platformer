#pragma once
#include "Event.h"

class EventListener
{
public:
	EventListener();
	virtual ~EventListener();
	virtual void notify(Event* event) = 0;
};

