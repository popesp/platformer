#include "KeyEvent.h"


KeyEvent::KeyEvent(int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods)
{
	type = KEY_EVENT;
}


KeyEvent::~KeyEvent()
{
}
