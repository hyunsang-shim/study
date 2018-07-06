#pragma once
#include "Circle.h"
#include <cmath>
#include <windows.h>


#define PI 3.14

Circle::Circle()
{
	this->PosX = 20;
	this->PosY = 20;
	this->radius = 10;
}

Circle::Circle(double x, double y, double radius)
{
	this->PosX = x;
	this->PosY = y;
	this->radius = radius;		
}

double Circle::getPosX()
{
	return PosX;
}

void Circle::setPosX(double X)
{
	this->PosX = X;
}

double Circle::getPosY()
{
	return PosY;
}

void Circle::setPosY(double Y)
{
	this->PosY = Y;
}

void Circle::overlaps(Circle & circle)
{
	double a = circle.PosX - this->getPosX();
	double b = circle.PosY - this->getPosY();
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	double dist_centers_comp = pow((circle.PosX - this->radius) + pow(circle.PosY - this->radius, 2), 0.5);

	if (dist_centers <= this->radius || dist_centers_comp <= this->radius)
	{
		this->setRadius(this->getRadius() * 2);
		circle.setValid(false);
	}

	// 커지는 순간 위치 보정 필요.
		
}

void Circle::setValid(bool isValid)
{
	this->isValid = isValid;
}

void Circle::move(long left, long top, long right, long bottom)
{
	setPosX(getPosX() + getSpeedX());
	setPosY(getPosY() + getSpeedY());

	//벽 충돌 시 팅김
	if (getPosX()-getRadius() < left || getPosX() + getRadius() > right)
		setSpeedX(-1 * getSpeedX());

	if (getPosY()-getRadius() < top || getPosY() + getRadius() > bottom)
		setSpeedY(-1 * getSpeedY());
}

void Circle::setDir(int dir)
{
	direction = dir;
}

double Circle::getRadius()
{
	return this->radius;
}

void Circle::setRadius(int radius)
{
	this->radius = radius;
}

void Circle::setSpeedX(int speed)
{
	this->speedX = speed;
}
void Circle::setSpeedY(int speed)
{
	this->speedY = speed;
}
double Circle::getSpeedX()
{
	return this->speedX;
}

double Circle::getSpeedY()
{
	return this->speedY;
}

bool Circle::checkValid()
{
	return isValid;
}


Circle::~Circle()
{
}
