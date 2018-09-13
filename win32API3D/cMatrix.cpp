#include "stdafx.h"
#include "cMatrix.h"


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
		double tmp = rand() % 100 / 10.0;
		tmp * (rand() % 3 == 0 ? -1 : 1);
		m_vecData.push_back(tmp);
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

	// ��� ���� ���� ������ ��� ��.
	// �ƴϸ� ���
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
		//�ƴϸ� ����ġ
		ret = false;

	return ret;
}

bool cMatrix::operator!=(cMatrix & mat)
{

	bool ret = true;

	// ��� ���� ���� ������ ����Ѵ�.
	// �ٸ��� ����ġ(true)
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
		//�ƴϸ� ����ġ
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
	
	// ���ؾ� �� ���� �� ��ŭ �ݺ� �ϴµ�
	for (int i = 0; i < this->Dimension(); i++)
	{
		// A�� �� �� ��ŭ
		for (int j = 0; j < this->Dimension(); j++)
		{
			// B�� �� ����� ���� ����
			for (int k = 0; k < this->Dimension(); k++)
			{
				// i = ���ؾ� �ϴ� ��
				// k = A����� ��
				// j = B����� ��
				tmp_sum += this->m_vecData_cols[i][k] * mat.m_vecData_cols[k][j];
			}

			// ���ؾ� �� ���� �� ���� �ִ´�.
			row.Add(tmp_sum);
			tmp_sum = 0;		//���� ���� �ʱ�ȭ��Ų��.
		}
		//���� ���������Ƿ�, ����� ���� �ִ´�.
		tmp.m_vecData_cols[i] = row;
		row.Resize(0);		//���� �־����Ƿ� �ʱ�ȭ �Ѵ�.
	}

	//���������� ������ ���� ��ȯ�Ѵ�.
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
	// ����� (Minor Matrix) ��ȯ��
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
		printf("������� �������� �ʽ��ϴ�.\n");
		return ret;
	}

	cMatrix Adj = Adjoint();

	ret = Adj * (1 / fDeterminent);

	return ret;
}

cMatrix cMatrix::Translation(double x, double y, double z)
{
	cMatrix ret(4);
	ret = cMatrix::Identity(4);

	printf("Identity(4)\n");
	for (int i = 0; i < ret.Dimension(); i++)
	{
		for (int j = 0; j < ret.Dimension(); j++)
		{
			printf("%.3f\t", ret[i][j]);
		}
		printf("\n");
	}


	ret[3][0] = x;
	ret[3][1] = y;
	ret[3][2] = z;
	ret[3][3] = 1;

	return ret;
}

cMatrix cMatrix::RotationX(double fAngle)
{

	return cMatrix();
}

cMatrix cMatrix::Viewport(double x, double y, double w, double h, double minZ, double maxZ)
{
	cMatrix ret(4);

	for (int i = 0; i < ret.Dimension(); i++)
	{
		for (int j = 0; j < ret.Dimension(); j++)
		{
			ret[i][j] = 0.0000f;
		}
	}

	ret[3][3] = 1;

	ret[0][0] = w / 2.0;
	ret[1][1] = ((-1) * h) / 2.0;
	ret[2][2] = maxZ - minZ;
	ret[3][0] = x + w / 2.0;
	ret[3][1] = y + h / 2.0;
	ret[3][2] = minZ;

	return ret;
}
