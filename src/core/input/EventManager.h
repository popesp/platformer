#pragma once
#include <vector>
#include	<GLFW/glfw3.h>
#include "../input/EventListener.h"
#include "../input/Event.h"
#include "../input/KeyEvent.h"

class EventManager
{
public:
	friend class Window;

	static void subscribe(EventListener* listener);
	static void unsubscribe(EventListener* listener);
	static void notify();
	static void poll();

private:
	static std::vector<EventListener*> listeners;
	static std::vector<Event*> events;

	EventManager();
	~EventManager();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

