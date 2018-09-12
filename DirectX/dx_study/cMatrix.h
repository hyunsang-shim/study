#pragma once
#include <windows.h>
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
		float operator[] (int nIndex);	//ok
	};

public :
	cMatrix(int nDimension);

	void Print();						//ok
	void Resize(int nDimension);		//ok
	int Dimension();					//ok

	static cMatrix Identity(int nDimention);	//ok

	cRow& operator[] (int nIndex);		//ok
	bool operator==(cMatrix& mat);		//ok
	bool operator!=(cMatrix& mat);		//ok
	cMatrix operator+(cMatrix& mat);	//ok
	cMatrix operator-(cMatrix& mat);	//ok
	cMatrix operator*(cMatrix& mat);	//ok
	cMatrix operator*(double scalar);	//ok
	cMatrix operator/(cMatrix& mat);	//ok
	cMatrix operator/(double scalar);	//ok
	void operator=(cMatrix& mat);		//ok
	cMatrix Transpose();				// ok
	cMatrix Inverse(OUT double& fDeterminent);
	double Determinent();				
	cMatrix adjoint();
	float Cofactor(int nRow, int mCol);
	float Minor(int nRow, int nCol);

private:
	std::vector<cRow> m_vecData_cols;
};

