#include "stdafx.h"


cHexagon::cHexagon()
{
}


cHexagon::~cHexagon()
{
}

void cHexagon::Setup()
{
	ST_PC_VERTEX point;
	float radius = 8.0f;
	point.color = D3DCOLOR_XRGB(200, 200, 0);	
	point.p = D3DXVECTOR3(8, 0.5f, 0);
	m_vecHexagonVertex.push_back(point);

	//m_vecHexagonVertex.push_back(point);
	for (float i = 1; i <= 12; i += 1.0f)
	{
		float tmp = D3DX_PI / 3.0f * i;
		point.p = D3DXVECTOR3(radius * cos(tmp), 0.5f, radius * -sin(tmp));
		m_vecHexagonVertex.push_back(point);
	}
	
	//for Debug
	/*
	for (int i = 0; i < m_vecHexagonVertex.size(); i++)
	printf("%d : %3f, %3f, %3f\n", i, m_vecHexagonVertex[i].p.x, m_vecHexagonVertex[i].p.y, m_vecHexagonVertex[i].p.z);
	*/
}

void cHexagon::Render()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecHexagonVertex.size()/2, &m_vecHexagonVertex[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);

}

vector<D3DXVECTOR3> cHexagon::GetPoints()
{
	vector<D3DXVECTOR3> vecRet;
	for (int i = 0; i < 6; i++)
	{
		m_vecHexagonVertex;
		vecRet.push_back(m_vecHexagonVertex[i].p);
	}

	return vecRet;

}
