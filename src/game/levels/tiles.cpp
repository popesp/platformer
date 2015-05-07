#include	"tiles.h"


TileManager* TileManager::instance = (TileManager*)0;

const float TileManager::tileWidth = 32.f;
const float TileManager::tileHeight = 32.f;


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


float Tile::uv_left()
{
	return uv_topleft[X];
}

float Tile::uv_right()
{
	return uv_botright[X];
}

float Tile::uv_top()
{
	return uv_topleft[Y];
}

float Tile::uv_bot()
{
	return uv_botright[Y];
}


TileManager* TileManager::getInstance()
{
	if (!instance)
		instance = new TileManager();

	return instance;
}


Tile* TileManager::getTile(unsigned tileIndex)
{
	return tiles[tileIndex];
}


TileManager::TileManager()
{
	tiles[0] = new Tile(false, 0.f, 0.f, 0.5f, 0.5f);
	tiles[1] = new Tile(true, 0.5f, 0.f, 1.f, 0.5f);
	tiles[2] = new Tile(true, 0.f, 0.5f, 0.5f, 1.f);
}