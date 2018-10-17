#pragma once

typedef struct boxman_pt {
	vector<ST_PT_VERTEX>	HEAD;
	int						nCntHEADTriangles;
	vector<ST_PT_VERTEX>	ARM_L;
	int						nCntARM_LTriangles;
	vector<ST_PT_VERTEX>	ARM_R;
	int						nCntARM_RTriangles;
	vector<ST_PT_VERTEX>	LEG_L;
	int						nCntLEG_LTriangles;
	vector<ST_PT_VERTEX>	LEG_R;
	int						nCntLEG_RTriangles;
	vector<ST_PT_VERTEX>	BODY;
	int						nCntBODYTriangles;
}BOXMAN_PT;

typedef struct objfromfile {
	vector<ST_PNT_VERTEX>	ObjFromFile;
}OBJ_FROM_FILE;


class cBoxman
{
public:
	cBoxman();
	~cBoxman();
		
	void Setup(TCHAR* filename);
	void Update();
	void Render();
		
	void SetRootScale(double scale); 
	void SetRootRotationY(double valueY);
	void SetRootPosition(D3DXVECTOR3 Position);
	void SetRootDirection(D3DXVECTOR3 direction);
	void SetTextureUV_HEAD();
	void SetTextureUV_BODY();
	void SetTextureUV_ARM_L();
	void SetTextureUV_ARM_R();
	void SetTextureUV_LEG_L();
	void SetTextureUV_LEG_R();
	void SetMoveState(bool move, bool run);
	void SetjumpState(bool value1, bool value2);
	void SetCurPos(D3DXVECTOR3 newCurPos);
	D3DXVECTOR3 GetCurPos();
	void SetNextPos(D3DXVECTOR3 newNextPos);
	D3DXVECTOR3 GetNextPos();

	

private:
	D3DXVECTOR3				m_vRootScale;
	double					m_fRootRotationY;
	D3DXVECTOR3				m_vecRootPosition;
	D3DXVECTOR3				m_vRootDirection;
	D3DMATERIAL9			m_matWhite;
	D3DXVECTOR3				m_CurPos;
	D3DXVECTOR3				m_NextPos;
	vector<D3DXVECTOR3>		m_waypoints;


	bool					m_isMoving;
	bool					m_isRunning;
	bool					m_isJumping;
	bool					m_isJumping_Top;
	float					m_vSwingFactor;
	
	float					m_fRotArmL;
	float					m_fRotArmR;
	float					m_fRotLegL;
	float					m_fRotLegR;

	// 루트 매트릭스
	D3DXMATRIXA16			m_matRootS;
	D3DXMATRIXA16			m_matRootR;
	D3DXMATRIXA16			m_matRootT;


	// 각 부위별 정점 저장용
	vector<D3DXVECTOR3>		m_vecHEAD;
	vector<D3DXVECTOR3>		m_vecARM_L;
	vector<D3DXVECTOR3>		m_vecARM_R;
	vector<D3DXVECTOR3>		m_vecLEG_L;
	vector<D3DXVECTOR3>		m_vecLEG_R;
	vector<D3DXVECTOR3>		m_vecBODY;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_HEAD;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_ARM_L;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_ARM_R;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_LEG_L;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_LEG_R;
	LPDIRECT3DVERTEXBUFFER9		m_pVB_Boxman_BODY;


	// 공용 박스 그리기용 정점 순서 배열
	vector<int>				vecVerTex_Box_Index;
	
	// 각 부위별 정점+텍스쳐UV좌표 저장용
	BOXMAN_PT				strBoxman;
	
	// 각 부위별 텍스쳐 좌표 저장용 (임시)
	vector<D3DXVECTOR2>		m_vTexture_HEAD;
	vector<D3DXVECTOR2>		m_vTexture_ARM_L;
	vector<D3DXVECTOR2>		m_vTexture_ARM_R;
	vector<D3DXVECTOR2>		m_vTexture_LEG_L;
	vector<D3DXVECTOR2>		m_vTexture_LEG_R;
	vector<D3DXVECTOR2>		m_vTexture_BODY;
	
	// 각 부위별 매트릭스 세팅 및 계산용
	// 머리
	D3DXMATRIXA16			m_matWorld_Head;
	D3DXMATRIXA16			m_matHeadS;
	D3DXMATRIXA16			m_matHeadR;
	D3DXMATRIXA16			m_matHeadT;

	// 몸통
	D3DXMATRIXA16			m_matWorld_Body;
	D3DXMATRIXA16			m_matBodyS;
	D3DXMATRIXA16			m_matBodyR;
	D3DXMATRIXA16			m_matBodyT;

	// 왼팔
	D3DXMATRIXA16			m_matWorld_ArmL;
	D3DXMATRIXA16			m_matArmLS;
	D3DXMATRIXA16			m_matArmLR;
	D3DXMATRIXA16			m_matArmLT;

	// 왼다리
	D3DXMATRIXA16			m_matWorld_LegL;
	D3DXMATRIXA16			m_matLegLS;
	D3DXMATRIXA16			m_matLegLR;
	D3DXMATRIXA16			m_matLegLT;

	// 오른팔
	D3DXMATRIXA16			m_matWorld_ArmR;
	D3DXMATRIXA16			m_matArmRS;
	D3DXMATRIXA16			m_matArmRR;
	D3DXMATRIXA16			m_matArmRT;

	// 오른다리
	D3DXMATRIXA16			m_matWorld_LegR;
	D3DXMATRIXA16			m_matLegRS;
	D3DXMATRIXA16			m_matLegRR;
	D3DXMATRIXA16			m_matLegRT;

	LPDIRECT3DTEXTURE9		m_pTexture;
};

