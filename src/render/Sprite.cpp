#include "Sprite.h"


Sprite::Sprite(const char* textureName)
	:Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIB_POS | SHADER_ATTRIB_TEX)
{
	texture->loadTexture(textureName);
}

Sprite::Sprite(vec2f position, float width, float height, const char* textureName)
	:Renderable(RENDER_MODE_TRIANGLES, SHADER_ATTRIB_POS | SHADER_ATTRIB_TEX)
{
	rect = Rectangle(position, width, height);
	texture = Texture::loadTexture(textureName);

	currentShader = Renderer::getInstance()->texture;
	//buf_verts = &rect.getPoints()->at(0);
}

Sprite::~Sprite()
{
}
