#include "stdafx.h"

cBoxman::cBoxman()
	: m_vecRootPosition(0, 0, 0)
	, m_vRootDirection(0, 0, -1)
	, m_fRootRotationY(0.0f)
	, m_isMoving(false)
	, m_isRunning(false)
	, m_vSwingFactor(0.05f)
	, m_isJumping(false)
	, m_isJumping_Top(false)
	, m_fRotArmL(0.0f)
	, m_fRotArmR(0.0f)
	, m_fRotLegL(0.0f)
	, m_fRotLegR(0.0f)
	, m_CurPos(D3DXVECTOR3())
	, m_NextPos(D3DXVECTOR3())
	, m_pVB_Boxman_HEAD(NULL)
	, m_pVB_Boxman_ARM_L(NULL)
	, m_pVB_Boxman_ARM_R(NULL)
	, m_pVB_Boxman_LEG_L(NULL)
	, m_pVB_Boxman_LEG_R(NULL)
	, m_pVB_Boxman_BODY(NULL)
{

}


cBoxman::~cBoxman()
{
}

void cBoxman::Setup(TCHAR* filename)
{
	ST_PT_VERTEX	v;


	//텍스쳐 정의
	D3DXCreateTextureFromFile(g_pD3DDevice, filename, &m_pTexture);

	// for head
	m_vecHEAD.push_back(D3DXVECTOR3(-0.4f, -0.4f, -0.4f));	m_vecHEAD.push_back(D3DXVECTOR3(-0.4f, 0.4f, -0.4f));
	m_vecHEAD.push_back(D3DXVECTOR3(0.4f, 0.4f, -0.4f));	m_vecHEAD.push_back(D3DXVECTOR3(0.4f, -0.4f, -0.4f));
	m_vecHEAD.push_back(D3DXVECTOR3(-0.4f, -0.4f, 0.4f));	m_vecHEAD.push_back(D3DXVECTOR3(-0.4f, 0.4f, 0.4f));
	m_vecHEAD.push_back(D3DXVECTOR3(0.4f, 0.4f, 0.4f));		m_vecHEAD.push_back(D3DXVECTOR3(0.4f, -0.4f, 0.4f));

	// for Body
	m_vecBODY.push_back(D3DXVECTOR3(-0.4f, -0.6f, -0.2f));	m_vecBODY.push_back(D3DXVECTOR3(-0.4f, 0.6f, -0.2f));
	m_vecBODY.push_back(D3DXVECTOR3(0.4f, 0.6f, -0.2f));	m_vecBODY.push_back(D3DXVECTOR3(0.4f, -0.6f, -0.2f));
	m_vecBODY.push_back(D3DXVECTOR3(-0.4f, -0.6f, 0.2f));	m_vecBODY.push_back(D3DXVECTOR3(-0.4f, 0.6f, 0.2f));
	m_vecBODY.push_back(D3DXVECTOR3(0.4f, 0.6f, 0.2f));		m_vecBODY.push_back(D3DXVECTOR3(0.4f, -0.6f, 0.2f));

	// for Arms
	m_vecARM_L.push_back(D3DXVECTOR3(-0.2f, -1.3f, -0.2f));	m_vecARM_L.push_back(D3DXVECTOR3(-0.2f, 0.0f, -0.2f));
	m_vecARM_L.push_back(D3DXVECTOR3(0.2f, 0.0f, -0.2f));	m_vecARM_L.push_back(D3DXVECTOR3(0.2f, -1.3f, -0.2f));
	m_vecARM_L.push_back(D3DXVECTOR3(-0.2f, -1.3f, 0.2f));	m_vecARM_L.push_back(D3DXVECTOR3(-0.2f, 0.0f, 0.2f));
	m_vecARM_L.push_back(D3DXVECTOR3(0.2f, 0.0f, 0.2f));	m_vecARM_L.push_back(D3DXVECTOR3(0.2f, -1.3f, 0.2f));

	m_vecARM_R.push_back(D3DXVECTOR3(-0.2f, -1.3f, -0.2f));	m_vecARM_R.push_back(D3DXVECTOR3(-0.2f, 0.0f, -0.2f));
	m_vecARM_R.push_back(D3DXVECTOR3(0.2f, 0.0f, -0.2f));	m_vecARM_R.push_back(D3DXVECTOR3(0.2f, -1.3f, -0.2f));
	m_vecARM_R.push_back(D3DXVECTOR3(-0.2f, -1.3f, 0.2f));	m_vecARM_R.push_back(D3DXVECTOR3(-0.2f, 0.0f, 0.2f));
	m_vecARM_R.push_back(D3DXVECTOR3(0.2f, 0.0f, 0.2f));	m_vecARM_R.push_back(D3DXVECTOR3(0.2f, -1.3f, 0.2f));

	// for Legs
	m_vecLEG_L.push_back(D3DXVECTOR3(-0.2f, -1.2f, -0.2f));	m_vecLEG_L.push_back(D3DXVECTOR3(-0.2f, 0.0f, -0.2f));
	m_vecLEG_L.push_back(D3DXVECTOR3(0.2f, 0.0f, -0.2f));	m_vecLEG_L.push_back(D3DXVECTOR3(0.2f, -1.2f, -0.2f));
	m_vecLEG_L.push_back(D3DXVECTOR3(-0.2f, -1.2f, 0.2f));	m_vecLEG_L.push_back(D3DXVECTOR3(-0.2f, 0.0f, 0.2f));
	m_vecLEG_L.push_back(D3DXVECTOR3(0.2f, 0.0f, 0.2f));	m_vecLEG_L.push_back(D3DXVECTOR3(0.2f, -1.2f, 0.2f));


	m_vecLEG_R.push_back(D3DXVECTOR3(-0.2f, -1.2f, -0.2f));	m_vecLEG_R.push_back(D3DXVECTOR3(-0.2f, 0.0f, -0.2f));
	m_vecLEG_R.push_back(D3DXVECTOR3(0.2f, 0.0f, -0.2f));	m_vecLEG_R.push_back(D3DXVECTOR3(0.2f, -1.2f, -0.2f));
	m_vecLEG_R.push_back(D3DXVECTOR3(-0.2f, -1.2f, 0.2f));	m_vecLEG_R.push_back(D3DXVECTOR3(-0.2f, 0.0f, 0.2f));
	m_vecLEG_R.push_back(D3DXVECTOR3(0.2f, 0.0f, 0.2f));	m_vecLEG_R.push_back(D3DXVECTOR3(0.2f, -1.2f, 0.2f));

	// common vertex drawing order (triangle)
	m_vecVerTex_Box_Index.push_back(0);	m_vecVerTex_Box_Index.push_back(1);	m_vecVerTex_Box_Index.push_back(2);
	m_vecVerTex_Box_Index.push_back(0);	m_vecVerTex_Box_Index.push_back(2);	m_vecVerTex_Box_Index.push_back(3);

	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(6);	m_vecVerTex_Box_Index.push_back(5);
	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(7);	m_vecVerTex_Box_Index.push_back(6);

	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(5);	m_vecVerTex_Box_Index.push_back(1);
	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(1);	m_vecVerTex_Box_Index.push_back(0);

	m_vecVerTex_Box_Index.push_back(3);	m_vecVerTex_Box_Index.push_back(2);	m_vecVerTex_Box_Index.push_back(6);
	m_vecVerTex_Box_Index.push_back(3);	m_vecVerTex_Box_Index.push_back(6);	m_vecVerTex_Box_Index.push_back(7);

	m_vecVerTex_Box_Index.push_back(1);	m_vecVerTex_Box_Index.push_back(5);	m_vecVerTex_Box_Index.push_back(6);
	m_vecVerTex_Box_Index.push_back(1);	m_vecVerTex_Box_Index.push_back(6);	m_vecVerTex_Box_Index.push_back(2);

	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(0);	m_vecVerTex_Box_Index.push_back(3);
	m_vecVerTex_Box_Index.push_back(4);	m_vecVerTex_Box_Index.push_back(3);	m_vecVerTex_Box_Index.push_back(7);

	// 각 부위별 텍스쳐 UV 좌표 저장
	SetTextureUV_HEAD();
	SetTextureUV_BODY();
	SetTextureUV_ARM_L();
	SetTextureUV_ARM_R();
	SetTextureUV_LEG_L();
	SetTextureUV_LEG_R();


	// 각 부위별 정점+텍스쳐 UV 좌표 세트를 그리기 순서에 맞게 배치
	// for head
	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecHEAD[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_HEAD[i];
		strBoxman.HEAD.push_back(v);
	}

	// for Body
	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecBODY[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_BODY[i];
		strBoxman.BODY.push_back(v);
	}

	// for Arms
	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecARM_L[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_ARM_L[i];
		strBoxman.ARM_L.push_back(v);
	}

	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecARM_R[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_ARM_R[i];
		strBoxman.ARM_R.push_back(v);
	}

	// for Legs
	// Left leg
	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecLEG_L[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_LEG_L[i];
		strBoxman.LEG_L.push_back(v);
	}

	// Left leg
	for (int i = 0; i < m_vecVerTex_Box_Index.size(); i++)
	{
		v.p = m_vecLEG_R[m_vecVerTex_Box_Index[i]];
		v.texture1 = m_vTexture_LEG_R[i];
		strBoxman.LEG_R.push_back(v);
	}

	// 버텍스 버퍼용 세팅 시작
	{
		{
			// 머리
			strBoxman.nCntHEADTriangles = strBoxman.HEAD.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.HEAD.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_HEAD,
				NULL);

			ST_PT_VERTEX* pV_HEAD = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_HEAD->Lock(0, 0, (LPVOID*)&pV_HEAD, 0);

			// 메모리 카피
			memcpy(pV_HEAD, &strBoxman.HEAD[0], strBoxman.HEAD.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_HEAD->Unlock();


		}
		{
			// 몸통
			strBoxman.nCntBODYTriangles = strBoxman.BODY.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.BODY.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_BODY,
				NULL);

			ST_PT_VERTEX* pV_BODY = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_BODY->Lock(0, 0, (LPVOID*)&pV_BODY, 0);

			// 메모리 카피
			memcpy(pV_BODY, &strBoxman.BODY[0], strBoxman.BODY.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_BODY->Unlock();
		}

		{
			// 왼팔
			strBoxman.nCntARM_LTriangles = strBoxman.ARM_L.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.ARM_L.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_ARM_L,
				NULL);

			ST_PT_VERTEX* pV_ARM_L = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_ARM_L->Lock(0, 0, (LPVOID*)&pV_ARM_L, 0);

			// 메모리 카피
			memcpy(pV_ARM_L, &strBoxman.ARM_L[0], strBoxman.ARM_L.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_ARM_L->Unlock();
		}
		{
			// 오른팔
			strBoxman.nCntARM_RTriangles = strBoxman.ARM_R.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.ARM_R.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_ARM_R,
				NULL);

			ST_PT_VERTEX* pV_ARM_R = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_ARM_R->Lock(0, 0, (LPVOID*)&pV_ARM_R, 0);

			// 메모리 카피
			memcpy(pV_ARM_R, &strBoxman.ARM_R[0], strBoxman.ARM_R.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_ARM_R->Unlock();
		}
		{
			// 왼다리
			strBoxman.nCntLEG_LTriangles = strBoxman.LEG_L.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.LEG_L.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_LEG_L,
				NULL);

			ST_PT_VERTEX* pV_LEG_L = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_LEG_L->Lock(0, 0, (LPVOID*)&pV_LEG_L, 0);

			// 메모리 카피
			memcpy(pV_LEG_L, &strBoxman.LEG_L[0], strBoxman.LEG_L.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_LEG_L->Unlock();
		}
		{
			// 오른다리
			strBoxman.nCntLEG_RTriangles = strBoxman.LEG_R.size() / 3;
			g_pD3DDevice->CreateVertexBuffer(strBoxman.LEG_R.size() * sizeof(ST_PT_VERTEX),
				0, ST_PT_VERTEX::FVF,
				D3DPOOL_MANAGED,
				&m_pVB_Boxman_LEG_R,
				NULL);

			ST_PT_VERTEX* pV_LEG_R = NULL;


			// 메모리 카피 시작
			m_pVB_Boxman_LEG_R->Lock(0, 0, (LPVOID*)&pV_LEG_R, 0);

			// 메모리 카피
			memcpy(pV_LEG_R, &strBoxman.LEG_R[0], strBoxman.LEG_R.size() * sizeof(ST_PT_VERTEX));

			// 메모리 카피 종료
			m_pVB_Boxman_LEG_R->Unlock();
		}

	}


	D3DXMatrixIdentity(&m_matBodyS);
	D3DXMatrixIdentity(&m_matBodyR);
	D3DXMatrixIdentity(&m_matHeadS);
	D3DXMatrixIdentity(&m_matHeadR);
	D3DXMatrixIdentity(&m_matArmLS);
	D3DXMatrixIdentity(&m_matArmLR);
	D3DXMatrixIdentity(&m_matArmRS);
	D3DXMatrixIdentity(&m_matArmRR);
	D3DXMatrixIdentity(&m_matLegLS);
	D3DXMatrixIdentity(&m_matLegLR);
	D3DXMatrixIdentity(&m_matLegRS);
	D3DXMatrixIdentity(&m_matLegRR);
}

void cBoxman::Update()
{
	static int DirFactor = 1;
	//루트의 S, R, T를 세팅은 MainGame에서 업데이트 해 준다.
	D3DXMatrixScaling(&m_matRootS, m_vRootScale.x, m_vRootScale.y, m_vRootScale.z);
	D3DXMatrixRotationY(&m_matRootR, m_fRootRotationY);
	D3DXMatrixTranslation(&m_matRootT, m_vecRootPosition.x, m_vecRootPosition.y, m_vecRootPosition.z);
	/*m_CurPos = m_NextPos * 0.1f;
	D3DXMatrixTranslation(&m_matRootT, m_CurPos.x, m_CurPos.y, m_CurPos.z);*/


	// 각 부위별 S,R,T 매트릭스를 업데이트 하고, 최종 로컬 월드 매트릭스를 구한다.
	// 머리
	
	D3DXMatrixTranslation(&m_matHeadT, 0, 2.8, 0);
	m_matWorld_Head = m_matRootS * m_matHeadS * m_matHeadR * m_matHeadT * m_matRootR * m_matRootT;

	// 몸
	
	D3DXMatrixTranslation(&m_matBodyT, 0, 1.8, 0);
	m_matWorld_Body = m_matRootS * m_matBodyS * m_matBodyR * m_matBodyT * m_matRootR * m_matRootT;

	if (m_isRunning)
		m_vSwingFactor = 0.1f;
	else
		m_vSwingFactor = 0.05f;
	
	// 왼팔
	if (m_isJumping)
	{
		m_fRotArmL = 0.7f * DirFactor;
	}	
	else if (m_isMoving)
	{
		if (m_fRotArmL + EPSILON > 0.7f || m_fRotArmL + EPSILON < -0.7f)
			DirFactor *= -1;

		m_fRotArmL += m_vSwingFactor * DirFactor;
	}
	else
		m_fRotArmL = 0.0f;
	
	
	D3DXMatrixRotationX(&m_matArmLR, m_fRotArmL);
	D3DXMatrixTranslation(&m_matArmLT, 0.6, 2.4, 0);
	m_matWorld_ArmL = m_matRootS * m_matArmLS * m_matArmLR * m_matArmLT * m_matRootR * m_matRootT;

	// 오른팔
	if (m_isJumping)
	{
		m_fRotArmR = -0.7f * DirFactor;
	}
	else if (m_isMoving)
	{		
		m_fRotArmR -= m_vSwingFactor * DirFactor;
	}
	else
		m_fRotArmR = 0.0f;

	D3DXMatrixRotationX(&m_matArmRR, m_fRotArmR);
	D3DXMatrixTranslation(&m_matArmRT, -0.6,2.4,0);
	m_matWorld_ArmR = m_matRootS * m_matArmRS * m_matArmRR * m_matArmRT * m_matRootR * m_matRootT;

	// 왼다리
	if (m_isJumping)
	{
		m_fRotLegL = -0.7f * DirFactor;
	}
	else if (m_isMoving)
	{
		m_fRotLegL -= m_vSwingFactor * DirFactor;
	}
	else
		m_fRotLegL = 0.0f;

	D3DXMatrixRotationX(&m_matLegLR, m_fRotLegL);
	D3DXMatrixTranslation(&m_matLegLT, 0.2, 1.2, 0);
	m_matWorld_LegL = m_matRootS * m_matLegLS * m_matLegLR * m_matLegLT * m_matRootR * m_matRootT;

	//// 오른다리
	if (m_isJumping)
	{
		m_fRotLegR = 0.7f * DirFactor;
	}
	else if (m_isMoving)
	{
		m_fRotLegR += m_vSwingFactor * DirFactor;
	}
	else
		m_fRotLegR = 0.0f;

	D3DXMatrixRotationX(&m_matLegRR, m_fRotLegR);	
	D3DXMatrixTranslation(&m_matLegRT, -0.2, 1.2, 0);
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
	// 일반 버텍스 그리기(CPU+RAM)
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.HEAD.size() / 3, &strBoxman.HEAD[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기(GPU+VRAM)
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_HEAD, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntHEADTriangles);
	}
	////몸
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_Body);
	////g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.BODY.size() / 3, &strBoxman.BODY[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_BODY, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntBODYTriangles);
	}
	//
	//// 왼팔
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_ArmL);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.ARM_L.size() / 3, &strBoxman.ARM_L[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_ARM_L, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntARM_LTriangles);
	}
	//
	//// 오른팔
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_ArmR);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.ARM_R.size() / 3, &strBoxman.ARM_R[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_ARM_R, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntARM_RTriangles);
	}

	//
	//// 왼다리
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_LegL);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.LEG_L.size() / 3, &strBoxman.LEG_L[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_LEG_L, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntLEG_LTriangles);
	}

	//// 오른다리
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld_LegR);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, strBoxman.LEG_R.size() / 3, &strBoxman.LEG_R[0], sizeof(ST_PT_VERTEX));
	{
		// 버텍스 버퍼 그리기
		 g_pD3DDevice->SetStreamSource(0, m_pVB_Boxman_LEG_R, 0, sizeof(ST_PT_VERTEX));
		 g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, strBoxman.nCntLEG_RTriangles);
	}


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
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y2));
	//back
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x4, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x4, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x4, UV_y1));
	//left
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(0, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	//right
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y2));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y2));
	// top
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x1, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y1));
	// bottom
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x2, 0));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, UV_y1));
	m_vTexture_HEAD.push_back(D3DXVECTOR2(UV_x3, 0));

}

void cBoxman::SetTextureUV_BODY()
{
	m_vTexture_BODY.clear();
	// front
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, 1));

	// back
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x5, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x5, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x5, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, UV_x5));

	// left
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1/2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1/2.0, 1));
	// right
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, 1));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x4, 1));
	// top
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, UV_y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x2 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x3 + UV_x1 / 2.0, UV_x5));
	//bottom
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_BODY.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
}

void cBoxman::SetTextureUV_ARM_L()
{
	m_vTexture_ARM_L.clear();
	// front
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));
	//back
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x7, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x7, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x7, UV_x5));
	//left
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, 1));

	//right
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5, 1));
	//top
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5+ UV_x1 / 2.0, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	//bottom
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_L.push_back(D3DXVECTOR2(UV_x6, UV_x5));
}

void cBoxman::SetTextureUV_ARM_R()
{
	m_vTexture_ARM_R.clear();
	// front
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, 1));
	//back
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x7, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x7, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x7, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	//left
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, 1));

	//right
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, 1));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, 1));

	//top
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x5 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
	//bottom
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6 + UV_x1 / 2.0, UV_x5));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_y2));
	m_vTexture_ARM_R.push_back(D3DXVECTOR2(UV_x6, UV_x5));
}

void cBoxman::SetTextureUV_LEG_L()
{
	m_vTexture_LEG_L.clear();
	// front
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	//back
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x2, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x2, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x2, UV_x5));
	//left
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, 1));
	//right
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(0, 1));
	//top
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_y2));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_y2));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	//bottom
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_y2));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_y2));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_L.push_back(D3DXVECTOR2(UV_x1, UV_y2));
}

void cBoxman::SetTextureUV_LEG_R()
{
	m_vTexture_LEG_R.clear();
	// front
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, 1));
	//back
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x2, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x2, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x2, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	//left
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(0, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(0, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, 1));
	//right
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, 1));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 +UV_x1 / 2.0, 1));
	//top
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_y2));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	//bottom
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1, UV_y2));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_x5));
	m_vTexture_LEG_R.push_back(D3DXVECTOR2(UV_x1 + UV_x1 / 2.0, UV_y2));
}


void cBoxman::SetMoveState(bool move, bool run)
{
	m_isMoving = move;
	m_isRunning = run;
}

void cBoxman::SetjumpState(bool value1, bool value2)
{
	m_isJumping = value1;
	m_isJumping_Top = value2;
}

void cBoxman::SetCurPos(D3DXVECTOR3 newCurPos)
{
	m_vecRootPosition = newCurPos;
}

D3DXVECTOR3 cBoxman::GetCurPos()
{
	return m_CurPos;
}

void cBoxman::SetNextPos(D3DXVECTOR3 newNextPos)
{
	m_NextPos = newNextPos;
}

D3DXVECTOR3 cBoxman::GetNextPos()
{
	return m_NextPos;
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
