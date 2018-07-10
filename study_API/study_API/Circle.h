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
	void overlaps(HDC & hdc, Circle & circle, const RECT & R);
	void setValid(bool isValid);
	void move(const RECT &rectView);
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
	int eatcount;
	bool isValid = false;
};

#endif