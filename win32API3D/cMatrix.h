#pragma once
#include "stdafx.h"

class cVector3;

class cMatrix
{
public:
	cMatrix();
	~cMatrix();
	
private:
	class cRow
	{
	private:
		std::vector<double> m_vecData;

	public:
		cRow();
		cRow(int nDimension);			//ok
		~cRow() {}
		void Add(double value);			//ok
		int GetRowSize();				//ok
		void Resize(int nDimension);	//ok
		double& operator[] (int nIndex);	//ok
	};

public :
	cMatrix(int nDimension);

	void Print();						// ok
	void Resize(int nDimension);		// ok
	int Dimension();					// ok

	static cMatrix Identity(int nDimention);	// ok

	cRow& operator[] (int nIndex);		// ok
	bool operator==(cMatrix& mat);		// ok
	bool operator!=(cMatrix& mat);		// ok
	cMatrix operator+(cMatrix& mat);	// ok
	cMatrix operator-(cMatrix& mat);	// ok
	cMatrix operator*(cMatrix& mat);	// ok
	cMatrix operator*(double scalar);	// ok	
	cMatrix operator/(double scalar);	// ok
	void operator=(cMatrix& mat);		// ok
	cMatrix Transpose();				// ok		
	double Minor(int nRow, int nCol);	
	double Determinent();	
	double Cofactor(int nRow, int mCol);
	cMatrix Adjoint(); 
	cMatrix Inverse(OUT double& fDeterminent);
	
	
	
	//
	static double ConvertToRadian(double Degree);
	static cMatrix Scale(double scaleX, double scaleY, double scaleZ);
	static cMatrix RotationX(double fAngle);							// ok
	static cMatrix RotationY(double fAngle);							// ok
	static cMatrix RotationZ(double fAngle);							// ok
	static cMatrix Rotation(double fAngleX, double fAngleY, double fAngleZ);
	static cMatrix Translation(double x, double y, double z);			// ok
	static cMatrix Translation(cVector3& v);							// ok
	static cMatrix View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);						// ok
	static cMatrix Projection(double fFovY, double fAspect, double fNearZ, double fFarZ);		// 
	static cMatrix Viewport(double x, double y, double w, double h, double minZ, double maxZ);	// ok

	

private:
	std::vector<cRow> m_vecData_cols;
};

