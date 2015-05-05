#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "../game/GameScreen.h"
#include "../game/PlayScreen.h"
#include "../game/ScreenManager.h"


#define	GAME_UPS							60
#define	GAME_SPU							(1. / (double)GAME_UPS)

#define	GAME_GLOBAL_FLAG_TERMINATED			0x00000001
#define	GAME_GLOBAL_FLAG_INIT				0x00000000

class Game
{
public:
	Game();
	~Game();

	void mainloop();

private:
	Window window;	

	struct
	{
		double rendertime;

		unsigned fps;
		unsigned flags;
	} global;


	void update();
	void render();
};