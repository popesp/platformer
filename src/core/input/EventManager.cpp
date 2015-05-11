#include "EventManager.h"
std::vector<Event*> EventManager::events;
std::map<Event::Type, std::vector<EventListener*>> EventManager::subscriptions;

void EventManager::subscribe(EventListener* listener, std::vector<Event::Type> events)
{
	//for each event type add the listener to the corrisponding list 
	for (unsigned i = 0; i < events.size(); ++i)
	{
		Event::Type type = events[i];		
		auto subs = subscriptions.find(type);

		// check if event type exists and add listner to list
		if (subs != std::end(subscriptions))
		{
			if (std::find(subs->second.begin(), subs->second.end(), listener) != std::end(subs->second))
				subs->second.push_back(listener);
			else
				;// listener already subscribed
		}
		// event type does not exist yet
		else 
		{
			std::vector<EventListener*> listeners;
			listeners.push_back(listener);
			subscriptions.insert(std::pair<Event::Type, std::vector<EventListener*>>(type, listeners));
		}
	}
}

void EventManager::unsubscribe(EventListener* listener, std::vector<Event::Type> events)
{
	for (unsigned i = 0; i < events.size(); ++i)
	{
		Event::Type eventType = events[i];
		std::vector<EventListener*> subscribers = subscriptions[eventType];
		auto element = std::find(subscribers.begin(), subscribers.end(), listener);

		if (element != std::end(subscribers))
			subscriptions[eventType].erase(element);
		else
			;// listener not in the list?
	}
}

void EventManager::notify()
{	
	for (unsigned i = 0; i < events.size(); ++i)
	{
		Event* event = events[i];
		std::vector<EventListener*> subscribers = subscriptions[event->getType()];

		for (unsigned j = 0; j < subscribers.size(); ++j)
			subscribers[j]->notify(event);
	}
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
