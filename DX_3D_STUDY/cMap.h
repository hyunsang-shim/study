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

	// 버텍스 버퍼
	vector<LPDIRECT3DVERTEXBUFFER9>	m_vpVB_SubMesh;

	// 인덱스 버퍼
	vector<LPDIRECT3DVERTEXBUFFER9 >	m_vpVBforIB_SubMesh;
	vector<LPDIRECT3DINDEXBUFFER9 >		m_vpIB_SubMesh;

public:
	void							Setup();
	void							Update();
	void							Render();
	void							SetBoxPosition(D3DXVECTOR3 box_pos);
	void							SetBoxScale(double scale);
	void							SetBoxRotationY(double rotY);

};