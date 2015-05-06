#include "Sprite.h"


Sprite::Sprite(vec2f position, float width, float height, const char* textureName)
{
	rect = Rectangle(position, width, height);
	texture->loadTexture(textureName);
	buf_verts = &rect.getPoints()->at(0);
}

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
}
