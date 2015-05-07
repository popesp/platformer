#pragma	once


#include	"../../math/vec2f.h"


class Level
{
public:
	Level(unsigned char layout[], unsigned width, unsigned height, float spawnx, float spawny);

private:
	unsigned char* layout;

	unsigned width;
	unsigned height;

	vec2f spawn;
};

class LevelManager
{
public:
	static LevelManager* getInstance();

private:
	static LevelManager* instance;

	Level level0;

	LevelManager();
};