#pragma once
class cHexagon
{
public:
	cHexagon();
	~cHexagon();

	void Setup();
	void Render();
	vector<D3DXVECTOR3>			GetPoints();

private:
	vector<ST_PC_VERTEX>		m_vecHexagonVertex;

};

