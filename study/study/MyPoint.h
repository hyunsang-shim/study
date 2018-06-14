#pragma once
class MyPoint
{
public:
	MyPoint();
	MyPoint(double, double);
	~MyPoint();

	double getX();
	double getY();
	void setX(double);
	void setY(double);
	double getDistance(MyPoint);

private:
	double pX;
	double pY;
};

