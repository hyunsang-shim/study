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

void Circle::overlaps(Circle & circle, const RECT &R)
{
	//계산을 편리하게 하기 위해서
	double a = circle.PosX - this->getPosX();
	double b = circle.PosY - this->getPosY();
	//두 중점 사이의 거리
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	// 대상 원의 일부가 원본의 외각선 안쪽에 있는지 확일을 위한 값  
	double dist_centers_comp = pow((circle.PosX - this->radius) + pow(circle.PosY - this->radius, 2), 0.5);

	//맞닿거나 조금이라도 겹치면
	if (dist_centers <= this->radius || dist_centers_comp <= this->radius)
	{
		//원본 원의 크기를 키우고
		this->setRadius(this->getRadius() * 1.2);
		//대상 원을 비활성화 시킨다.
		circle.setValid(false);
	}

	// 커진 원이 화면 밖을 나갈 수 있으니 안쪽으로 밀어 넣어 준다.
	if (getPosX() - getRadius() < R.left || getPosX() + getRadius() > R.right)
		setPosX(R.left + getRadius() + getSpeedX());

	if (getPosY() - getRadius() < R.top || getPosY() + getRadius() > R.bottom)
		setPosY(R.bottom - getRadius() - getSpeedX());

	// 커지는 순간 위치 보정 필요.
		
}

void Circle::setValid(bool isValid)
{
	this->isValid = isValid;
}

void Circle::move(const RECT &R)
{
	setPosX(getPosX() + getSpeedX());
	setPosY(getPosY() + getSpeedY());

	//벽 충돌 시 팅김
	if (getPosX()-getRadius() < R.left || getPosX() + getRadius() > R.right)
		setSpeedX(-1 * getSpeedX());

	if (getPosY()-getRadius() < R.top || getPosY() + getRadius() > R.bottom)
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
