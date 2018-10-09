#include "stdafx.h"

class cCamera;
cCubePC::cCubePC()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 10)
	, m_fBoxScale(0.1f)
	, m_fBoxRotY(0.1f)
	, m_fBoxRotX(-D3DX_PI / 2)
	, m_pTexture(NULL)
{	 
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
	SAFE_DELETE(m_pTexture);
}

void cCubePC::Setup()
{
	ST_PC_VERTEX	v;
	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));

	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(2);
	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(2);	vecVerTex_Box_Index.push_back(3);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(5);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(7);	vecVerTex_Box_Index.push_back(6);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(5);	vecVerTex_Box_Index.push_back(1);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(0);
	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(2);	vecVerTex_Box_Index.push_back(6);
	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(7);
	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(5);	vecVerTex_Box_Index.push_back(6);
	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(2);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(3);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(7);

	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = vecVerTex_Box[vecVerTex_Box_Index[i]];
		if (i % 6 == 0)
			v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);

		m_vecVertex.push_back(v);
	}

}

void cCubePC::Update()
{
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixScaling(&m_matScale, m_fBoxScale, m_fBoxScale, m_fBoxScale);
	D3DXMatrixRotationX(&m_matRotX, m_fBoxRotX);
	D3DXMatrixRotationY(&m_matRotY, m_fBoxRotY);	
	D3DXMatrixTranslation(&m_matTrans, m_vBoxPosition.x, m_vBoxPosition.y, m_vBoxPosition.z);
	m_matWorld = m_matScale * m_matRotX * m_matRotY * m_matTrans;
}

void cCubePC::Render()
{

	g_pD3DDevice->SetTexture(0, m_pTexture);	// 텍스쳐 사용 선언
	g_pD3DDevice->SetMaterial(&m_material);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (int i = 0; i < m_vecVertex.size(); i++)
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));


	g_pD3DDevice->SetTexture(0, NULL);	// 텍스쳐 사용 하지 않음 선언

}

void cCubePC::SetBoxPosition(D3DXVECTOR3 boxPos)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	 m_vBoxPosition = boxPos;
}

void cCubePC::SetBoxScale(double scale)
{
	m_fBoxScale = scale;
}

void cCubePC::SetBoxRotationY(double rotation)
{
	m_fBoxRotY = rotation;
}

vector<D3DXVECTOR3> cCubePC::GetOriginVertexList()
{
	return vecVerTex_Box;
}
