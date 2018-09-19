#pragma once


class cCubePC
{
public:
	cCubePC();
	~cCubePC();

private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<D3DXVECTOR3>		vecVerTex_Box;
	vector<int>				vecVerTex_Box_Index;
	D3DXMATRIXA16			m_matWorld;

	D3DXVECTOR3				m_vBoxDirection;
	D3DXVECTOR3				m_vPosition;
	double					m_fScale;
	double					m_fBoxRotY;

public:
	void					Setup();
	void					Update();
	void					Render();
	D3DXVECTOR3&			GetPosition();
	double					GetScale();
	double					GetRotationY();
	
};

