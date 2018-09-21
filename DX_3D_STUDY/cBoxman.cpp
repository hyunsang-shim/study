#include "stdafx.h"

cBoxman::cBoxman()
	: m_vecRootPosition(0, 0, 0),
	m_vRootDirection(0,0,1),
	m_fRootRotationY(0.0f)
{
}


cBoxman::~cBoxman()
{
	SAFE_DELETE(m_pTexture);
}

void cBoxman::Setup()
{
	ST_PT_VERTEX	v;
	ST_PC_VERTEX	v2;

	//텍스쳐 정의
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("D.VA.png"), &m_pTexture);

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
	m_vecARM.push_back(D3DXVECTOR3(-0.3f, -2.0f, -0.3f));	m_vecARM.push_back(D3DXVECTOR3(-0.3f, 0.0f, -0.3f));
	m_vecARM.push_back(D3DXVECTOR3(0.3f, 0.0f, -0.3f));		m_vecARM.push_back(D3DXVECTOR3(0.3f, -2.0f, -0.3f));
	m_vecARM.push_back(D3DXVECTOR3(-0.3f, -2.0f, 0.3f));	m_vecARM.push_back(D3DXVECTOR3(-0.3f, 0.0f, 0.3f));
	m_vecARM.push_back(D3DXVECTOR3(0.3f, 0.0f, 0.3f));		m_vecARM.push_back(D3DXVECTOR3(0.3f, -2.0f, 0.3f));

	// for Legs
	m_vecLEG.push_back(D3DXVECTOR3(-0.3f, -2.0f, -0.3f));	m_vecLEG.push_back(D3DXVECTOR3(-0.3f, 0.0f, -0.3f));
	m_vecLEG.push_back(D3DXVECTOR3(0.3f, 0.0f, -0.3f));		m_vecLEG.push_back(D3DXVECTOR3(0.3f, -2.0f, -0.3f));
	m_vecLEG.push_back(D3DXVECTOR3(-0.3f, -2.0f, 0.3f));	m_vecLEG.push_back(D3DXVECTOR3(-0.3f, 0.0f, 0.3f));
	m_vecLEG.push_back(D3DXVECTOR3(0.3f, 0.0f, 0.3f));		m_vecLEG.push_back(D3DXVECTOR3(0.3f, -2.0f, 0.3f));

	// common vertex drawing order (triangle)
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

	// 각 부위별 텍스쳐 UV 좌표 저장
	SetTextureUV_HEAD();
	SetTextureUV_BODY();
	SetTextureUV_ARM();
	SetTextureUV_LEG();

	
	// 각 부위별 정점+텍스쳐 UV 좌표 세트를 그리기 순서에 맞게 배치
	// for head
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecHEAD[vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_HEAD[vecVerTex_Box_Index[i]];
		m_vecPT_HEAD.push_back(v);
	}

	// for Body
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecBODY[vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_BODY[vecVerTex_Box_Index[i]];
		m_vecPT_BODY.push_back(v);
	}

	// for Arms
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecARM[vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_ARM[vecVerTex_Box_Index[i]];
		m_vecPT_ARM.push_back(v);
	}

	// for Legs
	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecLEG[vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_LEG[vecVerTex_Box_Index[i]];
		m_vecPT_LEG.push_back(v);
	}

}

void cBoxman::Update()
{
	//루트의 S, R, T를 세팅은 MainGame에서 업데이트 해 준다.
	D3DXMatrixScaling(&m_matRootS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixRotationY(&m_matRootR, m_fRootRotationY);
	D3DXMatrixTranslation(&m_matRootT, m_vecRootPosition.x, m_vecRootPosition.y, m_vecRootPosition.z);


	// 각 부위별 S,R,T 매트릭스를 업데이트 하고, 최종 로컬 월드 매트릭스를 구한다.
	// 머리
	D3DXMatrixIdentity(&m_matHeadS);
	D3DXMatrixIdentity(&m_matHeadR);	
	D3DXMatrixTranslation(&m_matHeadT, 0, 3.5, 0);
	m_matWorld_Head = m_matRootS * m_matHeadS * m_matHeadR * m_matHeadT * m_matRootR * m_matRootT;

	// 몸
	D3DXMatrixIdentity(&m_matBodyS);
	D3DXMatrixIdentity(&m_matBodyR);
	D3DXMatrixTranslation(&m_matBodyT, 0, 2, 0);
	m_matWorld_Body = m_matRootS * m_matBodyS * m_matBodyR * m_matBodyT * m_matRootR * m_matRootT;

	// 왼팔
	D3DXMatrixScaling(&m_matArmLS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixIdentity(&m_matArmLR);
	D3DXMatrixTranslation(&m_matArmLT, 1.5, 2, 0);
	m_matWorld_ArmL = m_matRootS * m_matArmLS * m_matArmLR * m_matArmLT * m_matRootR * m_matRootT;


	// 오른팔
	D3DXMatrixScaling(&m_matArmRS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixIdentity(&m_matArmRR);
	D3DXMatrixRotationY(&m_matArmRR, -1);
	D3DXMatrixTranslation(&m_matArmRT, -1.5, 2, 0);
	m_matWorld_ArmR = m_matRootS * m_matArmRS * m_matArmRR * m_matArmRT * m_matRootR * m_matRootT;

	// 왼다리
	D3DXMatrixScaling(&m_matLegLS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixIdentity(&m_matLegLR);
	D3DXMatrixTranslation(&m_matLegLT, 0.5, -1, 0);
	m_matWorld_LegL = m_matRootS * m_matLegLS * m_matLegLR * m_matLegLT * m_matRootR * m_matRootT;

	// 오른다리
	D3DXMatrixScaling(&m_matLegRS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixRotationY(&m_matLegRR, -1);
	D3DXMatrixTranslation(&m_matLegRT, -0.5, -1, 0);
	m_matWorld_LegR = m_matRootS * m_matLegRS * m_matLegRR * m_matLegRT * m_matRootR * m_matRootT;


}

void cBoxman::Render()
{

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	// root position. initially 0,0,0
	// root Scale -> local Scale * Rotate * Transformation -> root Rotation * root Transformation

	// 머리
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_Head);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_HEAD.size() / 3, &m_vecPT_HEAD[0], sizeof(ST_PT_VERTEX));

	//몸
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_Body);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_BODY.size() / 3, &m_vecPT_BODY[0], sizeof(ST_PT_VERTEX));
	
	// 왼팔
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_ArmL);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_ARM.size() / 3, &m_vecPT_ARM[0], sizeof(ST_PT_VERTEX));
	
	// 오른팔
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_ArmR);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_ARM.size() / 3, &m_vecPT_ARM[0], sizeof(ST_PT_VERTEX));
	
	// 왼다리
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_LegL);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_LEG.size() / 3, &m_vecPT_LEG[0], sizeof(ST_PT_VERTEX));
	
	// 오른다리
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_LegR);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPT_LEG.size() / 3, &m_vecPT_LEG[0], sizeof(ST_PT_VERTEX));


	g_pD3DDevice->SetTexture(0, NULL);




}

void cBoxman::SetRootPosition(D3DXVECTOR3 Position)
{
	m_vecRootPosition = Position;
}

void cBoxman::SetRootDirection(D3DXVECTOR3 direction)
{
	m_vRootDirection = direction;
}

void cBoxman::SetTextureUV_HEAD()
{
	m_vTexture_HEAD.clear();
	// front
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y2));
	//back
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x4, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x4, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x4, y1));
	//left
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y2));
	//right
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y2));
	// top
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x1, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	// bottom
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(x3, 0));

}

void cBoxman::SetTextureUV_BODY()
{
	m_vTexture_BODY.clear();
	// front
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, 1));

	// back
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x5, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x5, 0));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x5, x5));

	// left
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1/2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x2 + x1/2.0, 1));
	// right
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x3 + x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x4, 1));
	// top
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1/2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1/2.0, y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1/2.0, y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1/2.0, x5));
	//bottom
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1 + x1 / 2.0, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1, x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(x1 + x1 / 2.0, x5));
}

void cBoxman::SetTextureUV_ARM()
{
	m_vTexture_ARM.clear();
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(4 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(4 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(4 / 8.0, 2 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_ARM.push_back(D3DXVECTOR2(3 / 8.0, 0));
}

void cBoxman::SetTextureUV_LEG()
{
	m_vTexture_LEG.clear();
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(1 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(4 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(4 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(4 / 8.0, 2 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(2 / 8.0, 0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 1 / 4.0));
	m_vTexture_LEG.push_back(D3DXVECTOR2(3 / 8.0, 0));
}

void cBoxman::SetRootRotationY(double valueY)
{
	m_fRootRotationY = valueY;
}

void cBoxman::SetRootScale(double scale)
{
	m_vRootScale.x = scale;
	m_vRootScale.y = scale;
	m_vRootScale.z = scale;
}
