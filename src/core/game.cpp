#include	"game.h"

Game::Game()
{
	glfwInit();

	WindowSettings settings;
	settings.width = 1024;
	settings.height = 768;
	window.applysettings(&settings);
}

Game::~Game()
{
	// destroy
}

void Game::mainloop()
{
	ScreenManager screenManager = *ScreenManager::getInstance();
	GameScreen* screen = new PlayScreen();
	screenManager.init(screen);
	float deltaTime = 0.f;

	unsigned frames[GAME_UPS], current_update, i;
	double time;

	//initialize frames array
	for (i = 0; i < GAME_UPS; i++)
		frames[i] = 0;

	// initialize timer
	glfwSetTime(0.);
	time = 0.;

	// loop until terminated
	current_update = 0;
	while (!(global.flags & GAME_GLOBAL_FLAG_TERMINATED))
	{		
		// get elapsed time and reset the timer
		time += glfwGetTime();
		glfwSetTime(0.);

		// update as much as necessary
		while (time >= GAME_SPU)
		{
			// calculate the fps
			global.fps = 0;
			for (i = 0; i < GAME_UPS; i++)
				global.fps += frames[i];

			// update
			screen->update(deltaTime);

			current_update = (current_update + 1) % GAME_UPS;
			frames[current_update] = 0;
			time -= GAME_SPU;
		}

		// render as frequently as possible
		screen->render(deltaTime);

		frames[current_update]++;
	}
}


void Game::update()
{
	glfwPollEvents();

	// ESC to quit
	if (glfwGetKey(window.w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		global.flags |= GAME_GLOBAL_FLAG_TERMINATED;

	// check for window close messages
	if (glfwWindowShouldClose(window.w))
		global.flags |= GAME_GLOBAL_FLAG_TERMINATED;
}

void Game::render()
{
	// set render timer
	global.rendertime = -glfwGetTime();

	glClear(GL_COLOR_BUFFER_BIT);

	// end render timer
	global.rendertime += glfwGetTime();

	glfwSwapBuffers(window.w);
}