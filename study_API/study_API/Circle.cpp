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
	this->eatcount = 0;
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

void Circle::overlaps(HDC& hdc, Circle & circle, const RECT &R)
{
	//����� ���ϰ� �ϱ� ���ؼ�
	double a = circle.PosX - this->getPosX();
	double b = circle.PosY - this->getPosY();

	//�� ���� ������ �Ÿ�
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	// ��� ���� �Ϻΰ� ������ �ܰ��� ���ʿ� �ִ��� Ȯ���� ���� ��  
	double dist_centers_comp = pow((circle.PosX - this->radius) + pow(circle.PosY - this->radius, 2), 0.5);

	//�´�ų� �����̶� ��ġ��
	if (dist_centers <= this->getRadius()+circle.getRadius())
	{
		//ū ���� �Դ´�!
		if (circle.radius <= this->radius)
		{
			this->radius = this->radius * 2 / 3 + circle.radius * 2 / 3;
			this->setSpeedX(this->getSpeedX() * 2 / 3 + circle.getSpeedX() / 3);
			circle.setSpeedY(this->getSpeedY() * 2 / 3 + circle.getSpeedY() / 3);

			if (this->getSpeedX() == 0)
				this->setSpeedX(rand() % 3 + 3 * (rand() % 201 - 100) / 100);

			circle.setValid(false);
		}
		else if (circle.radius > this->radius)
		{
			circle.radius = circle.radius * 2 / 3 + this->radius * 2 / 3;
			circle.setSpeedX(circle.getSpeedX() * 2 / 3 + this->getSpeedX() / 3);
			circle.setSpeedY(circle.getSpeedY() * 2 / 3 + this->getSpeedY() / 3);
			
			if (circle.getSpeedX() == 0)
				circle.setSpeedX(rand() % 3 + 3 * (rand() % 201 - 100) / 100);

			if (circle.getSpeedY() == 0)
				circle.setSpeedY(rand() % 3 + 3 * (rand() % 201 - 100) / 100);
			this->setValid(false);
		}

		//��� ���� ��Ȱ��ȭ ��Ų��.
		circle.setValid(false);
	}	

	// Ŀ�� ���� ȭ�� ���� ���� �� ������ �������� �о� �־� �ش�.
	if (getPosX() - getRadius() <= R.left)
		setPosX(R.left + getRadius() + getSpeedX());
	else if (getPosX() + getRadius() >= R.right)
		setPosX(R.right - getRadius() - getSpeedX());

	if (getPosY() - getRadius() <= R.top)
		setPosY(R.bottom - getRadius() - getSpeedX());
	else if (getPosY() + getRadius() >= R.bottom)
		setPosY(R.top + getRadius() + getSpeedX());

	//�ʹ� Ŀ������ �����.
	if (this->getRadius() > 30)
	{
		this->setValid(false);
	}
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
	if (getPosX() - getRadius() <= R.left || getPosX() + getRadius() >= R.right)
	{
		if (getPosX() - getRadius() <= R.left)
			setPosX(R.left + getRadius() + 1);
		else
			setPosX(R.right - getRadius() - 1);

		setSpeedX(-1 * getSpeedX());
	}

	if (getPosY() - getRadius() <= R.top || getPosY() + getRadius() >= R.bottom)
	{
		if (getPosY() - getRadius() <= R.top)
			setPosY(R.top + getRadius() + 1);
		else
			setPosY(R.bottom - getRadius() - 1);

		setSpeedY(-1 * getSpeedY());
	}
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
