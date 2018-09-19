#include "stdafx.h"

cCubePC::cCubePC()
	:m_vBoxDirection(0, 0, 1),
	m_vPosition(0, 0, 0),
	m_fScale(1.0f),
	m_fBoxRotY(0.1f)
{	 
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{}

void cCubePC::Setup()
{
	ST_PC_VERTEX	v;
	v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);

	
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
		m_vecVertex.push_back(v);
	}
}

void cCubePC::Update()
{

	//박스의 회전
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}


	// 박스의 이동

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1f);
	}



	//박스의 스케일
	if (GetKeyState('Z') & 0x8000)
	{
		m_fScale += 0.1f;
		if (m_fScale > 2.0f)
			m_fScale = 2.0f;
	}

	if (GetKeyState('X') & 0x8000)
	{

		m_fScale -= 0.1f;
		if (m_fScale < 0.2f)
			m_fScale = 0.2f;
	}



}

void cCubePC::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & cCubePC::GetPosition()
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	return m_vPosition;
}

double cCubePC::GetScale()
{
	return m_fScale;
}

double cCubePC::GetRotationY()
{
	return m_fBoxRotY;
}
