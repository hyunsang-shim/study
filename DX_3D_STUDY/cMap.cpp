#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 10)
	, m_fBoxScale(0.1f)
	, m_fBoxRotY(0.1f)
	, m_fBoxRotX(-D3DX_PI / 2)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cMap::~cMap()
{
}

void cMap::Setup()
{	
	subMesh = ObjLoader::ParseObj();
}

void cMap::Update()
{
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixScaling(&m_matScale, m_fBoxScale * 0.01f, m_fBoxScale * 0.02f, m_fBoxScale * 0.02f);
	D3DXMatrixRotationX(&m_matRotX, -D3DX_PI/2);
	D3DXMatrixRotationY(&m_matRotY, m_fBoxRotY);
	D3DXMatrixTranslation(&m_matTrans, m_vBoxPosition.x, m_vBoxPosition.y, m_vBoxPosition.z);
	m_matWorld = m_matScale * m_matRotX * m_matRotY * m_matTrans;
}

void cMap::Render()
{
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXCreateTextureFromFileA(g_pD3DDevice, "./obj/box.jpg", &m_pTexture);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	D3DXMATRIXA16 m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (int i = 0; i < 2; i++)
	{
		//g_pD3DDevice->SetMaterial(&find(mtlLibrary[i].materials, mtlLibrary[i].materials, subMesh[i].MaterialName));
		//g_pD3DDevice->SetTexture(0, &find(textures.begin(), textures.end(), (find(mtlLibrary[i].strMtlName, mtlLibrary[i].strMtlName, subMesh[i].MaterialName))));
		//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, subMesh[i].vecPNT.size() / 3,  &subMesh[i].vecPNT[0], sizeof(ST_PNT_VERTEX));
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
