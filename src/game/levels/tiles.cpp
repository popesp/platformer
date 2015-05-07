#include	"tiles.h"


TileManager* TileManager::instance = (TileManager*)0;


Tile::Tile(bool collision, float u_topleft, float v_topleft, float u_botright, float v_botright)
	: collision {collision}
{
	vec2f_set(uv_topleft, u_topleft, v_topleft);
	vec2f_set(uv_botright, u_botright, v_botright);
}


bool Tile::getCollision()
{
	return collision;
}


TileManager* TileManager::getInstance()
{
	if (!instance)
		instance = new TileManager();

	return instance;
}


TileManager::TileManager()
	: empty(false, 0.f, 0.f, 0.5f, 1.f)
	, solid(true, 0.5f, 0.f, 1.f, 1.f)
{
	// initialize
}