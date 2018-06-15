#ifndef CIRCLE_H
	#define CIRCLE_H
class Circle
{
public:	//없으면 자동으로 private이 된다.
	Circle();	
	Circle(double);
	double getArea(); 
	double getRadius();
	void setRadius(double);
	static int getNumberOfObjects();
	~Circle();

	

private:
	double radius;
	static int numberOfObjects;
};
#endif