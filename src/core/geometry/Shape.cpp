#include "Shape.h"


Shape::~Shape()
{

}

std::vector<float>* Shape::getPoints()
{
	return &points;
}