#pragma	once


#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	"../game/ScreenManager.h"
#include	"../render/renderer.h"
#include	"window.h"


class Game
{
public:
	Game();
	~Game();

	void mainloop();

private:
	Renderer* renderer;
	ScreenManager* screenManager;
	Window* window;	

	struct
	{
		double rendertime;

		unsigned fps;
		unsigned flags;
	} global;


	void update();
	void render();
};