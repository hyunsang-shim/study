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
	//vector<ST_PC_VERTEX>		m_vecGridVertex;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_X;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Y;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Z;			// ���ؽ� ������ ���� ����
	int							m_nNumLines;	// ���� ���� ���� �� ����
	int							m_nNumVertices_X;	// X ����� ���ؽ� �� ���� ����
	int							m_nNumVertices_Y;	// Y ����� ���ؽ� �� ���� ����
	int							m_nNumVertices_Z;	// Z ����� ���ؽ� �� ���� ����


	
	double						m_fMax;
	double						m_fMin;

};

