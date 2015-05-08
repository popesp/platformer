#pragma	once


#include	"../../math/vec2f.h"
#include	"../../render/renderer.h"


#define	LEVELS								1


class Level : public Renderable
{
public:
	Level(unsigned char layout[], unsigned width, unsigned height, float spawnx, float spawny, const char* tilesheet);

	void updateTransform();

	vec2f* getSpawn();

private:
	unsigned width;
	unsigned height;
	
	unsigned char* layout;
	
	vec2f spawn;
	
};

class LevelManager
{
public:
	static LevelManager* getInstance();

	Level* levels[LEVELS];

private:
	static LevelManager* instance;

	LevelManager();
};