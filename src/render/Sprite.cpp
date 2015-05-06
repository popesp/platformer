#include "Sprite.h"


Sprite::Sprite(const char* textureName)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_TEX)
{
	texture->loadTexture(textureName);
}

Sprite::Sprite(vec2f pos, vec2f dim, const char* textureName)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_COL)
{
	vec2f_copy(this->pos, pos);
	vec2f_copy(this->dim, dim);
	vec2f_set(scale, 1.f, 1.f);
	rotation = 0.2f;

	texture = Texture::solidDiffuse(255, 0, 0, 255);
	currentShader = Renderer::getInstance()->wireframe;

	allocate(6);

	vertpos(-dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(-dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);

	vertpos(-dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	vertpos(dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);

	upload();
}

Sprite::~Sprite()
{
	delete texture;
}


void Sprite::updateTransform()
{
	mat3f_translate(transform, pos[X], pos[Y]);
	mat3f_rotatemul(transform, rotation);
	mat3f_scalemul(transform, scale[X], scale[Y]);
}