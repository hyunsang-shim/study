#include "Throne.h"
#include <vector>


cThrone::cThrone()
{
}

bool cThrone::getFlag()
{
	return this->Flag;
}

void cThrone::setFlag(int flag)
{
	this->Flag = flag;
}

double cThrone::getCenterX()
{
	return this->CenterX;
}

double cThrone::getCenterY()
{
	return this->CenterY;
}

double cThrone::getSize()
{
	return this->Size;
}

double cThrone::getSizeMin()
{
	return this->sizeMin;
}

double cThrone::getSizeMax()
{
	return this->sizeMax;
}
double cThrone::getSizeMod()
{
	return this->sizeMod;
}

void cThrone::DrawObject(HDC hdc, LPARAM lparam, double size)
{
	double x = LOWORD(lparam);
	double y = HIWORD(lparam);
	size = 10;	
	Ellipse(hdc, x - size, x - size, x + size, x + size);
}

cThrone::~cThrone()
{
}
