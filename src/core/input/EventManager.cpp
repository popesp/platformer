#include "EventManager.h"
std::vector<EventListener*> EventManager::listeners;
std::vector<Event*> EventManager::events;

void EventManager::subscribe(EventListener* listener)
{
	listeners.push_back(listener);
}

void EventManager::unsubscribe(EventListener* listener)
{
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void EventManager::notify()
{	
	for (unsigned i = 0; i < listeners.size(); ++i)
		for (unsigned j = 0; j < events.size(); ++j)
			listeners[i]->notify(events[j]);
	events.clear();
}

void EventManager::poll()
{
	glfwPollEvents();	
}

void EventManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void*) window;
	events.push_back(new KeyEvent(key, scancode, action, mods));
}