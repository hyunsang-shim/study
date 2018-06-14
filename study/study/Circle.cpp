#include "stdafx.h"
#include "Circle.h"


Circle::Circle()
{
}

Circle::~Circle()
{
}

Circle::Circle(double newRadius)
	:radius(newRadius)
{}


double Circle::getArea()
{
	return radius * radius * 3.14159;
}
