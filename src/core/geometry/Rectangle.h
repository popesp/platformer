#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	~Rectangle();

	bool pointIn(vec2f point);
	bool collidingWith(const Shape* shape);
};

