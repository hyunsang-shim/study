#include "stdafx.h"
#include "cMatrix.h"
#include "cVector3.h"


cMatrix::cMatrix()
{}

cMatrix::~cMatrix()
{}

cMatrix::cRow::cRow()
{}

cMatrix::cRow::cRow(int nDimension)
{
	for (int i = 0; i < nDimension; i++)
	{	
		m_vecData.push_back(0.0f);
	}
}

void cMatrix::cRow::Add(double value)
{
	m_vecData.push_back(value);
}

int cMatrix::cRow::GetRowSize()
{
	return m_vecData.size();
}

void cMatrix::cRow::Resize(int nDimension)
{
		m_vecData.resize(nDimension);
}

double& cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

cMatrix::cMatrix(int nDimension)
{		
	m_vecData_cols.resize(nDimension);

	for (int i = 0; i < nDimension; i++)
	{
		cMatrix::cRow tmp(nDimension);
		m_vecData_cols[i] = tmp;
	}
}

void cMatrix::Print()
{

	for (int i = 0; i < this->Dimension(); i++)
	{
		for (int j = 0; j < this->Dimension(); j++)
		{
			printf("\t%.1f", (m_vecData_cols[i])[j]);
		}
		printf("\n");
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData_cols.resize(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		cMatrix::cRow r(nDimension);
		m_vecData_cols[i] = r;
	}
}

int cMatrix::Dimension()
{
	
	return m_vecData_cols.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix ret(nDimension);

	for (int i = 0; i <nDimension; i++)
	{		
		for (int j = 0; j < nDimension; j++)
		{
			i == j ? ret[i][j] = 1 : ret[i][j] = 0;
		}
	}	

	return ret;
}

cMatrix::cRow& cMatrix::operator[](int nIndex)
{
	return m_vecData_cols[nIndex];
}

bool cMatrix::operator==(cMatrix & mat)
{

	bool ret = false;

	// 행과 열의 수가 같으면 계산 들어감.
	// 아니면 취소
	if (this->Dimension() == mat.Dimension())
	{
		for (int i = 0; i < this->Dimension(); i++)
		{
			for (int j = 0; j < this->Dimension(); j++)
			{
				if ((this->m_vecData_cols[i])[j] - (mat.m_vecData_cols[i])[j] <= EPSILON)
					ret = true;
				else
					ret = false;
			}
		}
	}
	else
		//아니면 불일치
		ret = false;

	return ret;
}

bool cMatrix::operator!=(cMatrix & mat)
{

	bool ret = true;

	// 행과 열의 수가 같으면 계산한다.
	// 다르면 불인치(true)
	if (this->Dimension() == mat.Dimension())
	{
		for (int i = 0; i < m_vecData_cols.size(); i++)
		{
			for (int j = 0; j < (this->m_vecData_cols.at(i)).GetRowSize(); j++)
			{
				if ((this->m_vecData_cols[i])[j] == (mat.m_vecData_cols[i])[j])
					ret = false;
				else
					ret = true;
			}
		}
	}
	else
		//아니면 불일치
		ret = true;


	return ret;
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;


	if (this->Dimension() == mat.Dimension())
	{
		for (int i = 0; i < this->Dimension(); i++)
		{			
			row.Resize(0);
			for (int j = 0; j < this->Dimension(); j++)
			{
				row.Add((this->m_vecData_cols[i])[j] + (mat.m_vecData_cols[i])[j]);
			}
			tmp.m_vecData_cols[i] = row;
		}
	}
	this->m_vecData_cols = tmp.m_vecData_cols;

	return tmp;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;


	if (this->Dimension() == mat.Dimension())
	{
		for (int i = 0; i < this->Dimension(); i++)
		{
			row.Resize(0);
			for (int j = 0; j < this->Dimension(); j++)
			{
				row.Add((this->m_vecData_cols[i])[j] - (mat.m_vecData_cols[i])[j]);
			}
			tmp.m_vecData_cols[i] = row;
		}
	}
	this->m_vecData_cols = tmp.m_vecData_cols;

	return tmp;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;
	double tmp_sum = 0;
	
	// 구해야 할 행의 수 만큼 반복 하는데
	for (int i = 0; i < this->Dimension(); i++)
	{
		// A의 행 수 만큼
		for (int j = 0; j < this->Dimension(); j++)
		{
			// B의 각 열들과 곱한 값을
			for (int k = 0; k < this->Dimension(); k++)
			{
				// i = 구해야 하는 행
				// k = A행렬의 행
				// j = B행렬의 열
				tmp_sum += this->m_vecData_cols[i][k] * mat.m_vecData_cols[k][j];
			}

			// 구해야 할 행의 각 열에 넣는다.
			row.Add(tmp_sum);
			tmp_sum = 0;		//넣은 값은 초기화시킨다.
		}
		//행이 구해졌으므로, 결과에 값을 넣는다.
		tmp.m_vecData_cols[i] = row;
		row.Resize(0);		//값을 넣었으므로 초기화 한다.
	}

	//최종적으로 구해진 값을 반환한다.
	this->m_vecData_cols = tmp.m_vecData_cols;
	return tmp;
}

cMatrix cMatrix::operator*(double scalar)
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;


	
	for (int i = 0; i < this->Dimension(); i++)
	{
		row.Resize(0);
		for (int j = 0; j < this->Dimension(); j++)
		{
			row.Add((this->m_vecData_cols[i])[j] * scalar);
		}
		tmp.m_vecData_cols[i] = row;
	}
	
	this->m_vecData_cols = tmp.m_vecData_cols;

	return tmp;
}

cMatrix cMatrix::operator/(double scalar)
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;



	for (int i = 0; i < this->Dimension(); i++)
	{
		row.Resize(0);
		for (int j = 0; j < this->Dimension(); j++)
		{
			row.Add((this->m_vecData_cols[i])[j] / scalar);
		}
		tmp.m_vecData_cols[i] = row;
	}

	this->m_vecData_cols = tmp.m_vecData_cols;

	return tmp;
}


void cMatrix::operator=(cMatrix & mat)
{	
	if (this->Dimension() == 0)
		this->Resize(mat.Dimension());

	for (int i = 0; i < mat.Dimension(); i++)
	{
		for (int j = 0; j < mat.Dimension(); j++)
		{
			((*this))[i][j] = mat[i][j];			
		}
	}
}

cMatrix cMatrix::Transpose()
{
	cMatrix tmp(this->Dimension());

	for (int i = 0; i < this->Dimension(); i++)
	{
		for (int j = 0; j < this->Dimension(); j++)
		{
			tmp[i][j] = m_vecData_cols[j][i];
		}
	}

	return tmp;
}


double cMatrix::Minor(int nRow, int nCol)
{
	// 소행렬 (Minor Matrix) 반환용
	cMatrix ret(this->Dimension() - 1);

	int nMinorCol = 0;
	int nMinorRow = 0;

	for (int i = 0; i < Dimension(); i++)
	{
		if (nRow == 1)
			continue;

		nMinorCol = 0;
		for (int j = 0; j < Dimension(); i++)
		{
			if (nCol == j) continue;

			ret[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}
	
	return ret.Determinent();
}

double cMatrix::Determinent()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}

	double fDeterminant = 0.0f;
	for (int i = 0; i < Dimension(); i++)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

double cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;

	if ((nRow + nCol) % 2 != 0)
		nConst = -1;
	
	return Minor(nRow, nCol) * nConst;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			ret[i][j] = Cofactor(j,1);
		}
	}

	return ret;
}

cMatrix cMatrix::Inverse(OUT double & fDeterminent)
{
	cMatrix ret = cMatrix::Identity(Dimension());

	fDeterminent = Determinent();
	if (-EPSILON < fDeterminent && fDeterminent < EPSILON)
	{
		printf("역행렬이 존재하지 않습니다.\n");
		return ret;
	}

	cMatrix Adj = Adjoint();

	ret = Adj * (1 / fDeterminent);

	return ret;
}

double cMatrix::ConvertToRadian(double Degree)
{
	double radian;

	radian = Degree * (PI / 180);

	return radian;

}

cMatrix cMatrix::Scale(double scaleX, double scaleY, double scaleZ)
{
	cMatrix ret;
	ret = Identity(4);

	ret[0][0] = scaleX;
	ret[1][1] = scaleY;
	ret[2][2] = scaleZ;
	ret[3][3] = 1.0f;

	return ret;
}

cMatrix cMatrix::Translation(double x, double y, double z)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);

	ret[3][0] = x;
	ret[3][1] = y;
	ret[3][2] = z;
	ret[3][3] = 1;

	return ret;
}

cMatrix cMatrix::Translation(cVector3 & v)
{		
	cMatrix ret(4);
	ret = cMatrix::Identity(4);

	ret[3][0] = v.x;
	ret[3][1] = v.y;
	ret[3][2] = v.z;
	ret[3][3] = 1;
	return ret;
}


cMatrix cMatrix::RotationX(double fAngle)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);
	double deg = cMatrix::ConvertToRadian(fAngle);
	
	ret[1][1] = cos(deg);
	ret[2][1] = -sin(deg);
	ret[1][2] = sin(deg);
	ret[2][2] = cos(deg);

	return ret;
}

cMatrix cMatrix::RotationY(double fAngle)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);
	double deg = cMatrix::ConvertToRadian(fAngle);
	ret[0][0] = cos(deg);
	ret[0][2] = sin(deg);
	ret[2][0] = -sin(deg);
	ret[2][2] = cos(deg);

	return ret;
}

cMatrix cMatrix::RotationZ(double fAngle)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);
	double deg = cMatrix::ConvertToRadian(fAngle);

	ret[0][0] = cos(deg);
	ret[0][1] = sin(deg);
	ret[1][0] = -sin(deg);
	ret[1][0] = cos(deg);

	return ret;
}

cMatrix cMatrix::Rotation(double fAngleX, double fAngleY, double fAngleZ)
{
	cMatrix ret;
	ret = Identity(4);

	ret = ret * RotationX(fAngleX);
	ret = ret * RotationY(fAngleY);
	ret = ret * RotationZ(fAngleZ);

	return ret;
}

cMatrix cMatrix::View(cVector3 & vEye, cVector3 & vLookAt, cVector3& vUp)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);	

	// W = (vLookAt - vEye) / ( vLookAt - vEye).length()
	// W는 새로운 Z축
	cVector3 w(0, 0, 0);
	w = vLookAt - vEye;
	w = w.Normalize();


	//u = j * W / (j * W).length()
	// 바라보는 방향(W)와 y축 벡터를 Cross 하면(직교시키면) -> 오른쪽 벡터를 구할 수 있다.
	// u = 오른쪽 벡터 = 새로운 X축
	cVector3 u(0, 0, 0);
	u = cVector3::Cross(vUp,w);
	u = u.Normalize();

	//v = w * u; (Cross곱. 직교 시키는 이유는 u와 같음)
	// v = 새로운 y축
	cVector3 v(0, 0, 0);
	v = cVector3::Cross(w, u);

	ret[0][0] = u.x;
	ret[1][0] = u.y;
	ret[2][0] = u.z;
	ret[3][0] = cVector3::Dot(vEye, u) * -1.0f;

	ret[0][1] = v.x;
	ret[1][1] = v.y;
	ret[2][1] = v.z;
	ret[3][1] = cVector3::Dot(vEye, v) * -1.0f;

	ret[0][2] = w.x;
	ret[1][2] = w.y;
	ret[2][2] = w.z;
	ret[3][2] = cVector3::Dot(vEye, w) * -1.0f;

	ret[0][3] = 0;
	ret[1][3] = 0;
	ret[2][3] = 0;
	ret[3][3] = 1;	


	return ret;
}

cMatrix cMatrix::Projection(double fFovY, double fAspect, double fNearZ, double fFarZ)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);
	
	double fScaleY = 1.0f / tanf(fFovY / 2.0f);
	double fScaleX = fScaleY / fAspect;	
	/*
	//원본
	ret[0][0] = fScaleX;
	ret[1][1] = fScaleY;
	ret[2][2] = fFarZ / (fFarZ - fNearZ);
	ret[2][3] = 1.0f;
	ret[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	ret[3][3] = 0.0f;
	*/
	ret[0][0] = fScaleX;
	ret[1][1] = fScaleY;
	ret[2][2] = fFarZ / (fFarZ - fNearZ);
	ret[2][3] = 1.0f;
	ret[3][2] = -1.0f * (fFarZ * (fNearZ / (fFarZ - fNearZ)));
	ret[3][3] = 0.0f;

	return ret;

}

cMatrix cMatrix::Viewport(double x, double y, double w, double h, double minZ, double maxZ)
{
	cMatrix ret(4);

	ret = cMatrix::Identity(4);

	ret[0][0] = w / 2.0f;
	ret[1][1] = (-1) * (h / 2.0f);
	ret[2][2] = maxZ - minZ;
	ret[3][0] = x + w / 2.0f;
	ret[3][1] = y + h / 2.0f;
	ret[3][2] = minZ;

	return ret;
}
