#pragma	once


#include	"../../math/vec2f.h"
#include	"../../render/renderer.h"


#define	LEVELS								1


class Level : public Renderable
{
public:
	Level(unsigned char layout[], unsigned width, unsigned height, float spawnx, float spawny, const char* tilesheet);

	void updateTransform();

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

	void render(unsigned levelIndex);

private:
	static LevelManager* instance;

	Level* levels[LEVELS];

	LevelManager();
};