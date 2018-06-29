#pragma once
#include "MyPoint.h"

class MyPoint3D :public MyPoint
{
public :
	MyPoint3D();
	MyPoint3D(double x, double y, double z);
	void setZ(double pZ);
	double getZ();
	double getDistance(MyPoint3D);

private:
	double pX; 
	double pY;
	double pZ;
	
	

};