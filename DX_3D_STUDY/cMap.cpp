#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 0)
	, m_fBoxScale(0.1f)
	, m_fBoxRotY(D3DX_PI / 2)
	, m_fBoxRotX(-D3DX_PI / 2)
	, m_vpVBforIB_SubMesh(NULL)
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
	//for (int i = 0; i < subMesh.size(); i++)
	//{
	//	LPDIRECT3DVERTEXBUFFER9 tmpLPVB;
	//	g_pD3DDevice->CreateVertexBuffer(subMesh[i].vPNT_VERTEX.size() * sizeof(ST_PNT_VERTEX), 0, ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &tmpLPVB, NULL);
	//	m_vpVB_SubMesh.push_back(tmpLPVB);
	//	
	//	ST_PNT_VERTEX* pV_tmpPNT = NULL;	
	//	m_vpVB_SubMesh[i]->Lock(0, 0, (LPVOID*)&pV_tmpPNT, 0);

	//	{
	//		//for 문으로 변경
	//		for (int i = 0; i < subMesh[i].vPNT_VERTEX.size(); i++)
	//		{
	//			pV_tmpPNT[i] = subMesh[i].vPNT_VERTEX[i];
	//		}
	//		
	//	}
	//	
	//	m_vpVB_SubMesh[i]->Unlock();
	//}

	// 인덱스 버퍼용 버텍스 버퍼
	{
		for (int i = 0; i < subMesh.size(); i++)
		{
			LPDIRECT3DVERTEXBUFFER9 tmpLPVB;
			g_pD3DDevice->CreateVertexBuffer(subMesh[i].vPNT_VERTEX.size() * sizeof(ST_PNT_VERTEX), 0, ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &tmpLPVB, NULL);
			m_vpVBforIB_SubMesh.push_back(tmpLPVB); 
			
			ST_PNT_VERTEX* pV_tmpPNT = NULL;
			m_vpVBforIB_SubMesh[i]->Lock(0, 0, (LPVOID*)&pV_tmpPNT, 0);
			for (int j = 0; j < subMesh[i].vecVertex.size(); j++)
			{
				pV_tmpPNT[j].p = subMesh[i].vecVertex[j];
				pV_tmpPNT[j].normal = subMesh[i].vecVertex[ subMesh[i].vec_nFaceIndex[j] ];
				pV_tmpPNT[j].texture = subMesh[i].vecUV[subMesh[i].vec_nUV_Index[j] ];
			}

			m_nVB_SubMesh.push_back(subMesh[i].vecVertex.size());
			m_vpVBforIB_SubMesh[i]->Unlock();
		}

	}
	//// 인덱스 버퍼
	{
		m_vpIB_SubMesh.resize(subMesh.size());

		for (int i = 0; i < subMesh.size(); i++)
		{
			
			// 인덱스 버퍼 세팅
			WORD *piB;
			g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * subMesh[i].vec_nFaceIndex.size(), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_vpIB_SubMesh[i], NULL);
			m_vpIB_SubMesh[i]->Lock(0, 0, (void**)&piB, 0);

			for (int j = 0; j < subMesh[i].vec_nFaceIndex.size(); j++)
			{
				piB[j] = subMesh[i].vec_nFaceIndex[j];				
			}	
			m_nIB_SubMesh.push_back(subMesh[i].vec_nFaceIndex.size());
			m_vpIB_SubMesh[i]->Unlock();
		}
		
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
	for (int i = 0; i < subMesh.size(); i++)
	{		
		// g_pD3DDevice->SetMaterial(&subMesh[i].mat9Material);
		// g_pD3DDevice->SetTexture(0, subMesh[i].tx9Texture);
		// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, subMesh[i].vPNT_VERTEX.size() / 3, &subMesh[i].vPNT_VERTEX[0], sizeof(ST_PNT_VERTEX));
	}

	// 버텍스 버퍼 이용 (텍스쳐, 매터리얼은 기존 버퍼 이용)
	//for (int i = 0; i < m_vpVB_SubMesh.size(); i++)
	{
		// g_pD3DDevice->SetMaterial(&subMesh[i].mat9Material);
		// g_pD3DDevice->SetTexture(0, subMesh[i].tx9Texture);
		// g_pD3DDevice->SetStreamSource(0, m_vpVB_SubMesh[i], 0, sizeof(ST_PNT_VERTEX));
		// g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, subMesh[i].nCntTriangles);
	}

	// 인덱스 버퍼 이용
	{	
		for (int i = 0; i < m_nVB_SubMesh.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&subMesh[i].mat9Material);
			g_pD3DDevice->SetTexture(0, subMesh[i].tx9Texture);
			g_pD3DDevice->SetIndices(m_vpIB_SubMesh[i]);
			g_pD3DDevice->SetStreamSource(0, m_vpVBforIB_SubMesh[i], 0, sizeof(ST_PNT_VERTEX));
			g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVB_SubMesh[i], 0, subMesh[i].vec_nFaceIndex.size());
		}
		
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
