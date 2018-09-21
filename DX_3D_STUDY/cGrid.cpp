#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
	// 그리드 표시용
	int nNumHalfTile = 10;
	double fInterval = 1.0f;
	double fMax = nNumHalfTile * fInterval;
	double fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		ST_PC_VERTEX	v;

		if (i % 5 == 0)
			v.color = D3DCOLOR_XRGB(200, 200, 200);
		else
			v.color = D3DCOLOR_XRGB(120, 120, 120);

		v.p = D3DXVECTOR3(fMin, 0, i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval);			m_vecGridVertex.push_back(v);


		v.p = D3DXVECTOR3(i * fInterval, 0, fMin);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax);			m_vecGridVertex.push_back(v);

	}

	// 가운데 선은 비어있게 되니까 채워준다.
	// z축은 빨간색
	ST_PC_VERTEX	v;
	v.color = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 0, fMin*5);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, fMax*5);
	m_vecGridVertex.push_back(v);

	// X축은 파란색
	v.color = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(fMin*5, 0, 0);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(fMax*5, 0, 0);
	m_vecGridVertex.push_back(v);


	// y축은 녹색
	v.color = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin*5, 0);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, fMax*5, 0);
	m_vecGridVertex.push_back(v);


	// Indicator for Z-Axis
	// m_vecIndVertexZ
	{
		ST_PC_VERTEX	IndZ;
		IndZ.color = D3DCOLOR_XRGB(255, 0, 0);
		IndZ.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);

		IndZ.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);

		IndZ.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);

		IndZ.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);

		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);

		IndZ.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
		IndZ.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexZ.push_back(IndZ);
	}

	// Indicator for X-Axis
	//m_vecIndVertexX
	{
		ST_PC_VERTEX	IndX;
		IndX.color = D3DCOLOR_XRGB(0, 0, 255);
		IndX.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);

		IndX.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);

		IndX.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);

		IndX.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);

		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);

		IndX.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
		IndX.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexX.push_back(IndX);
	}

	// Indicator for Y-Axis
	//m_vecIndVertexY
	{
		ST_PC_VERTEX	IndY;
		IndY.color = D3DCOLOR_XRGB(0, 255, 0);
		IndY.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);

		IndY.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);

		IndY.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);

		IndY.p = D3DXVECTOR3(0, 0, 0);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);

		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);

		IndY.p = D3DXVECTOR3(0.2, 0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(-0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
		IndY.p = D3DXVECTOR3(0.2, -0.2, 1.0f);
		m_vecIndVertexY.push_back(IndY);
	}
}

void cGrid::DrawGrid()
{
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);

	D3DXMATRIXA16 m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecGridVertex.size() / 2, &m_vecGridVertex[0], sizeof(ST_PC_VERTEX));
}

void cGrid::DrawIndicator()
{
	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIXA16		matRot;
	D3DXMATRIXA16		matScale;
	D3DXMATRIXA16		matSR;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matRot);


	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);


	//// Draw Z-Axis Indicator
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	m_matWorld = matScale * m_matWorld; 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexZ.size() / 3, &m_vecIndVertexZ[0], sizeof(ST_PC_VERTEX));

	//// Draw X-Axis Indicator
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	D3DXMatrixRotationY(&matRot, D3DX_PI / 2);
	matSR = matScale * matRot;
	m_matWorld = matSR * m_matWorld;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexX.size() / 3, &m_vecIndVertexX[0], sizeof(ST_PC_VERTEX));


	//// Draw Y-Axis Indicator
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matScale, 0.5, 0.5, 1.5);
	D3DXMatrixRotationX(&matRot, -D3DX_PI / 2);
	matSR = matScale * matRot;
	m_matWorld = matSR * m_matWorld;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertexY.size() / 3, &m_vecIndVertexY[0], sizeof(ST_PC_VERTEX));


}

void cGrid::Render()
{
	DrawGrid();
	DrawIndicator();
}
