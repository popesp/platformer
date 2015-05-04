#include "Vector2.h"

Vector2::Vector2(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector2::Vector2()
{
	zero();
}

void Vector2::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector2::zero()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector2::~Vector2()
{
}
