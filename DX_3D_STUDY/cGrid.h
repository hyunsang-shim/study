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
	LPDIRECT3DVERTEXBUFFER9		m_pVB;					// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVBforIB;				// �ε��� ���ۿ� ���ؽ� ����
	LPDIRECT3DINDEXBUFFER9		m_pIB;					// �ε��� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_X;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Y;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Z;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_XforIB;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_YforIB;			// ���ؽ� ������ ���� ����
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_ZforIB;			// ���ؽ� ������ ���� ����
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_X_IB;					// �ε��� ����
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_Y_IB;					// �ε��� ����
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_Z_IB;					// �ε��� ����
	int							m_nNumLines;			// ���� ���� ���� �� ����
	int							m_nNumVertices_X;		// X ����� ���ؽ� �� ���� ����
	int							m_nNumVertices_Y;		// Y ����� ���ؽ� �� ���� ����
	int							m_nNumVertices_Z;		// Z ����� ���ؽ� �� ���� ����
	int							m_nNumIndex_X;		// X ����� ���ؽ� �� ���� ����
	int							m_nNumIndex_Y;		// Y ����� ���ؽ� �� ���� ����
	int							m_nNumIndex_Z;		// Z ����� ���ؽ� �� ���� ����


	
	double						m_fMax;
	double						m_fMin;

};

