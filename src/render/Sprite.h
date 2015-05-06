#pragma once
#include "../math/vec2f.h"
#include "../core/geometry/Rectangle.h"
#include "../render/texture.h"
#include "../render/renderer.h"

class Sprite : public Renderable
{
public:
	Sprite();
	Sprite(vec2f position, float width, float height, const char* textureName);
	~Sprite();
	void setPosition(float x, float y);
	void translate(float x, float y);


private:
	vec2f position;
	Rectangle rect;
};

