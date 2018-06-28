#pragma once
#include "GeomatricObject.h"
class Triangle : public GeometricObject
{
public:
	Triangle();
	Triangle(double side1, double side2, double side3);
	Triangle(double side1, double side2, double side3, string color, bool filled);

	double getSide1();
	double getSide2();
	double getSide3();
	void setSide1(double side1);
	void setSide2(double side2);
	void setSide3(double side2);
	double getArea();
	double getPerimeter();
	string toString();

	~Triangle();

private:
	double side1;
	double side2;
	double side3;
};

