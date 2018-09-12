#include "stdafx.h"
#include "cVector3.h"

#define EPSILON		0.0001f

cVector3::cVector3()
{
}


cVector3::~cVector3()
{
}

cVector3::cVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool cVector3::operator==(cVector3 & vec)
{
	if ((float)abs(this->x - vec.x) <= EPSILON)
	{
		if ((float)abs(this->y - vec.y) <= EPSILON)
		{
			if ((float)abs(this->z - vec.z) <= EPSILON)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool cVector3::operator!=(cVector3 & vec)
{
	if ((float)abs(this->x - vec.x) <= EPSILON)
	{
		if ((float)abs(this->y - vec.y) <= EPSILON)
		{
			if ((float)abs(this->z - vec.z) <= EPSILON)
			{
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

cVector3 cVector3::operator+(cVector3 & vec)
{
	cVector3 ret;

	ret.x = this->x + vec.x;
	ret.y = this->y + vec.y;
	ret.z = this->z + vec.z;

	return ret;
}

cVector3 cVector3::operator-(cVector3 & vec)
{
	cVector3 ret;

	ret.x = this->x - vec.x;
	ret.y = this->y - vec.y;
	ret.z = this->z - vec.z;

	return ret;
}

cVector3 cVector3::operator*(float f)
{
	cVector3 ret;

	ret.x = this->x * f;
	ret.y = this->y * f;
	ret.z = this->z * f;

	return ret;
}

cVector3 cVector3::operator/(float f)
{
	cVector3 ret;

	ret.x = this->x / f;
	ret.y = this->y / f;
	ret.z = this->z / f;

	return ret;
}

void cVector3::operator=(cVector3 & vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	cVector3 ret;

	ret.x = (v1.y * v2.z - v1.z * v2.y);
	ret.y = (v1.x * v2.z - v1.z * v2.x);
	ret.z = (v1.x * v2.y - v1.y * v2.x);

	return ret;
}

float cVector3::Length()
{

	return pow(pow(this->x,2) + pow(this->y,2) + pow(this->z,2),0.5);
}

cVector3 cVector3::Normalize()
{
	cVector3 ret;
	float leng = Length();
	ret.x = pow(pow(this->x / leng, 2), 0.5);
	ret.y = pow(pow(this->y / leng, 2), 0.5);
	ret.z = pow(pow(this->z / leng, 2), 0.5);

	return ret;
}
