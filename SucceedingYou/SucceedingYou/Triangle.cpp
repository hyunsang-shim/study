#pragma once
#include "Triangle.h"
#include <cmath>
#include <windows.h>

cTriangle::cTriangle()
{
	double x = 20;
	double y = 20;
	double size = 10;

	this->points[0].x = x;
	this->points[0].y = y - size;

	this->points[1].x = size * cos(120 * 3.14 / 180);
	this->points[1].y = size * sin(120 * 3.14 / 180);

	this->points[2].x = size * cos(120 * 3.14 / 180);
	this->points[2].y = size * sin(120 * 3.14 / 180);
}

cTriangle::cTriangle(LPARAM lparam, int Flag)
{
	double x = LOWORD(lparam);
	double y = HIWORD(lparam);
	double mod = Flag * this->getSizeMod();
	
	this->points[0].x = x + (this->getSize() + mod);
	this->points[0].y = y - (this->getSize() + mod);

	this->points[1].x = (this->getSize() + mod) * cos(120 * 3.14 / 180);
	this->points[1].y = (this->getSize() + mod) * sin(120 * 3.14 / 180);

	this->points[2].x = (this->getSize() + mod) * cos(240 * 3.14 / 180);
	this->points[2].y = (this->getSize() + mod) * sin(240 * 3.14 / 180);
}

cTriangle::~cTriangle()
{
}

void cTriangle::setPoints(int idx, LPARAM lparam, int Flag)
{

	double centerX = LOWORD(lparam);
	double centerY = HIWORD(lparam);
	double mod = Flag * this->getSizeMod();

	this->points[0].x = centerX;
	this->points[0].y = centerY - this->mySize;

	this->points[1].x = centerX + this->mySize * cos(120*3.14 / 180);
	this->points[1].y = centerY + (this->mySize * sin(120*3.14 / 180) ) * mod;

	this->points[2].x = centerX + this->mySize * cos(240*3.14 / 180);
	this->points[2].y = centerY + (this->mySize * sin(240 * 3.14 / 180)) * mod;
/*
	this->points[0].x = 100;
	this->points[0].y = 100;
	this->points[1].x = 40;
	this->points[1].y = 200;
	this->points[0].x = 160;
	this->points[0].y = 200;*/

	this->mySize += mod;
}

void cTriangle::Draw(HDC hdc, LPARAM lparam)
{
	Ellipse(hdc, 0,0, 200,200);
	//POINT tmp[3] = { {100,100},{40,200},{160,200} };
	
		
	Polygon(hdc, this->points, 3);

}
