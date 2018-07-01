#include "stdafx.h"
#include "MyPoint3D.h"
#include <cmath>

MyPoint3D::MyPoint3D()
{
	setX(0);
	setY(0);
	setZ(0);
}

MyPoint3D::MyPoint3D(double x, double y, double z)
{
	pX = x;
	pY = y;
	pZ = z;
}

void MyPoint3D::setZ(double pZ)
{
	this->pZ = pZ;
}

double MyPoint3D::getZ()
{
	return this->pZ;
}

double MyPoint3D::getDistance(MyPoint3D targetP)
{

	double a = this->pX - targetP.pX;
	double b = this->pY - targetP.pY;
	double c = this->pZ - targetP.pZ;

	double d = pow(pow(a, 2) + pow(b, 2) + pow(c, 2), 0.5);


	return d;


}
