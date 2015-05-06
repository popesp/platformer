#include "Rectangle.h"


Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
}


bool Rectangle::pointIn(vec2f point)
{
	(void)point;
	return false;
}

bool Rectangle::collidingWith(const Shape* shape)
{
	(void)shape;
	return false;
}