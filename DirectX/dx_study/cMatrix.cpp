#include "stdafx.h"
#include "cMatrix.h"


cMatrix::cMatrix()
{
}


cMatrix::~cMatrix()
{
}

cMatrix::cRow::cRow()
{
}

cMatrix::cRow::cRow(int nDimension)
{
	for (int i = 0; i < nDimension; i++)
	{
		float tmp = rand() % 100 / 10.0;
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
	if (nDimension == 0)
		m_vecData.clear();
	else 
		m_vecData.resize(nDimension);
}

float cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData.at(nIndex);
}

cMatrix::cMatrix(int nDimension)
{
	for (int i = 0; i < nDimension; i++)
	{
		m_vecData_cols.push_back(cRow(nDimension));
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
	for (int i = 0; i < m_vecData_cols.size(); i++)
		m_vecData_cols[i].Resize(nDimension);

	m_vecData_cols.resize(nDimension);

}

int cMatrix::Dimension()
{
	
	return m_vecData_cols.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix tmp(nDimension);
	cMatrix::cRow row = { 0 };

	for (int i = 0; i <nDimension; i++)
	{
		row.Resize(0);
		for (int j = 0; j < nDimension; j++)
		{
			if (j == i)
			{
				row.Add(1);
			}
			else
				row.Add(0);
		}
		tmp.m_vecData_cols[i] = row;
	}	

	return tmp;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	return m_vecData_cols.at(nIndex);
}

bool cMatrix::operator==(cMatrix & mat)
{

	bool ret = false;

	// ��� ���� ���� ������ ��� ��.
	// �ƴϸ� ���
	if (this->Dimension() == mat.Dimension())
	{
		for (int i = 0; i < m_vecData_cols.size(); i++)
		{
			for (int j = 0; j < (this->m_vecData_cols.at(i)).GetRowSize(); j++)
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

cMatrix cMatrix::operator/(cMatrix & mat)
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
				tmp_sum += this->m_vecData_cols[i][k] / mat.m_vecData_cols[k][j];
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
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;

	for (int i = 0; i < mat.Dimension(); i++)
	{
		row.Resize(0);
		for (int j = 0; j < mat.Dimension(); j++)
		{
			row.Add((mat.m_vecData_cols[i])[j]);
		}
		tmp.m_vecData_cols[i] = row;
	}

	this->m_vecData_cols = tmp.m_vecData_cols;
}

cMatrix cMatrix::Transpose()
{
	cMatrix tmp(this->Dimension());
	cMatrix::cRow row;
	
	for (int i = 0; i < this->Dimension(); i++)
	{
		row.Resize(0);
		for (int j = 0; j < this->Dimension(); j++)
		{
			row.Add(m_vecData_cols[j][i]);
		}
		tmp.m_vecData_cols[i] = row;
	}
	
	this->m_vecData_cols = tmp.m_vecData_cols;

	return tmp;
	
}


cMatrix cMatrix::Minor(int nRow, int nCol)
{
	cMatrix minor(this->Dimension() - 1);
	std::vector<cRow> row;

	for (int i = 0; i < this->Dimension(); i++)
	{
		for (int j = 0; j < this->Dimension(); j++)
		{
			if (i != nRow && j != nCol)
			{
				row.Add(m_vecData_cols[i][j]);
			}

			minor.m_vecData_cols[i][j] = row[i][j];
		}

	}
		return ;
}

double cMatrix::Determinent()
{
	double det = 0.0f;

	for (int i = 0; i < this->Dimension(); i++)
	{
		this->m_vecData_cols[0][i] * 
	}

	return det;
}


