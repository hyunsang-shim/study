#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 0)
	, m_fBoxScale(0.1f)
	, m_fBoxRotY(D3DX_PI / 2)
	, m_fBoxRotX(-D3DX_PI / 2)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cMap::~cMap()
{
}

void cMap::Setup()
{	
	subMesh = ObjLoader::ParseObj("./obj/map.obj");

	
	// 버텍스 버퍼 이용
	for (int i = 0; i < subMesh.size(); i++)
	{
		LPDIRECT3DVERTEXBUFFER9 tmpLPVB;
		g_pD3DDevice->CreateVertexBuffer(subMesh[i].vPNT_VERTEX.size() * sizeof(ST_PNT_VERTEX), 0, ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &tmpLPVB, NULL);
		m_vpVB_SubMesh.push_back(tmpLPVB);
		
		ST_PNT_VERTEX* pV_tmpPNT = NULL;	
		m_vpVB_SubMesh[i]->Lock(0, 0, (LPVOID*)&pV_tmpPNT, 0);

		memcpy(pV_tmpPNT, &subMesh[i].vPNT_VERTEX[0], subMesh[i].vPNT_VERTEX.size() * sizeof(ST_PNT_VERTEX));

		m_vpVB_SubMesh[i]->Unlock();
	}

}

void cMap::Update()
{
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixScaling(&m_matScale, m_fBoxScale * 0.2f, m_fBoxScale * 0.2f, m_fBoxScale * 0.2f);
	D3DXMatrixRotationX(&m_matRotX, m_fBoxRotX);
	D3DXMatrixRotationY(&m_matRotY, m_fBoxRotY);
	D3DXMatrixTranslation(&m_matTrans, m_vBoxPosition.x, m_vBoxPosition.y, m_vBoxPosition.z);
	m_matWorld = m_matScale * m_matRotX * m_matRotY * m_matTrans;
}

void cMap::Render()
{
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	// 일반 vector 이용
	//for (int i = 0; i < subMesh.size(); i++)
	//{		
	//		g_pD3DDevice->SetMaterial(&subMesh[i].mat9Material);
	//		g_pD3DDevice->SetTexture(0, subMesh[i].tx9Texture);
	//		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, subMesh[i].vPNT_VERTEX.size() / 3, &subMesh[i].vPNT_VERTEX[0], sizeof(ST_PNT_VERTEX));

	//	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, subMesh[i].vecPNT.size() / 3,  &subMesh[i].vecPNT[0], sizeof(ST_PNT_VERTEX));
	//}

	// 버텍스 버퍼 이용 (텍스쳐, 매터리얼은 기존 버퍼 이용)
	for (int i = 0; i < m_vpVB_SubMesh.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&subMesh[i].mat9Material);
		g_pD3DDevice->SetTexture(0, subMesh[i].tx9Texture);
		g_pD3DDevice->SetStreamSource(0, m_vpVB_SubMesh[i], 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, subMesh[i].nCntTriangles);
	}

	g_pD3DDevice->SetTexture(0, NULL);
	
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
