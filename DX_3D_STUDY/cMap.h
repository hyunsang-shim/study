#pragma once

class cMap
{
public:
	cMap();
	~cMap();

private:
	vector<ST_PNT_SubMesh>	subMesh;
	map<string, MATERIAL>	mtlLibrary;
	map<string, string>		textures;

	string					objFileName;	
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matTrans;
	D3DXMATRIXA16			m_matRotX;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matScale;

	LPDIRECT3DTEXTURE9		m_pTexture;


	D3DXVECTOR3				m_vBoxDirection;
	D3DXVECTOR3				m_vBoxPosition;		// �ַ� ���ο��� ���޹޴´�.
	double					m_fBoxScale;			// �ַ� ���ο��� ���޹޴´�.
	double					m_fBoxRotX;			// �ַ� ���ο��� ���޹޴´�.
	double					m_fBoxRotY;			// �ַ� ���ο��� ���޹޴´�.

public:
	void					Setup();
	void					Update();
	void					Render();
	void					SetBoxPosition(D3DXVECTOR3 box_pos);
	void					SetBoxScale(double scale);
	void					SetBoxRotationY(double rotY);

};