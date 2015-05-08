#pragma once
class Event
{
public:
	enum Type
	{
		KEY_EVENT
	};

	Event();
	virtual ~Event();
	Type getType();

protected:
	Type type;
};

