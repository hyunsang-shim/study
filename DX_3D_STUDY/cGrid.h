#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

	void Setup();
	void DrawGrid();
	void DrawIndicator();
	void Render();
	RECT GetGridMinMax();

private:
	vector<ST_PC_VERTEX>		m_vecGridVertex;
	vector<ST_PC_VERTEX>		m_vecIndVertexX;
	vector<ST_PC_VERTEX>		m_vecIndVertexY;
	vector<ST_PC_VERTEX>		m_vecIndVertexZ;
	double						m_fMax;
	double						m_fMin;

};

