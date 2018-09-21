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

	// ��Ʈ ��Ʈ����
	D3DXMATRIXA16			m_matRootS;
	D3DXMATRIXA16			m_matRootR;
	D3DXMATRIXA16			m_matRootT;


	// �� ������ ���� �����
	vector<D3DXVECTOR3>		m_vecHEAD;
	vector<D3DXVECTOR3>		m_vecARM;
	vector<D3DXVECTOR3>		m_vecLEG;
	vector<D3DXVECTOR3>		m_vecBODY;

	// ���� �ڽ� �׸���� ���� ���� �迭
	vector<int>				vecVerTex_Box_Index;
	
	// �� ������ ����+�ؽ���UV��ǥ �����
	vector<ST_PT_VERTEX>	m_vecPT_HEAD;
	vector<ST_PT_VERTEX>	m_vecPT_ARM;
	vector<ST_PT_VERTEX>	m_vecPT_LEG;
	vector<ST_PT_VERTEX>	m_vecPT_BODY;
	
	// �� ������ �ؽ��� ��ǥ ����� (�ӽ�)
	vector<D3DXVECTOR2>		m_vTexture_HEAD;
	vector<D3DXVECTOR2>		m_vTexture_ARM;
	vector<D3DXVECTOR2>		m_vTexture_LEG;
	vector<D3DXVECTOR2>		m_vTexture_BODY;
	
	// �� ������ ��Ʈ���� ���� �� ����
	// �Ӹ�
	D3DXMATRIXA16			m_matWorld_Head;
	D3DXMATRIXA16			m_matHeadS;
	D3DXMATRIXA16			m_matHeadR;
	D3DXMATRIXA16			m_matHeadT;

	// ����
	D3DXMATRIXA16			m_matWorld_Body;
	D3DXMATRIXA16			m_matBodyS;
	D3DXMATRIXA16			m_matBodyR;
	D3DXMATRIXA16			m_matBodyT;

	// ����
	D3DXMATRIXA16			m_matWorld_ArmL;
	D3DXMATRIXA16			m_matArmLS;
	D3DXMATRIXA16			m_matArmLR;
	D3DXMATRIXA16			m_matArmLT;

	// �޴ٸ�
	D3DXMATRIXA16			m_matWorld_LegL;
	D3DXMATRIXA16			m_matLegLS;
	D3DXMATRIXA16			m_matLegLR;
	D3DXMATRIXA16			m_matLegLT;

	// ������
	D3DXMATRIXA16			m_matWorld_ArmR;
	D3DXMATRIXA16			m_matArmRS;
	D3DXMATRIXA16			m_matArmRR;
	D3DXMATRIXA16			m_matArmRT;

	// �����ٸ�
	D3DXMATRIXA16			m_matWorld_LegR;
	D3DXMATRIXA16			m_matLegRS;
	D3DXMATRIXA16			m_matLegRR;
	D3DXMATRIXA16			m_matLegRT;

	LPDIRECT3DTEXTURE9		m_pTexture;
};

