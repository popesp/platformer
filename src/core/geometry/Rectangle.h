#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(vec2f position, float width, float height);
	~Rectangle();

	bool pointIn(vec2f point);
	bool collidingWith(const Shape* shape);
	void setPosition(float x, float y);
	void setWidth(float width);
	void setHeight(float height);
	
private:
	float width;
	float height;

	void calculatePoints();
};

