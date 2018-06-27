#ifndef CIRCLE_H
	#define CIRCLE_H
class Circle
{
public:	//������ �ڵ����� private�� �ȴ�.
	Circle();	
	Circle(double);
	double getArea(); 
	double getRadius();
	void setRadius(double);

	bool operator<(Circle& secondCircle) const;
	bool operator<=(Circle& secondCircle) const;
	bool operator>(Circle& secondCircle) const;
	bool operator>=(Circle& secondCircle) const;
	bool operator==(Circle& secondCircle) const;
	bool operator!=(Circle& secondCircle) const;
	static int getNumberOfObjects();
	~Circle();
	
private:
	double radius;
	static int numberOfObjects;
};
#endif