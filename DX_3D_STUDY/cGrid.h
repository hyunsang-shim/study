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
	LPDIRECT3DVERTEXBUFFER9		m_pVB;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_X;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Y;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Z;			// 버텍스 정보를 담을 버퍼
	int							m_nNumLines;	// 라인 수를 저장 할 변수
	int							m_nNumVertices_X;	// X 기즈모 버텍스 수 저장 변수
	int							m_nNumVertices_Y;	// Y 기즈모 버텍스 수 저장 변수
	int							m_nNumVertices_Z;	// Z 기즈모 버텍스 수 저장 변수


	
	double						m_fMax;
	double						m_fMin;

};

