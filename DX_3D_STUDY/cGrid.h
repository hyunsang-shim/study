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
	LPDIRECT3DVERTEXBUFFER9		m_pVB;					// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVBforIB;				// 인덱스 버퍼용 버텍스 버퍼
	LPDIRECT3DINDEXBUFFER9		m_pIB;					// 인덱스 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_X;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Y;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_Z;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_XforIB;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_YforIB;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Gizmo_ZforIB;			// 버텍스 정보를 담을 버퍼
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_X_IB;					// 인덱스 버퍼
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_Y_IB;					// 인덱스 버퍼
	LPDIRECT3DINDEXBUFFER9		m_pVB_Gizmo_Z_IB;					// 인덱스 버퍼
	int							m_nNumLines;			// 라인 수를 저장 할 변수
	int							m_nNumVertices_X;		// X 기즈모 버텍스 수 저장 변수
	int							m_nNumVertices_Y;		// Y 기즈모 버텍스 수 저장 변수
	int							m_nNumVertices_Z;		// Z 기즈모 버텍스 수 저장 변수
	int							m_nNumIndex_X;		// X 기즈모 버텍스 수 저장 변수
	int							m_nNumIndex_Y;		// Y 기즈모 버텍스 수 저장 변수
	int							m_nNumIndex_Z;		// Z 기즈모 버텍스 수 저장 변수


	
	double						m_fMax;
	double						m_fMin;

};

