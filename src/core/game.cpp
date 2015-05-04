#include	"game.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>


#define	GAME_UPS							60
#define	GAME_SPU							(1. / (double)GAME_UPS)

#define	GAME_GLOBAL_FLAG_TERMINATED			0x00000001
#define	GAME_GLOBAL_FLAG_INIT				0x00000000


Game::Game()
{
	glfwInit();
	// init
}

Game::~Game()
{
	// destroy
}


void Game::mainloop()
{
	unsigned frames[GAME_UPS], current_update, i;
	double time;

	
	// initialize frames array
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
			update();
			current_update = (current_update + 1) % GAME_UPS;
			frames[current_update] = 0;
			time -= GAME_SPU;
		}

		// render as frequently as possible
		render();
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