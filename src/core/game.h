#ifndef GAME
#define	GAME


#include	"window.h"


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


#endif
