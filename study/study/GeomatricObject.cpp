#include "GeomatricObject.h"

GeometricObject::GeometricObject()
{
	color = "white";
	filled = false;
}

GeometricObject::GeometricObject(const string& color, bool fill)
{
	this->color = color;
	this->setFilled(fill);
}

string GeometricObject::getColor() const
{
	return color;
}

void GeometricObject::setColor(const string & color)
{
	this->color = color;

}
bool GeometricObject::isFilled()
{
	return filled;
}
void GeometricObject::setFilled(bool filled)
{
	this->filled = filled;
}

string GeometricObject::toString() const
{
	return "Geometric Object";
}
