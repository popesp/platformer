#include "ScreenManager.h"

//navigate and push the old current screen onto the stack
void navigate(GameScreen* screen)
{
	//stack.push current screen
	//current screen = screen
}

//navigate and replace the current screen
void navigateAndReplace(GameScreen* screen)
{
	//delete current screen
	//current screen = screen
}

//navigate and delete all previous screens
void navigateAndClear(GameScreen* screen)
{
	//delete current screen
	//clear screen stack

	//current screen = screen
}

//navigate back one screen
void back()
{
	//delete current screen 
	//current screen = stack.pop 
}

void destroy()
{

}