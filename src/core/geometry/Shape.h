#pragma once
#include <vector>
#include "../../math/vec2f.h"
#include "../../math/mat3f.h"

class Shape
{
public:
	virtual ~Shape();

	virtual bool pointIn(vec2f point) = 0;
	virtual bool collidingWith(const Shape* shape) = 0;

	std::vector<float>* getPoints();

protected:
	vec2f position;
	std::vector<float> points;
	mat3f transform;
};

