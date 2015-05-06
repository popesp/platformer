#include "Rectangle.h"


Rectangle::Rectangle()
{
}

Rectangle::Rectangle(vec2f position, float width, float height)
{
	this->position[X] = position[X];
	this->position[Y] = position[Y];
	this->width = width;
	this->height = height;
	calculatePoints();
}

Rectangle::~Rectangle()
{
}

void Rectangle::setPosition(float x, float y)
{
	this->position[X] = x;
	this->position[Y] = y;
	calculatePoints();
}

void Rectangle::setWidth(float width)
{
	this->width = width;
	calculatePoints();
}

void Rectangle::setHeight(float height)
{
	this->height = height;
	calculatePoints();
}

void Rectangle::calculatePoints()
{
	points.clear();

	float x = position[X];
	float y = position[Y];

	points.push_back(x);
	points.push_back(y);

	points.push_back(x + width);
	points.push_back(y);

	points.push_back(x + width);
	points.push_back(y - height);

	points.push_back(x);
	points.push_back(y - height);
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