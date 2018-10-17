#pragma once

class cMap
{
public:
	cMap();
	~cMap();

private:
	vector<SubMesh>					subMesh;

	string							objFileName;
	D3DXMATRIXA16					m_matWorld;
	D3DXMATRIXA16					m_matTrans;
	D3DXMATRIXA16					m_matRotX;
	D3DXMATRIXA16					m_matRotY;
	D3DXMATRIXA16					m_matScale;

	D3DXVECTOR3						m_vBoxDirection;
	D3DXVECTOR3						m_vBoxPosition;		
	double							m_fBoxScale;		
	double							m_fBoxRotX;			
	double							m_fBoxRotY;			


	vector<LPDIRECT3DVERTEXBUFFER9>	m_vpVB_SubMesh;

public:
	void							Setup();
	void							Update();
	void							Render();
	void							SetBoxPosition(D3DXVECTOR3 box_pos);
	void							SetBoxScale(double scale);
	void							SetBoxRotationY(double rotY);

};