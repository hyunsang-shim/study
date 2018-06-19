#include "stdafx.h"
#include "Rectangle2D.h"

extern double Get_Length(double, double, double, double);

Rectangle2D::Rectangle2D()
{
}

Rectangle2D::Rectangle2D(double center_x, double center_y, double width, double height)
{
	this->centerX = center_x;
	this->centerY = center_y;
	this->width = width;
	this->height = height;
}

double Rectangle2D::getArea()
{
	return width * height;
}

double Rectangle2D::getPerimeter()
{
	return 2*(height + width);
}

void Rectangle2D::setCenterX(double center_x)
{
	this->centerX = center_x;
}

double Rectangle2D::getCenterX()
{
	return centerX;
}

void Rectangle2D::setCenterY(double center_y)
{
	this->centerY = center_y;
}

double Rectangle2D::getCenterY()
{
	return centerY;
}

void Rectangle2D::setWidth(double width)
{
	this->width = width;
}

double Rectangle2D::getWidth()
{
	return width;
}

void Rectangle2D::setHeight(double height)
{
	this->height = height;
}

double Rectangle2D::getHeight()
{
	return height;
}

bool Rectangle2D::contains(double x, double y)
{
	if (Get_Length(centerX, 0, x,0) <= width/2 && Get_Length(0, centerY, 0, y) <= height/2)
		return true;
	else
		return false;
}

bool Rectangle2D::contains(const Rectangle2D & r)
{
	if (contains(r.centerX, r.centerY) 
		&& Get_Length(r.centerX, 0, r.centerX + r.width / 2, 0) <= centerX + width / 2 
		&& Get_Length(0, r.centerY, 0, r.centerY + r.height / 2) <= centerY + height / 2)
		return true;
	else
		return false;
}

bool Rectangle2D::overlaps(const Rectangle2D & r)
{
	if (contains(r.centerX, r.centerY)
		|| Get_Length(r.centerX, 0, r.centerX + r.width / 2, 0) <= centerX + width / 2
		|| Get_Length(0, r.centerY, 0, r.centerY + r.height / 2) <= centerY + height / 2)
		return true;
	else
		return false;
}


Rectangle2D::~Rectangle2D()
{
}
