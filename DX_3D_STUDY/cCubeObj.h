#pragma once
class cCubeObj
{
public:
	cCubeObj();
	~cCubeObj();


private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<D3DXVECTOR3>		vecVerTex_Box;
	vector<D3DXVECTOR2>		vecVerTex_Texture;
	vector<int>				vecVerTex_Box_Index;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matTrans;
	D3DXMATRIXA16			m_matRotX;
	D3DXMATRIXA16			m_matRotY;
	D3DXMATRIXA16			m_matScale;

};

