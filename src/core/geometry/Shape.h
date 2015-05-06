#pragma once
#include <vector>
#include "../../math/vec2f.h"
#include "../../math/mat3f.h"

class Shape
{
public:
	virtual bool pointIn(vec2f point) = 0;
	virtual bool collidingWith(Shape const * shape) = 0;

protected:
	vec2f position;
	std::vector<vec2f> points;
	mat3f transform;
};

