#ifndef CIRCLE_H
	#define CIRCLE_H
class Circle
{
public:	//������ �ڵ����� private�� �ȴ�.

	double radius;

	Circle();
	~Circle();
	Circle(double);

	double getArea();
};
#endif