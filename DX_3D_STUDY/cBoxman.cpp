#include "stdafx.h"

cBoxman::cBoxman()
	: m_vecRootPosition(0, 0, 0),
	m_vRootDirection(0,0,1),
	m_fRootRotationY(0.0f)
{
}


cBoxman::~cBoxman()
{
}

void cBoxman::Setup()
{


	// for head
	m_vecHEAD.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));	m_vecHEAD.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	m_vecHEAD.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));	m_vecHEAD.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));
	m_vecHEAD.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));	m_vecHEAD.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	m_vecHEAD.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));		m_vecHEAD.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	
	// for Body
	m_vecBODY.push_back(D3DXVECTOR3(-1.0f, -1.0f, -0.3f));	m_vecBODY.push_back(D3DXVECTOR3(-1.0f, 1.0f, -0.3f));
	m_vecBODY.push_back(D3DXVECTOR3(1.0f, 1.0f, -0.3f));	m_vecBODY.push_back(D3DXVECTOR3(1.0f, -1.0f, -0.3f));
	m_vecBODY.push_back(D3DXVECTOR3(-1.0f, -1.0f, 0.3f));	m_vecBODY.push_back(D3DXVECTOR3(-1.0f, 1.0f, 0.3f));
	m_vecBODY.push_back(D3DXVECTOR3(1.0f, 1.0f, 0.3f));		m_vecBODY.push_back(D3DXVECTOR3(1.0f, -1.0f, 0.3f));

	// for Arms
	m_vecARM.push_back(D3DXVECTOR3(-0.3f, -1.0f, -0.3f));	m_vecARM.push_back(D3DXVECTOR3(-0.3f, 1.0f, -0.3f));
	m_vecARM.push_back(D3DXVECTOR3(0.3f, 1.0f, -0.3f));		m_vecARM.push_back(D3DXVECTOR3(0.3f, -1.0f, -0.3f));
	m_vecARM.push_back(D3DXVECTOR3(-0.3f, -1.0f, 0.3f));	m_vecARM.push_back(D3DXVECTOR3(-0.3f, 1.0f, 0.3f));
	m_vecARM.push_back(D3DXVECTOR3(0.3f, 1.0f, 0.3f));		m_vecARM.push_back(D3DXVECTOR3(0.3f, -1.0f, 0.3f));

	// for Legs
	m_vecLEG.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));	m_vecLEG.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	m_vecLEG.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));		m_vecLEG.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));
	m_vecLEG.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));	m_vecLEG.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	m_vecLEG.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));		m_vecLEG.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	// common vertex drawing order (triangle)
	ST_PC_VERTEX	v;
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


	// for head
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecHEAD[vecVerTex_Box_Index[i]];
		if (i % 6 == 0)		v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		m_vecPC_HEAD.push_back(v);
	}

	// for Body
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecBODY[vecVerTex_Box_Index[i]];
		if (i % 6 == 0)		v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		m_vecPC_BODY.push_back(v);
	}

	// for Arms
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecARM[vecVerTex_Box_Index[i]];
		if (i % 6 == 0)		v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		m_vecPC_ARM.push_back(v);
	}

	// for Legs
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecLEG[vecVerTex_Box_Index[i]];
		if (i % 6 == 0)		v.color = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		m_vecPC_LEG.push_back(v);
	}

}

void cBoxman::Update()
{
}

void cBoxman::Render()
{

	D3DXMATRIXA16		matLocalSRT;
	D3DXMATRIXA16		matRootS;
	D3DXMATRIXA16		matRootR;
	D3DXMATRIXA16		matRootT;

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	// root position. initially 0,0,0
	// root Scale -> local Scale * Rotate * Transformation -> root Rotation * root Transformation
	D3DXMatrixIdentity(&matRootS);
	D3DXMatrixIdentity(&matRootR);
	D3DXMatrixIdentity(&matRootT);
	D3DXMatrixIdentity(&matLocalSRT);

	// Body

	// Head

	// L-Arm
	// R-Arm

	// L-Leg
	// R-Leg


	//// Right Arm
	//D3DXMatrixIdentity(&matScale);
	//D3DXMatrixIdentity(&matRot);
	//D3DXMatrixTranslation(&matTrans, m_vecRootPosition.x - 1.5, m_vecRootPosition.y, m_vecRootPosition.z);

	//matRT = matScale * matRot * matTrans;
	//m_matWorld = matRootRT * matRT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPC_ARM.size() / 3, &m_vecPC_ARM[0], sizeof(ST_PC_VERTEX));


	//// Left Leg
	//D3DXMatrixIdentity(&matScale);
	//D3DXMatrixIdentity(&matRot);
	//D3DXMatrixTranslation(&matTrans, m_vecRootPosition.x + 1.5, m_vecRootPosition.y, m_vecRootPosition.z);

	//matRT = matScale * matRot * matTrans;
	//m_matWorld = matRootRT * matRT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPC_LEG.size() / 3, &m_vecPC_LEG[0], sizeof(ST_PC_VERTEX));

	//// Right Leg
	//D3DXMatrixIdentity(&matScale);
	//D3DXMatrixIdentity(&matRot);
	//D3DXMatrixTranslation(&matTrans, m_vecRootPosition.x - 1.5, m_vecRootPosition.y, m_vecRootPosition.z);

	//matRT = matScale * matRot * matTrans;
	//m_matWorld = matRootRT * matRT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPC_LEG.size() / 3, &m_vecPC_LEG[0], sizeof(ST_PC_VERTEX));



}

void cBoxman::SetRootPosition(D3DXVECTOR3 Position)
{
	m_vecRootPosition = Position;
}

void cBoxman::SetRootDirection(D3DXVECTOR3 direction)
{
	m_vRootDirection = direction;
}

void cBoxman::SetRootRotationY(double valueY)
{
	m_fRootRotationY = valueY;
}

void cBoxman::SetRootScale(double scale)
{
	m_fRootScale = scale;
}
