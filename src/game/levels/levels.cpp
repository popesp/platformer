#include	"levels.h"

#include	"tiles.h"


LevelManager* LevelManager::instance = (LevelManager*)0;


static unsigned char layout0[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};


Level::Level(unsigned char layout[], unsigned width, unsigned height, float spawnx, float spawny, const char* tilesheet)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_TEX)
	, layout{layout}
	, width{width}
	, height{height}
{
	unsigned i;
	float y;

	vec2f_set(spawn, spawnx, spawny);

	texture = Texture::loadTexture(tilesheet);
	texture->upload();

	currentShader = Renderer::getInstance()->texture;

	allocate(width * height * 6);

	// build level
	y = 0.f;
	for (i = 0; i < height; i++)
	{
		unsigned j;
		float x;

		x = 0.f;
		for (j = 0; j < width; j++)
		{
			Tile* tile = TileManager::getInstance()->getTile(layout[i*width + j]);

			// tile vertex attributes
			vertpos(x, y);
			verttex(tile->uv_left(), tile->uv_top());
			vertpos(x, y + TileManager::tileHeight);
			verttex(tile->uv_left(), tile->uv_bot());
			vertpos(x + TileManager::tileWidth, y + TileManager::tileHeight);
			verttex(tile->uv_right(), tile->uv_bot());

			vertpos(x, y);
			verttex(tile->uv_left(), tile->uv_top());
			vertpos(x + TileManager::tileWidth, y + TileManager::tileHeight);
			verttex(tile->uv_right(), tile->uv_bot());
			vertpos(x + TileManager::tileWidth, y);
			verttex(tile->uv_right(), tile->uv_top());

			x += TileManager::tileWidth;
		}

		y += TileManager::tileHeight;
	}

	upload();

	mat3f_identity(transform);
}


void Level::updateTransform()
{

}


vec2f* Level::getSpawn()
{
	return &spawn;
}


LevelManager* LevelManager::getInstance()
{
	if (!instance)
		instance = new LevelManager();

	return instance;
}


LevelManager::LevelManager()
{
	levels[0] = new Level(layout0, 28, 19, 100.f, 80.f, "res/images/tiles.png");
}