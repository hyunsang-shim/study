#include "stdafx.h"
#include "Rectangle.h"

cRectangle::cRectangle()
{
	height = 1;
	width = 1;
}

cRectangle::cRectangle(double newWidth, double newHeight)
{
	width = newWidth;
	height = newHeight;
}

cRectangle::~cRectangle()
{
}


void cRectangle::setWidth(double newWidth)
{
	width = newWidth;
}
double cRectangle::getWidth()
{
	return width;
}

void cRectangle::setHeight(double newHeight)
{
		height = newHeight;
}
double cRectangle::getHeight()
{
	return height;
}
double cRectangle::getArea()
{
	return width * height;
}
double cRectangle::getPerimeter()
{
	return 2 * (width + height);
}