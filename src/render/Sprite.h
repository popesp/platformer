#pragma once
#include "../math/vec2f.h"
#include "../core/geometry/Rectangle.h"
#include "../render/texture.h"
#include "../render/renderer.h"

class Sprite : public Renderable
{
public:
	vec2f pos, scale;
	float rotation;

	Sprite(vec2f pos, vec2f dim, const char* textureName);
	~Sprite();

	void setPosition(float x, float y);
	void translate(float x, float y);

	void updateTransform();

private:
	vec2f dim;

	void calculateVerts();
};

