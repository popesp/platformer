#pragma once


#include	"../../math/vec2f.h"
#include	"Shape.h"



class Circle : public Shape
{
public:
	Circle(vec2f position, float radius);
	~Circle();

	bool pointIn(vec2f point);
	bool collidingWith(const Shape* shape);

	void setRadius(float radius);
	float getRadius();

private:
	float radius;
	float radius2;
};