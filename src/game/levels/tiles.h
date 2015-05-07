#pragma	once


#include	"../../math/vec2f.h"


class Tile
{
public:
	Tile(bool collision, float u_topleft, float v_topleft, float u_botright, float v_botright);

	bool getCollision();

private:
	vec2f uv_topleft;
	vec2f uv_botright;

	bool collision;
};


class TileManager
{
public:
	static TileManager* getInstance();

private:
	static TileManager* instance;

	Tile empty;
	Tile solid;

	TileManager();
};