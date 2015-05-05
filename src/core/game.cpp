#include	"game.h"


#define	GAME_TITLE							"Platformer"
#define	GAME_VERSION						"0.0.1"

#define	GAME_DEFAULT_WIDTH					1280
#define	GAME_DEFAULT_HEIGHT					800

#define	GAME_UPS							60
#define	GAME_SPU							(1. / (double)GAME_UPS)

#define	GAME_GLOBAL_FLAG_TERMINATED			0x00000001
#define	GAME_GLOBAL_FLAG_INIT				0x00000000


Game::Game()
{
	GameScreen* play;
	glfwInit();

	window = new Window(GAME_DEFAULT_WIDTH, GAME_DEFAULT_HEIGHT, GAME_TITLE " " GAME_VERSION);

	screenManager = ScreenManager::getInstance();
	play = new PlayScreen();
	screenManager->init(play);
}

Game::~Game()
{
	// delete
}

void Game::mainloop()
{
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

	screenManager->getScreen()->update(0.f);

	// check for window close messages
	if (glfwWindowShouldClose(window->w))
		global.flags |= GAME_GLOBAL_FLAG_TERMINATED;
}

void Game::render()
{
	// set render timer
	global.rendertime = -glfwGetTime();

	glClear(GL_COLOR_BUFFER_BIT);

	screenManager->getScreen()->render(0.f);

	// end render timer
	global.rendertime += glfwGetTime();

	glfwSwapBuffers(window->w);
}