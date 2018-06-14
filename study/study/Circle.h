#ifndef CIRCLE_H
	#define CIRCLE_H
class Circle
{
public:	//없으면 자동으로 private이 된다.

	double radius;

	Circle();
	~Circle();
	Circle(double);

	double getArea();
};
#endif