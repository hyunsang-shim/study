#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_pMesh(NULL)
{
}


cHeightMap::~cHeightMap()
{
}

void cHeightMap::Setup(string Filename)
{
	int filesize = 0;
	vector<int> heights = cRawLoader::RawLoad(Filename, filesize);
	int width = pow(filesize, 0.5);
	// 임시 조정
	const DWORD			NumSubset = 0;
	HRESULT				hr;
	hr = D3DXCreateMeshFVF(pow((width-1),2) * 2, pow(width, 2), D3DXMESH_VB_DYNAMIC | D3DXMESH_32BIT, ST_PC_VERTEX::FVF, g_pD3DDevice, &m_pMesh);
	ST_PC_VERTEX *v = NULL;
	m_pMesh->LockVertexBuffer(0, (void**)&v);

	int CntVertices = 0;
	// Set for P(vertex)

	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < width; col++)
		{			
			v[CntVertices].p = D3DXVECTOR3(
				row * width + col - width,
				heights[CntVertices] / 10.0f,
				row * width + col + width);

			CntVertices++;
		}
	}

	
	// Set Color
	for (int row = 0; row < width; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if ((row * width + col) % 6 == 0)
				v[CntVertices--].color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
			else
				v[CntVertices--].color = D3DCOLOR_XRGB(255,255,255);
		}
	}

	m_pMesh->UnlockVertexBuffer();



	WORD *i = NULL;
	m_pMesh->LockIndexBuffer(0, (void**)&i);
	int CntIdx = 0;
	
	for (int row = 1; row < width; row++)
	{
		for (int col = 1; col < width; col++)
		{
			i[CntIdx++] = row * width + col;
			i[CntIdx++] = (row - 1) * width + (col - 1);
			i[CntIdx++] = (row - 1) * width + col;
			i[CntIdx++] = row * width + col;
			i[CntIdx++] = row * width + col - 1;
			i[CntIdx++] = (row - 1) * width + (col - 1);
		}
	}


	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = NULL;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int a = 0; a < 4; a++)
		attributeBuffer[a] = 0;

	for (int b = 4; b < 8; b++)
		attributeBuffer[b] = 1;

	for (int c = 8; c < 12; c++)
		attributeBuffer[c] = 2;

	m_pMesh->UnlockAttributeBuffer();

	vector<DWORD> adjacencyBuffer(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0);


	m_DefaultMaterial.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_DefaultMaterial.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_DefaultMaterial.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	matWorld = matS * matR;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_DefaultMaterial);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pMesh->DrawSubset(0);
}
