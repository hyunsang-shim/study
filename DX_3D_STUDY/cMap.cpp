#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 10)
	, m_fBoxScale(0.1f)
	, m_fBoxRotY(0.1f)
	, m_fBoxRotX(-D3DX_PI / 2)
	, m_pTexture(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cMap::~cMap()
{
	SAFE_DELETE(m_pTexture);
}

void cMap::Setup()
{
	ST_PNT_VERTEX	v;
	ObjLoader::ParseObj("obj/Map.obj");

}

void cMap::Update()
{
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixScaling(&m_matScale, m_fBoxScale, m_fBoxScale, m_fBoxScale);
	D3DXMatrixRotationX(&m_matRotX, m_fBoxRotX);
	D3DXMatrixRotationY(&m_matRotY, m_fBoxRotY);
	D3DXMatrixTranslation(&m_matTrans, m_vBoxPosition.x, m_vBoxPosition.y, m_vBoxPosition.z);
	m_matWorld = m_matScale * m_matRotX * m_matRotY * m_matTrans;
}

void cMap::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (int i = 0; i < m_vecVertex.size(); i++)
	{

		g_pD3DDevice->SetMaterial(&m_material);
		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex[i].vertexPNT.size() / 3, &m_vecVertex[i].vertexPNT[0], sizeof(ST_PNT_VERTEX));
	}
	
	g_pD3DDevice->SetTexture(0, NULL);	// 텍스쳐 사용 하지 않음 선언

}

void cMap::SetBoxPosition(D3DXVECTOR3 boxPos)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	m_vBoxPosition = boxPos;
}

void cMap::SetBoxScale(double scale)
{
	m_fBoxScale = scale;
}

void cMap::SetBoxRotationY(double rotation)
{
	m_fBoxRotY = rotation;
}

vector<D3DXVECTOR3> cMap::GetOriginVertexList()
{
	return vecVerTex_Box;
}
