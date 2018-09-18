#include "stdafx.h"
#include "cVector3.h"
#include "cMatrix.h"

class cMatrix;
#define EPSILON		0.0001f

cVector3::cVector3()
{
}


cVector3::~cVector3()
{
}

cVector3::cVector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool cVector3::operator==(cVector3 & vec)
{
	if ((double)abs(this->x - vec.x) <= EPSILON)
	{
		if ((double)abs(this->y - vec.y) <= EPSILON)
		{
			if ((double)abs(this->z - vec.z) <= EPSILON)
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
	if ((double)abs(this->x - vec.x) <= EPSILON)
	{
		if ((double)abs(this->y - vec.y) <= EPSILON)
		{
			if ((double)abs(this->z - vec.z) <= EPSILON)
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


cVector3 cVector3::operator*(double f)
{
	cVector3 ret;

	ret.x = this->x * f;
	ret.y = this->y * f;
	ret.z = this->z * f;

	return ret;
}

cVector3 cVector3::operator/(double f)
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

double cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	cVector3 ret;

	ret.x = (v1.y * v2.z - v1.z * v2.y);
	ret.y = (v1.z * v2.x - v1.x * v2.z);
	ret.z = (v1.x * v2.y - v1.y * v2.x);

	return ret;
}

double cVector3::Length()
{		
	return sqrtf(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
}

cVector3 cVector3::Normalize()
{
	cVector3 ret;
	double length = Length();
	ret.x = (*this).x / length;
	ret.y = (*this).y / length;
	ret.z = (*this).z / length;

	return ret;
}

cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{	
	cVector3 ret;	
	vector<double> vToVec;
	vector<double> tmp_calc(4,0);
	double x, y, z, w;
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1.0f;

	vToVec.push_back(x);
	vToVec.push_back(y);
	vToVec.push_back(z);
	vToVec.push_back(w);

	for (int i = 0; i < vToVec.size(); i++)
	{
		for (int j = 0; j < vToVec.size(); j++)
		{
			tmp_calc[i] += vToVec[j] * mat[j][i];
		}
	}
	w = x * mat[0][3] + y * mat[1][3] + z * mat[2][3] + mat[3][3];

	/*ret.x = tmp_calc[0] / w;
	ret.y = tmp_calc[1] / w;
	ret.z = tmp_calc[2] / w;*/	


	ret.x = tmp_calc[0] / w;
	ret.y = tmp_calc[1] / w;
	ret.z = tmp_calc[2] / w; 


	return ret;
}

cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 ret;

	ret.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0];
	ret.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1];
	ret.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2];

	return ret;
}
