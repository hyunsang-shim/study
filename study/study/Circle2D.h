#ifndef CIRCLE2D_H
#define CIRCLE2D_H

class Circle2D
{
public:
	Circle2D();
	Circle2D(double x, double y, double radius);

	double getPosX();
	void setPosX(double X);
	double getPosY();
	void setPosY(double Y);

	double getRadius();
	
	double getArea();
	double getPerimeter();

	bool contains(double x, double y);
	bool contains(const Circle2D& circle);
	bool overlaps(const Circle2D& circle);	

	~Circle2D();

private:
	double PosX;
	double PosY;
	double area;
	double radius;
	double perimeter;
};

#endif