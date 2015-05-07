#include "Sprite.h"


Sprite::Sprite(vec2f pos, vec2f dim, const char* textureName)
	: Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_COL | SHADER_ATTRIBFLAG_TEX)
{
	vec2f_copy(this->dim, dim);
	vec2f_copy(this->pos, pos);
	vec2f_set(scale, 1.f, 1.f);
	rotation = 0.f;

	texture = Texture::loadTexture(textureName);
	texture->upload();

	currentShader = Renderer::getInstance()->texture;

	allocate(6);

	vertpos(-dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(0.f, 0.f);
	vertpos(-dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(0.f, 1.f);
	vertpos(dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(1.f, 1.f);

	vertpos(-dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(0.f, 0.f);
	vertpos(dim[X] / 2.f, dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(1.f, 1.f);
	vertpos(dim[X] / 2.f, -dim[Y] / 2.f);
	vertcol(1.f, 1.f, 1.f, 1.f);
	verttex(1.f, 0.f);

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