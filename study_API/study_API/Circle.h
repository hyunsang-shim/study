#ifndef CIRCLE_H
#define CIRCLE_H
#include <Windows.h>

class Circle
{
public:
	Circle();
	Circle(double x, double y, double radius);

	double getPosX();
	void setPosX(double X);
	double getPosY();	
	void setPosY(double Y);
	void overlaps(Circle& circle, const RECT &rectView);
	void setValid(bool isValid);
	void move(const RECT &rectView);
	void setDir(int dir);
	double getRadius();
	void setRadius(int radius);
	void setSpeedX(int speed);
	void setSpeedY(int speed);

	double getSpeedX();
	double getSpeedY();
	bool checkValid();	
	~Circle();

private:
	int PosX;
	int PosY;
	int radius;
	int speedX;
	int speedY;
	int Tick;
	int direction;
	bool isValid = false;
};

#endif