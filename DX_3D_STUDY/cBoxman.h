#pragma once
class cBoxman
{
public:
	cBoxman();
	~cBoxman();
		
	void Setup();
	void Update();
	void Render();
		
	void SetRootPosition(D3DXVECTOR3 Position);
	void SetRootDirection(D3DXVECTOR3 direction);
	void SetRootRotationY(double valueY);

private:
	D3DXVECTOR3				m_vecRootPosition;
	D3DXVECTOR3				m_vRootDirection;
	vector<D3DXVECTOR3>		m_vecHEAD;
	vector<D3DXVECTOR3>		m_vecARM;
	vector<D3DXVECTOR3>		m_vecLEG;
	vector<D3DXVECTOR3>		m_vecBODY;
	vector<int>				vecVerTex_Box_Index;
	vector<ST_PC_VERTEX>	m_vecPC_HEAD;
	vector<ST_PC_VERTEX>	m_vecPC_ARM;
	vector<ST_PC_VERTEX>	m_vecPC_LEG;
	vector<ST_PC_VERTEX>	m_vecPC_BODY;

	double					m_fRootRotationY;
	D3DXMATRIXA16			m_matBodySRT;
	D3DXMATRIXA16			m_matWorld;

};

