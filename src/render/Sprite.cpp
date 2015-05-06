#include "Sprite.h"


Sprite::Sprite(const char* textureName)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_TEX)
{
	texture->loadTexture(textureName);
}

Sprite::Sprite(vec2f position, float width, float height, const char* textureName)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_COL)
{
	rect = Rectangle(position, width, height);
	// Texture* temp = Texture::loadTexture(textureName);

	texture = Texture::solidDiffuse(255, 0, 0, 255);

	currentShader = Renderer::getInstance()->wireframe;

	allocate(6);

	vertpos(position[X] - width / 2.f, position[Y] - height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(position[X] - width / 2.f, position[Y] + height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(position[X] + width / 2.f, position[Y] + height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);

	vertpos(position[X] - width / 2.f, position[Y] - height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(position[X] + width / 2.f, position[Y] + height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(position[X] + width / 2.f, position[Y] - height / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);

	upload();
}

Sprite::~Sprite()
{
}
