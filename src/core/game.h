#ifndef GAME
#define	GAME
#include "../Player.h"

class Game
{
public:
	Game();

	void mainloop();

	~Game();

private:
	static bool running;

	Player player;
};


#endif
