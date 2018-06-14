#pragma once
class cRectangle
{
public:
	cRectangle();
	cRectangle(double, double);
	
	void setWidth(double newWidth);
	double getWidth();

	void setHeight(double newHeight);
	double getHeight();

	double getArea();
	double getPerimeter();

	~cRectangle();

private:
	double width;
	double height;
};

