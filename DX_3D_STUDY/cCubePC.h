#pragma once


class cCubePC
{
public:
	cCubePC();
	~cCubePC();

private:
	vector<ST_PNT_VERTEX>	m_vecVertex;
	vector<D3DXVECTOR3>		vecVerTex_Box;
	vector<D3DXVECTOR2>		vecVerTex_Texture;
	vector<int>				vecVerTex_Box_Index;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matTrans;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matScale;

	LPDIRECT3DTEXTURE9		m_pTexture;


	D3DXVECTOR3				m_vBoxDirection;
	D3DXVECTOR3				m_vBoxPosition;		// 주로 메인에게 전달한다.
	double					m_fBoxScale;			// 메인에게 전달한다.
	double					m_fBoxRotY;			// 주로 메인에게 전달한다.

public:
	void					Setup();
	void					Update();
	void					Render();
	void					SetBoxPosition(D3DXVECTOR3 box_pos);
	void					SetBoxScale(double scale);
	void					SetBoxRotationY(double rotY);
	D3DMATERIAL9			m_material;
	vector<D3DXVECTOR3>		GetOriginVertexList();
	
};