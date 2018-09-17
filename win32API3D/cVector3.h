#pragma once

class cMatrix;

class cVector3
{
public:
	cVector3();
	~cVector3();

	
	cVector3(double x, double y, double z);
	double x, y, z;


	bool operator==(cVector3& vec);
	bool operator!=(cVector3& evc);
	cVector3 operator+(cVector3& vec);
	cVector3 operator-(cVector3& vec);	
	cVector3 operator*(double f);
	cVector3 operator/(double f);
	void operator=(cVector3& vec);

	static double Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	double Length();
	cVector3 Normalize();

	static cVector3 TransformCoord(cVector3& v, cMatrix& mat);	//ok
	static cVector3 TransformNormal(cVector3& v, cMatrix& mat);


};

