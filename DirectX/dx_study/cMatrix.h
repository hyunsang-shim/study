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
	public:
		std::vector<double> m_vecData;

	public:
		cRow();
		cRow(int nDimension);			//ok
		~cRow() {}
		void Add(double value);			//ok
		int GetRowSize();				//ok
		void Resize(int nDimension);	//ok
		double operator[] (int nIndex);	//ok
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
	cMatrix Minor(OUT int nRow, int nCol);	
	double Determinent();	
	double Cofactor(int nRow, int mCol);
	cMatrix Adjoint(); 
	cMatrix Inverse(OUT double& fDeterminent);
	
	//
	static cMatrix Translation(double x, double y, double z);
	static cMatrix Translation(cVector3& v);
	static cMatrix RotationX(double fAngle);
	static cMatrix RotationY(double fAngle);
	static cMatrix RotationZ(double fAngle);
	static cMatrix View(cVector3& vRyr, cVector3& vLookAt, cVector3 vUp);
	static cMatrix Projection(double fFovY, double fAspect, double fNearZ, double fFarZ);
	static cMatrix Viewport(double x, double y, double w, double h, double minZ, double maxZ);
	
	

private:
	std::vector<cRow> m_vecData_cols;
};

