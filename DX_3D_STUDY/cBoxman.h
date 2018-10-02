#pragma once

typedef struct boxman_pt {
	vector<ST_PT_VERTEX>	HEAD;
	vector<ST_PT_VERTEX>	ARM_L;
	vector<ST_PT_VERTEX>	ARM_R;
	vector<ST_PT_VERTEX>	LEG_L;
	vector<ST_PT_VERTEX>	LEG_R;
	vector<ST_PT_VERTEX>	BODY;
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
	

private:
	D3DXVECTOR3				m_vRootScale;
	double					m_fRootRotationY;
	D3DXVECTOR3				m_vecRootPosition;
	D3DXVECTOR3				m_vRootDirection;
	D3DMATERIAL9			m_matWhite;

	bool					m_isMoving;
	bool					m_isRunning;
	bool					m_isJumping;
	bool					m_isJumping_Top;
	float					m_vSwingFactor;
	
	float					m_fRotArmL;
	float					m_fRotArmR;
	float					m_fRotLegL;
	float					m_fRotLegR;

	// ��Ʈ ��Ʈ����
	D3DXMATRIXA16			m_matRootS;
	D3DXMATRIXA16			m_matRootR;
	D3DXMATRIXA16			m_matRootT;


	// �� ������ ���� �����
	vector<D3DXVECTOR3>		m_vecHEAD;
	vector<D3DXVECTOR3>		m_vecARM_L;
	vector<D3DXVECTOR3>		m_vecARM_R;
	vector<D3DXVECTOR3>		m_vecLEG_L;
	vector<D3DXVECTOR3>		m_vecLEG_R;
	vector<D3DXVECTOR3>		m_vecBODY;

	// ���� �ڽ� �׸���� ���� ���� �迭
	vector<int>				vecVerTex_Box_Index;
	
	// �� ������ ����+�ؽ���UV��ǥ �����
	BOXMAN_PT				strBoxman;
	
	// �� ������ �ؽ��� ��ǥ ����� (�ӽ�)
	vector<D3DXVECTOR2>		m_vTexture_HEAD;
	vector<D3DXVECTOR2>		m_vTexture_ARM_L;
	vector<D3DXVECTOR2>		m_vTexture_ARM_R;
	vector<D3DXVECTOR2>		m_vTexture_LEG_L;
	vector<D3DXVECTOR2>		m_vTexture_LEG_R;
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

