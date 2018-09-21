#pragma once
class cBoxman
{
public:
	cBoxman();
	~cBoxman();
		
	void Setup();
	void Update();
	void Render();
		
	void SetRootScale(double scale); 
	void SetRootRotationY(double valueY);
	void SetRootPosition(D3DXVECTOR3 Position);
	void SetRootDirection(D3DXVECTOR3 direction);
	void SetTextureUV_HEAD();
	void SetTextureUV_BODY();
	void SetTextureUV_ARM();
	void SetTextureUV_LEG();
	

private:
	D3DXVECTOR3				m_vRootScale;
	double					m_fRootRotationY;
	D3DXVECTOR3				m_vecRootPosition;
	D3DXVECTOR3				m_vRootDirection;

	// 루트 매트릭스
	D3DXMATRIXA16			m_matRootS;
	D3DXMATRIXA16			m_matRootR;
	D3DXMATRIXA16			m_matRootT;


	// 각 부위별 정점 저장용
	vector<D3DXVECTOR3>		m_vecHEAD;
	vector<D3DXVECTOR3>		m_vecARM;
	vector<D3DXVECTOR3>		m_vecLEG;
	vector<D3DXVECTOR3>		m_vecBODY;

	// 공용 박스 그리기용 정점 순서 배열
	vector<int>				vecVerTex_Box_Index;
	
	// 각 부위별 정점+텍스쳐UV좌표 저장용
	vector<ST_PT_VERTEX>	m_vecPT_HEAD;
	vector<ST_PT_VERTEX>	m_vecPT_ARM;
	vector<ST_PT_VERTEX>	m_vecPT_LEG;
	vector<ST_PT_VERTEX>	m_vecPT_BODY;
	
	// 각 부위별 텍스쳐 좌표 저장용 (임시)
	vector<D3DXVECTOR2>		m_vTexture_HEAD;
	vector<D3DXVECTOR2>		m_vTexture_ARM;
	vector<D3DXVECTOR2>		m_vTexture_LEG;
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

