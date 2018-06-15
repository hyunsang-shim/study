#include "stdafx.h"
#include "Circle.h"

int Circle::numberOfObjects = 0;
Circle::Circle()
{
	radius = 1;
	numberOfObjects++;
}

Circle::~Circle()
{
}

Circle::Circle(double newRadius)
{
	radius = newRadius;
	numberOfObjects++;
}


double Circle::getArea()
{
	return radius * radius * 3.14159;
}

double Circle::getRadius()
{
	return radius;

}

void Circle::setRadius(double newRadius)
{
	radius = (newRadius >=0)? newRadius : 0;
}

int Circle::getNumberOfObjects()
{
	return numberOfObjects;
}