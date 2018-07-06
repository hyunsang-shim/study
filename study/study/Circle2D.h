#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
public:
	Circle();
	Circle(double x, double y, double radius);

	double getPosX();
	void setPosX(double X);
	double getPosY();
	void setPosY(double Y);

	double getRadius();
	
	double getArea();
	double getPerimeter();

	bool contains(double x, double y);
	bool contains(const Circle& circle);
	bool overlaps(const Circle& circle);	

	~Circle();

private:
	double PosX;
	double PosY;
	double area;
	double radius;
	double perimeter;
};

#endif