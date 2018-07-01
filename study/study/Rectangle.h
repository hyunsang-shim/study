#pragma once
#include "GeomatricObject.h"

class cRectangle : public GeometricObject
{
public:
	cRectangle();
	cRectangle(double, double);
	cRectangle(double width, double height, const string& color, bool filled);

	
	void setWidth(double newWidth);
	double getWidth() const;

	void setHeight(double newHeight);
	double getHeight();

	double getArea();
	double getPerimeter();
	string toString();

	~cRectangle();

private:
	double width;
	double height;
};

