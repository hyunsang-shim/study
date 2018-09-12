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

	// 행과 열의 수가 같으면 계산 들어감.
	// 아니면 취소
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

cMatrix cMatrix::operator/(cMatrix & mat)
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
				tmp_sum += this->m_vecData_cols[i][k] / mat.m_vecData_cols[k][j];
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


