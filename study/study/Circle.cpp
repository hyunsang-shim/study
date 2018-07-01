#pragma once
#include "stdafx.h"
#include "Circle.h"

int Circle::numberOfObjects = 0;	// ����� ����� static ������ �ʱ�ȭ �ؾ� �Ѵ�. (�������ʿ� �ϸ� �ȵ�)

Circle::Circle()
{
	radius = 1;
	numberOfObjects++;
}

Circle::~Circle()
{
	numberOfObjects--;
}

Circle::Circle(double newRadius)
{
	radius = newRadius;
	numberOfObjects++;
}

Circle::Circle(double radius, const string & color, bool filled)
{
	setRadius(radius);
	setColor(color);
	setFilled(filled);

	numberOfObjects++;
}


double Circle::getArea()
{
	return radius * radius * PI;
}

double Circle::getRadius()
{
	return radius;
}

void Circle::setRadius(double newRadius)
{
	radius = (newRadius >=0)? newRadius : 0;
}

double Circle::getPerimeter() const
{
	return 2 * radius * PI;
}

double Circle::getDiameter() const
{
	return 2 * PI;
}

bool Circle::operator<(Circle & secondCircle) const
{
	if (this->radius < secondCircle.getRadius())
		return true;
	else
		return false;
}

bool Circle::operator<=(Circle & secondCircle) const
{
	if (this->radius <= secondCircle.getRadius())
		return true;
	else
		return false;
}

bool Circle::operator>(Circle & secondCircle) const
{
	if (this->radius > secondCircle.getRadius())
		return true;
	else
		return false;
}

bool Circle::operator>=(Circle & secondCircle) const
{
	if (this->radius >= secondCircle.getRadius())
		return true;
	else
		return false;
}

bool Circle::operator==(Circle & secondCircle) const
{
	if (this->radius == secondCircle.getRadius())
		return true;
	else
		return false;
}

bool Circle::operator!=(Circle & secondCircle) const
{
	if (this->radius != secondCircle.getRadius())
		return true;
	else
		return false;
}

int Circle::getNumberOfObjects()
{
	return numberOfObjects;
}

string Circle::toString()
{
	return "Circle Object";
}
