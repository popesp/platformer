#pragma	once


#include	"../../math/vec2f.h"


#define	TILES								3


class Tile
{
public:
	Tile(bool collision, float u_topleft, float v_topleft, float u_botright, float v_botright);

	bool getCollision();

	float uv_left();
	float uv_right();
	float uv_top();
	float uv_bot();

private:
	vec2f uv_topleft;
	vec2f uv_botright;

	bool collision;
};


class TileManager
{
public:
	static TileManager* getInstance();

	static const float tileWidth;
	static const float tileHeight;

	Tile* getTile(unsigned tileIndex);

private:
	static TileManager* instance;

	Tile* tiles[TILES];

	TileManager();
};