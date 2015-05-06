#include "Circle.h"


Circle::Circle(vec2f position, float radius)
{
	vec2f_copy(this->position, position);
	setRadius(radius);
}

Circle::~Circle()
{
}


bool Circle::pointIn(vec2f point)
{
	vec2f diff;

	vec2f_subtractn(diff, point, position);

	if (vec2f_length2(diff) < radius2)
		return true;

	return false;
}

bool Circle::collidingWith(const Shape* shape)
{
	// TODO
	(void)shape;
	return false;
}


void Circle::setRadius(float radius)
{
	this->radius = radius;
	this->radius2 = radius * radius;
}

float Circle::getRadius()
{
	return radius;
}