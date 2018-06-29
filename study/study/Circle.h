#ifndef CIRCLE_H
	#define CIRCLE_H
#include "GeomatricObject.h"

class Circle : public GeometricObject
{
public:	//없으면 자동으로 private이 된다.
	Circle();	
	Circle(double);
	Circle(double radius, const string& color, bool filled);
	double getArea();
	double getRadius();

	void setRadius(double);
	
	double getPerimeter() const;
	double getDiameter() const;

	bool operator<(Circle& secondCircle) const;
	bool operator<=(Circle& secondCircle) const;
	bool operator>(Circle& secondCircle) const;
	bool operator>=(Circle& secondCircle) const;
	bool operator==(Circle& secondCircle) const;
	bool operator!=(Circle& secondCircle) const;
	static int getNumberOfObjects();
	string toString();

	~Circle();
	
private:
	double radius;
	static int numberOfObjects;
};
#endif