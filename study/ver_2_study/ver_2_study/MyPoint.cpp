#include "stdafx.h"
#include "MyPoint.h"
#include <cmath>


MyPoint::MyPoint()
{
	pX = 1;
	pY = 1;
}

MyPoint::MyPoint(double new_pX, double new_pY)
{
	pX = new_pX;
	pY = new_pY;
}

MyPoint::~MyPoint()
{
}

double MyPoint::getX()
{
	return pX;
}
void MyPoint::setX(double New_pX)
{
	pX = New_pX;
}
double MyPoint::getY()
{
	return pY;
}
void MyPoint::setY(double New_pY)
{
	pY = New_pY;
}

double MyPoint::getDistance(MyPoint targetP)
{
	//직선의 거리
	/*
	점 A(x1, y1)와 점 B(x2, y2)사이의 거리 = 	root( ( x2 - x1 ) ^2 + ( y2 - y1 ) ^2 )
	*/
	double a = targetP.pX - pX;
	double b = targetP.pY - pY;

	return pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
}
