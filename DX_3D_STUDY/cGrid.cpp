#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
	:m_pVB(NULL)
	, m_nNumLines(0)
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{

	int nNumHalfTile = 10;
	double fInterval = 1.0f;
	m_fMax = nNumHalfTile * fInterval;
	m_fMin = -nNumHalfTile * fInterval;
	vector<ST_PC_VERTEX>		vecGridVertex;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		
		ST_PC_VERTEX				v;

		if (i % 5 == 0)
			v.color = D3DCOLOR_XRGB(200, 200, 200);
		else
			v.color = D3DCOLOR_XRGB(120, 120, 120);

		v.p = D3DXVECTOR3(m_fMin, 0, i * fInterval);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(m_fMax, 0, i * fInterval);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(m_fMin, 0, -i * fInterval);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(m_fMax, 0, -i * fInterval);			vecGridVertex.push_back(v);


		v.p = D3DXVECTOR3(i * fInterval, 0, m_fMin);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, m_fMax);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, m_fMin);			vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, m_fMax);			vecGridVertex.push_back(v);

		
	}

	// 가운데 선은 비어있게 되니까 채워준다.
	// z축은 빨간색
	ST_PC_VERTEX	v;
	v.color = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 0, m_fMin*5);
	vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, m_fMax*5);
	vecGridVertex.push_back(v);

	// X축은 파란색
	v.color = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(m_fMin*5, 0, 0);
	vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(m_fMax*5, 0, 0);
	vecGridVertex.push_back(v);


	// y축은 녹색
	v.color = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, m_fMin*5, 0);
	vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, m_fMax*5, 0);
	vecGridVertex.push_back(v);
		{
			m_nNumLines = vecGridVertex.size() / 2;
			g_pD3DDevice->CreateVertexBuffer(
				vecGridVertex.size() * sizeof(ST_PC_VERTEX),
				0,
				ST_PC_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB,
				NULL);
			ST_PC_VERTEX* pV = NULL;
			// 메모리 카피 시작
			m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
			// 메모리 카피
			memcpy(pV, &vecGridVertex[0], vecGridVertex.size() * sizeof(ST_PC_VERTEX));
			// 메모리 카피 종료
			m_pVB->Unlock();
		}

	// Indicator for Z-Axis
	// m_vecIndVertexZ
	{
		vector<ST_PC_VERTEX>		vecIndVertexZ;
		
		ST_PC_VERTEX	IndZ;
		IndZ.color = D3DCOLOR_XRGB(255, 0, 0);
		IndZ.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexZ.push_back(IndZ);
		{
			m_nNumVertices_Z = vecIndVertexZ.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(
				vecIndVertexZ.size() * sizeof(ST_PC_VERTEX),
				0,
				ST_PC_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Gizmo_Z,
				NULL);
			ST_PC_VERTEX* pV_IndZ = NULL;
			// 메모리 카피 시작
			m_pVB_Gizmo_Z->Lock(0, 0, (LPVOID*)&pV_IndZ, 0);
			// 메모리 카피
			memcpy(pV_IndZ, &vecIndVertexZ[0], vecIndVertexZ.size() * sizeof(ST_PC_VERTEX));
			// 메모리 카피 종료
			m_pVB_Gizmo_Z->Unlock();
		}
	}

	//// Indicator for X-Axis
	////m_vecIndVertexX
	{
		vector<ST_PC_VERTEX>		vecIndVertexX;
		ST_PC_VERTEX				IndX;
		IndX.color = D3DCOLOR_XRGB(0, 0, 255);
		IndX.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexX.push_back(IndX);
		{
			m_nNumVertices_X = vecIndVertexX.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(
				vecIndVertexX.size() * sizeof(ST_PC_VERTEX),
				0,
				ST_PC_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Gizmo_X,
				NULL);
			ST_PC_VERTEX* pV_IndX = NULL;
			// 메모리 카피 시작
			m_pVB_Gizmo_X->Lock(0, 0, (LPVOID*)&pV_IndX, 0);
			// 메모리 카피
			memcpy(pV_IndX, &vecIndVertexX[0], vecIndVertexX.size() * sizeof(ST_PC_VERTEX));
			// 메모리 카피 종료
			m_pVB_Gizmo_X->Unlock();
		}
	}

	// Indicator for Y-Axis
	//m_vecIndVertexY
	{
		vector<ST_PC_VERTEX>		vecIndVertexY;
		ST_PC_VERTEX	IndY;
		IndY.color = D3DCOLOR_XRGB(0, 255, 0);
		IndY.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0, 0, 0);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		vecIndVertexY.push_back(IndY);
	
		{
			m_nNumVertices_Y = vecIndVertexY.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(
				vecGridVertex.size() * sizeof(ST_PC_VERTEX),
				0,
				ST_PC_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Gizmo_Y,
				NULL);
			ST_PC_VERTEX* pV_IndY = NULL;
			// 메모리 카피 시작
			m_pVB_Gizmo_Y->Lock(0, 0, (LPVOID*)&pV_IndY, 0);
			// 메모리 카피
			memcpy(pV_IndY, &vecIndVertexY[0], vecIndVertexY.size() * sizeof(ST_PC_VERTEX));
			// 메모리 카피 종료
			m_pVB_Gizmo_Y->Unlock();
		}

}
	
	

}

void cGrid::DrawGrid()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecGridVertex.size() / 2, &m_vecGridVertex[0], sizeof(ST_PC_VERTEX));
	{
		// 버텍스 버퍼를 이용한 Draw 구문으로 대체
		g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLines);
	}
	g_pD3DDevice->SetTexture(0, NULL);
}

void cGrid::DrawIndicator()
{
	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIXA16		matRot;
	D3DXMATRIXA16		matScale;
	D3DXMATRIXA16		matSR;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matRot);


	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//// Draw Z-Axis Indicator
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	m_matWorld = matScale * m_matWorld; 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);	
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexZ.size() / 3, &m_vecIndVertexZ[0], sizeof(ST_PC_VERTEX));
	{
		g_pD3DDevice->SetStreamSource(0, m_pVB_Gizmo_Z, 0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumVertices_Z);
	}
	//// Draw X-Axis Indicator
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	D3DXMatrixRotationY(&matRot, D3DX_PI / 2);
	matSR = matScale * matRot;
	m_matWorld = matSR * m_matWorld;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexX.size() / 3, &m_vecIndVertexX[0], sizeof(ST_PC_VERTEX));
	{
		g_pD3DDevice->SetStreamSource(0, m_pVB_Gizmo_X, 0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumVertices_X);
	}

	//// Draw Y-Axis Indicator
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	D3DXMatrixRotationX(&matRot, -D3DX_PI / 2);
	matSR = matScale * matRot;
	m_matWorld = matSR * m_matWorld;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);	
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexY.size() / 3, &m_vecIndVertexY[0], sizeof(ST_PC_VERTEX));
	{
		g_pD3DDevice->SetStreamSource(0, m_pVB_Gizmo_Y, 0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumVertices_Y);
	}

}

void cGrid::Render()
{
	DrawGrid();
	DrawIndicator();
}

RECT cGrid::GetGridMinMax()
{
	RECT ret;
	ret.right = m_fMax;
	ret.left = m_fMin;
	ret.top = m_fMin;
	ret.bottom = m_fMax;
	return ret;
}
