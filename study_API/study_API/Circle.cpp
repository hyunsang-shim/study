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
	//����� ���ϰ� �ϱ� ���ؼ�
	double a = circle.PosX - this->getPosX();
	double b = circle.PosY - this->getPosY();
	//�� ���� ������ �Ÿ�
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	// ��� ���� �Ϻΰ� ������ �ܰ��� ���ʿ� �ִ��� Ȯ���� ���� ��  
	double dist_centers_comp = pow((circle.PosX - this->radius) + pow(circle.PosY - this->radius, 2), 0.5);

	//�´�ų� �����̶� ��ġ��
	if (dist_centers <= this->radius || dist_centers_comp <= this->radius)
	{
		//���� ���� ũ�⸦ Ű���
		this->setRadius(this->getRadius() * 1.2);
		//��� ���� ��Ȱ��ȭ ��Ų��.
		circle.setValid(false);
	}

	// Ŀ�� ���� ȭ�� ���� ���� �� ������ �������� �о� �־� �ش�.
	if (getPosX() - getRadius() < R.left || getPosX() + getRadius() > R.right)
		setPosX(R.left + getRadius() + getSpeedX());

	if (getPosY() - getRadius() < R.top || getPosY() + getRadius() > R.bottom)
		setPosY(R.bottom - getRadius() - getSpeedX());

	// Ŀ���� ���� ��ġ ���� �ʿ�.
		
}

void Circle::setValid(bool isValid)
{
	this->isValid = isValid;
}

void Circle::move(const RECT &R)
{
	setPosX(getPosX() + getSpeedX());
	setPosY(getPosY() + getSpeedY());

	//�� �浹 �� �ñ�
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
