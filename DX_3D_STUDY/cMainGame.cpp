#pragma once
#include "stdafx.h"
#include "cMainGame.h"
#include "cSkinnedMesh.h"
#include "cZealot.h"
#include "cOBB.h"
#include "cFontManager.h" // ��Ʈ�Ŵ���
// ui ����
#include "cUIImageView.h"
#include "cUIButton.h"
#include "cUITextView.h"

enum
{
	E_BUTTON_OK = 11,
	E_BUTTON_CANCEL,
	E_BUTTON_EXIT,
	E_TEXT_VIEW,
};
class cCubePC;
class cBoxman;
class cCamera;
class cGrid;
class cHexagon;
class ObjLoader;
class cMap;
class cASE_Char;

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_vecNormalBoxman(NULL)
	, m_vecBesierBoxman(NULL)
	, m_pGrid(NULL)
	, m_pTexture(NULL)
	, m_vecOriginalBox(NULL)
	, m_pHexagon(NULL)
	, m_pMap(NULL)
	, m_pASE_Char(NULL)
	, m_pBoxman(NULL)
	, m_pMeshTeapot(NULL)
	, m_pHeightmap(NULL)
	, m_pLoadFromX(NULL)			// x ���� �ҷ�����
//	, m_pFrustum(NULL)
	, m_pHoldZealot(NULL)
	, m_pMoveZealot(NULL)
	, m_vEye(10, 8, -15)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vBoxPosition(2,0,-1)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_isMButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fCamTransY(0)
	, m_fBoxRotY(0.0f)
	, m_vBoxDirection(0, 0, -1)
	, m_fBoxScale(1.0f)
	, m_swDirLight(true)
	, m_swSpotLight(true)
	, m_isMoving(false)
	, m_isRunning(false)
	, m_isRotating(false)
	, m_isJumping(false)
	, m_isJumping_Top(false)
	, m_isCamFollow(false)
	, m_pRootFrame(NULL)		// ����� ASE �δ�
	, m_pSkinnedMesh(NULL)
	, m_pFont_a(NULL)		// ����� ��Ʈ ����
	, m_p3DText (NULL)		// ����� ��Ʈ ����
	, m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pUIRoot(NULL)
	, m_pTex0(NULL)
	, m_pTex1(NULL)
	, m_pTex2(NULL)


{
	g_pDeviceManager;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}

cMainGame::~cMainGame()
{

	if (m_pUIRoot) m_pUIRoot->Destroy();
	SAFE_RELEASE(m_pFont_a);
	SAFE_RELEASE(m_p3DText);
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pTexture);

	
	SAFE_DELETE(m_pHexagon);
	SAFE_DELETE(m_pASE_Char);

	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pMap);
	//SAFE_DELETE(m_pCubeman);

	// ����� ASE �δ�
	/*m_pRootFrame->Destroy();	
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();*/

	SAFE_DELETE(m_pSkinnedMesh);

	SAFE_RELEASE(m_pMeshTeapot);
	SAFE_DELETE(m_pLoadFromX);
	//SAFE_DELETE(m_pFrustum);

	
	SAFE_DELETE(m_pHoldZealot);
	SAFE_DELETE(m_pMoveZealot);

	g_pDeviceManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pFontManager->Destroy();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTextureUI);

	SAFE_RELEASE(m_pTex0);
	SAFE_RELEASE(m_pTex1);
}


void cMainGame::Setup() 
{
	srand(time(NULL));

	Create_Font();
	/*m_pASE_Char = new cASE_Char;
	m_pASE_Char->Setup();*/

	// �޽� ������ ����
	Mesh_Setup();
	
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	InitMaterial();
	InitLights();
	
	GetClientRect(g_hWnd, &m_RectTxtArea);

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();
	m_pCubePC->SetBoxPosition(D3DXVECTOR3(1.0f, 0.0f, 1.0f));

	m_pBoxman = new cBoxman;
	m_pBoxman->Setup(_T("D.VA.png"));
		
	//m_pMap = new cMap;
	//m_pMap->Setup();

	//m_pHeightmap = new cHeightMap;
	//m_pHeightmap->Setup("HeightMap/HeightMap.raw");

	//// ����� ASE�δ�
	//cASELoader_inst loader;
	//m_pRootFrame = loader.Load("woman/woman_01_all.ASE");
	////m_pRootFrame = loader.Load("ASE/gun.ASE");


	//{
	//	m_pLoadFromX = new cLoadXFile;
	//	m_pLoadFromX->Setup("Xfile/bigship1.x");
	//}

	// Skinned Mesh Setup
	{
		//m_pSkinnedMesh = new cSkinnedMesh;
		//m_pSkinnedMesh->Setup("Zealot", "zealot.X");
	}

	{
//		m_pFrustum = new cFrustumCulling;
//		m_pFrustum->Setup();
	}

	// OBB �浹 ���� ����
	{
		m_pHoldZealot = new cZealot;
		m_pHoldZealot->Setup();
		

		m_pMoveZealot = new cZealot;
		m_pMoveZealot->Setup();
		cCharacter* pCharacter = new cCharacter;
		m_pMoveZealot->SetCharacterController(pCharacter);
		SAFE_RELEASE(pCharacter);
	}

	// ����� UI ����
	Setup_UI();

	Setup_Multitexture();

}

void cMainGame::Update(){
	


	// ĳ����(Boxmax)�� ��Ʈ ������ �ϴ� �ڽ�.	
	if (m_pCubePC)
	{

		m_pCubePC->SetBoxScale(1.0f);
		m_pCubePC->Update();

		//
		// Boxman �̵� ���� ó��
		//
		//�ڽ��� ȸ��
		if (GetKeyState('A') & 0x8000)
		{
			m_isRotating = true;
		}
		else if (GetKeyState('D') & 0x8000)
		{
			m_isRotating = true;
		}
		else
			m_isRotating = false;

		// �ڽ��� �̵�
		double fMin = m_pGrid->GetGridMinMax().left;
		double fMax = m_pGrid->GetGridMinMax().right;

		if (GetKeyState('W') & 0x8000)
		{
			m_isMoving = true;
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * -0.18f);
				m_isRunning = true;
			}
			else
			{
				m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * -0.1f);
				m_isRunning = false;

			}

			// ĳ���Ͱ� �׸��� ������ ���������� ������ �����Ѵ�.
			if (m_vBoxPosition.x >= fMax)
				m_vBoxPosition.x = fMax;
			else if (m_vBoxPosition.x <= fMin)
				m_vBoxPosition.x = fMin;

			if (m_vBoxPosition.z >= fMax)
				m_vBoxPosition.z = fMax;
			else if (m_vBoxPosition.z <= fMin)
				m_vBoxPosition.z = fMin;


		}
		else if (GetKeyState('S') & 0x8000)
		{
			m_isMoving = true;
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.18f);
				m_isRunning = true;
			}
			else
			{

				m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.1f);
				m_isRunning = false;
			}


			if (m_vBoxPosition.x >= fMax)
				m_vBoxPosition.x = fMax;
			else if (m_vBoxPosition.x <= fMin)
				m_vBoxPosition.x = fMin;

			if (m_vBoxPosition.z >= fMax)
				m_vBoxPosition.z = fMax;
			else if (m_vBoxPosition.z <= fMin)
				m_vBoxPosition.z = fMin;
		}
		else
			m_isMoving = false;

		// �ڽ��� ����

		if (m_isJumping && !m_isJumping_Top)
		{
			if (m_vBoxPosition.y < 1.0 + EPSILON)
				m_vBoxPosition.y += 0.125f;
			else
			{
				m_isJumping_Top = true;
			}

		}
		else if (m_isJumping && m_isJumping_Top)
		{

			if (m_vBoxPosition.y >= 0.0f + EPSILON)
				m_vBoxPosition.y -= 0.125f;
			else
			{
				m_vBoxPosition.y = 0.0000000f;
				m_isJumping = false;
				m_isJumping_Top = false;
			}

		}

		// ĳ���Ϳ� �̵� ���¸� �����Ѵ�.		
		if (m_pBoxman)
		{
			m_pBoxman->SetMoveState(m_isMoving | m_isRotating, m_isRunning);
			m_pBoxman->SetjumpState(m_isJumping, m_isJumping_Top);
			//m_pBoxman->SetRootPosition(m_vBoxPosition);
			//m_pBoxman->SetRootDirection(m_vBoxDirection);
			//m_pBoxman->SetRootRotationY(m_fBoxRotY);
			m_pBoxman->SetRootScale(m_fBoxScale);
		}
	}

	//ī�޶� ������Ʈ
	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);
		m_pCamera->Update();
	}

	// map update
	/*if (m_pMap)
		m_pMap->Update();*/

	if (m_pBoxman)
		m_pBoxman->Update();

	// ����� ĳ���� �׸���
	/*
	if (m_pCubeman)
		m_pCubeman->Update();
	*/

	// ����� ASE�δ�
	/*if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);*/

//	if (m_pSkinnedMesh)
//		m_pSkinnedMesh->Update();

	// OBB �浹 ���� ����
	{
		if (m_pHoldZealot)
			m_pHoldZealot->Update();

		if (m_pMoveZealot)
			m_pMoveZealot->Update();
	}

	// ����� UI ����
	if (m_pUIRoot)
		m_pUIRoot->Update();

}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Draw and Set Lights	
	g_pD3DDevice->SetMaterial(&m_matWhite);  // ���Ͽ��� �ҷ��� ���͸��� Ȯ���� ���� �ּ�ó�� ��
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetLight(0, &SpotLight);
	g_pD3DDevice->SetLight(1, &PointLight);


	if (m_swDirLight)
		g_pD3DDevice->SetLight(2, &DirLight);
	else
		g_pD3DDevice->SetLight(3, &DirLight_Default);

	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->LightEnable(1, true);

	if (m_swDirLight)
	{
		g_pD3DDevice->LightEnable(2, true);
		g_pD3DDevice->LightEnable(3, false);
	}
	else
	{
		g_pD3DDevice->LightEnable(2, false);
		g_pD3DDevice->LightEnable(3, true);
	}

	if (m_swSpotLight)
	{
		g_pD3DDevice->LightEnable(0, true);
	}
	else
		g_pD3DDevice->LightEnable(0, false);



	// Draw Something
	if (m_pGrid)
		m_pGrid->Render();


	g_pTimeManager->Update();
	//if (m_pSkinnedMesh)
	//	m_pSkinnedMesh->Render(NULL);
	//if (m_pFont)
	//{
	//	m_pFont->DrawTextA(NULL, message.c_str(), -1, &m_RectTxtArea, DT_LEFT, D3DCOLOR_XRGB(200, 200, 200));
	//}


	//if (m_pFrustum)
//		m_pFrustum->Render();

	// ����� �߻�ȭ Ŭ���� ���
	/* 
	if (m_pCubeman)
		m_pCubeman->Render();
	
	// sample code
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16	matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetTexture(0, m_pTexture);	// �ؽ��� ��� ����
		g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

		g_pD3DDevice->SetTexture(0, NULL);	// �ؽ��� ��� ���� ���� ����
	}
	*/
	


	if (m_pCubePC)
		m_pCubePC->Render();

	if (m_pMap)
		m_pMap->Render();

	if (m_pHexagon)
		m_pHexagon->Render();

	if (m_pBoxman)
		m_pBoxman->Render();


	if (m_pASE_Char)
		m_pASE_Char->Render();


	if (m_pRootFrame)
		m_pRootFrame->Render();

	// �޽� ������ ����
	//Mesh_Render();

	//if (m_pHeightmap)
	//	m_pHeightmap->Render();

	/*if (m_pLoadFromX)
		m_pLoadFromX->Render();*/

	// OBB �浹 ���� ����
	/*{
		D3DCOLOR c = cOBB::IsCollision(m_pHoldZealot->GetOBB(),	m_pMoveZealot->GetOBB()) ? D3DCOLOR_XRGB(200, 0, 0) : D3DCOLOR_XRGB(128, 128, 128);

		if (m_pHoldZealot)
			m_pHoldZealot->Render(c);

		if (m_pMoveZealot)
			m_pMoveZealot->Render(c);

	}*/



	// ����� UI ���� ����
	Render_UI();
	Render_Text();
	Render_Multitexture();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);



}

void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	matWorld = matS * matR;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMrlTeapot);
	m_pMeshTeapot->DrawSubset(0);


}

void cMainGame::Mesh_Setup()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	ZeroMemory(&m_stMrlTeapot, sizeof(D3DMATERIAL9));
	m_stMrlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMrlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMrlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
		
}

void cMainGame::InitMaterial()
{
	m_matWhite.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_matWhite.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_matWhite.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_matWhite.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_matWhite.Power = 8.0f;	
}

void cMainGame::InitLights()
{
	DirLight.Type = D3DLIGHT_DIRECTIONAL;
	DirLight.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	DirLight.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	DirLight.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	DirLight.Direction = D3DXVECTOR3(1, 0, 0);

	DirLight_Default.Type = D3DLIGHT_DIRECTIONAL;
	DirLight_Default.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	DirLight_Default.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	DirLight_Default.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	DirLight_Default.Direction = D3DXVECTOR3(1, 0, 0);


	SpotLight.Type = D3DLIGHT_SPOT;
	SpotLight.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	SpotLight.Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	SpotLight.Specular = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	SpotLight.Position = D3DXVECTOR3(2.0f, 10.0f, 2.0f);
	SpotLight.Direction = D3DXVECTOR3(0, -1.0f, 0);
	SpotLight.Range = 25.0f;
	SpotLight.Falloff = 1.0f;
	SpotLight.Attenuation0 = 0.001f;
	SpotLight.Attenuation1 = 0.001f;
	SpotLight.Attenuation2 = 0.001f;
	SpotLight.Theta = D3DX_PI / 6;
	SpotLight.Phi = D3DX_PI / 2;


	PointLight.Type = D3DLIGHT_POINT;
	PointLight.Diffuse = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Ambient = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Specular = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Position = D3DXVECTOR3(0.0f, 7.0f, -5.0f);
	PointLight.Range = 20.0f;
	PointLight.Attenuation0 = 0.001f;
	PointLight.Attenuation1 = 0.001f;
	PointLight.Attenuation2 = 0.001f;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MBUTTONDOWN:
		m_isMButtonDown = true;
		break;
	case WM_MBUTTONUP:
		m_isMButtonDown = false;
		break;
	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);

			double fDeltaX = (double)ptCurMouse.x - m_ptPrevMouse.x;
			double fDeltaY = (double)ptCurMouse.y - m_ptPrevMouse.y;

			// x �� �̵��� (ȭ�� ��ǥ�� �¿�) -> 3D ��ǥ���� Y�� �̵��ӿ� ����
			// 1:1 ���� ��Ű�� ȸ�� ���� �ſ� Ŀ���Ƿ�, ���� ������ �����ش�.
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);

			m_ptPrevMouse = ptCurMouse;

			m_pCamera->SetCameraRotationAngle(m_vCamRotAngle);
		}
		
		if (m_isMButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.y = HIWORD(lParam);
			double fDeltaY = (double)ptCurMouse.y - m_ptPrevMouse.y;

			// y�� �̵����� ����Ͽ� ī�޶� �� �Ǵ� �Ʒ��� �̵���Ų��.
			m_fCamTransY += m_pCamera->GetCamPos().y + fDeltaY / 100.0f ;
			
			m_ptPrevMouse = ptCurMouse;

			m_pCamera->SetCameraPosY(m_fCamTransY);

		}
		break;
	case WM_RBUTTONDOWN:
	{
//		if (m_pFrustum)
//			m_pFrustum->Update(m_pCamera->GetCamPos());
		
		if (m_pSkinnedMesh)
		{
			static int aidx = 1;
			static float checker = 0.0f;
			checker = m_pSkinnedMesh->GetCurAnimPosRate();
			printf("%.2f ", checker);
			if (checker > BLENDING_START_PLAY_RATE)
			{
				switch (m_pSkinnedMesh->SetAnimationIndexBlend(aidx))
				{
				case 1:
					if (++aidx >= 5)
						aidx = 0;

					printf(" new aidx : #%d\n", aidx);
					checker = 0.0f;
					break;
				case 99:
					aidx--;
					break;
				}
			}
		}
		
	}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 90.0f);
/*
		if (m_fCameraDistance < EPSILON)
			m_fCameraDistance = EPSILON;*/

		// ī�޶� Ŭ������ ī�޶� �Ÿ����� �Ѱ��ش�.
		m_pCamera->SetCameraDistance(m_fCameraDistance);
		break;	

		case WM_KEYDOWN:
			switch (wParam)
			{
				
				case VK_SPACE:
				{
					if (m_pBoxman)
					{
						if (m_isJumping)
							break;
						else
						{
							m_isJumping = true;
							m_isJumping_Top = false;
							m_pBoxman->SetjumpState(true, false);
						}
					}
				}
					break;
				case 'C':
					if (m_isCamFollow)
					m_isCamFollow = false;
					else
					m_isCamFollow = true;

					m_pCamera->ChangeCameraMode(m_isCamFollow);
					break;				
			case 'L':
				if (m_swDirLight)
					m_swDirLight = false;
				else
					m_swDirLight = true;
				break;
			case 'P':
				if (m_swSpotLight)
					m_swSpotLight = false;
				else
					m_swSpotLight = true;
				break;
			}
			
	}
}

void cMainGame::Create_Font()
{
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		
		// �ý��� ��Ʈ�� ��� �� ���
		//strcpy_s(fd.FaceName, "����ü");

		AddFontResource("font/umberto.ttf");
		strcpy_s(fd.FaceName, "umberto.ttf");

		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont_a);
	}

	{
		//3D ��Ʈ
		HDC hdc = CreateCompatibleDC(0);
		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = 25;
		lf.lfWidth = 12;
		lf.lfWeight = 500;
		lf.lfItalic = false;
		lf.lfUnderline = false;
		lf.lfStrikeOut = false;
		strcpy(lf.lfFaceName, "����ü");

		HFONT hFont;
		HFONT hFontOld;
		hFont = CreateFontIndirect(&lf);
		hFontOld = (HFONT)SelectObject(hdc, hFont);
		D3DXCreateText(g_pD3DDevice, hdc, _T("DX9 �ѱ�"), 0.001f, 0.01f, &m_p3DText, 0, 0);

		SelectObject(hdc, hFontOld);
		DeleteObject(hFont);
		DeleteDC(hdc);
	}


}

void cMainGame::Render_Text()
{
	string sText("Sample Text");
	RECT rc;
	SetRect(&rc, 100, 100, 101, 101);
	m_pFont_a->DrawTextA(NULL, sText.c_str(), sText.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));

	{
		//3D �ؽ�Ʈ
		D3DXMATRIXA16 matWorld, matS, matR, matT;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 15.0f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
		D3DXMatrixTranslation(&matT, -2.0f, 2.0f, 0.0f);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_p3DText->DrawSubset(0);
	}

	LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_QUEST);	

	RECT rc2;
	string string2("����Ʈ");

	SetRect(&rc2, 100, 200, 101, 101);
	pFont->DrawTextW(NULL, (LPCWSTR)string2.c_str(), lstrlen(string2.c_str()), &rc2, DT_LEFT, D3DCOLOR_XRGB(255, 0, 255));

}

void cMainGame::Setup_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	// m_pTextureUI = g_pTextureManager->GetTexture("UI/������.jpg");
	// D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/������.jpg", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, D3DCOLOR_XRGB(128,128,128), &m_stImage_info, NULL, &m_pTextureUI);

	{
		cUIImageView* pImageView = new cUIImageView;
		pImageView->SetPosition(0, 0, 0);
		pImageView->SetTexture("./UI/panel-info.png");
		m_pUIRoot = pImageView;

		cUITextView* pTextView = new cUITextView;
		pTextView->SetText("���� �ؽ�Ʈ!!!");
		pTextView->Setsize(ST_SIZE_N(380, 300));
		pTextView->SetPosition(70, 80);
		pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
		pTextView->SetTag(E_TEXT_VIEW);
		m_pUIRoot->AddChild(pTextView);

		cUIButton* pButtonOK = new cUIButton;
		pButtonOK->SetTexture("./UI/btn-med-up.png", "./UI/btn-med-over.png", "./UI/btn-med-down.png", "OK");
		pButtonOK->SetPosition(100,275);
		pButtonOK->SetDelegate(this);
		pButtonOK->SetTag(E_BUTTON_OK);
		m_pUIRoot->AddChild(pButtonOK);

		/*cUIButton* pButtonCancel = new cUIButton;
		pButtonCancel->SetTexture("./UI/btn-med-up.png", "./UI/btn-med-over.png", "./UI/btn-med-down.png", "Cancel");
		pButtonCancel->SetPosition(150, 200);
		pButtonCancel->SetDelegate(this);
		pButtonCancel->SetTag(E_BUTTON_CANCEL);
		m_pUIRoot->AddChild(pButtonCancel);

		cUIButton* pButtonExit= new cUIButton;
		pButtonExit->SetTexture("./UI/btn-main-menu.png","./UI/btn-main-menu.png", "./UI/btn-main-menu.png");
		pButtonExit->SetPosition(200, 0);
		pButtonExit->SetDelegate(this);
		pButtonExit->SetTag(E_BUTTON_EXIT);
		m_pUIRoot->AddChild(pButtonExit);*/

	}

}

void cMainGame::Render_UI()
{
	/*
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matT, matR, matS, matWorld;
	D3DXMatrixTranslation(&matT, m_stImage_info.Width / 2, m_stImage_info.Height / 2, 0);
	static float fAngle = 0.0f;
	fAngle += 0.01f;
	D3DXMatrixRotationZ(&matR, fAngle);
	matWorld = matR * matT;
	
	m_pSprite->SetTransform(&matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stImage_info.Width, m_stImage_info.Height);
	m_pSprite->Draw(m_pTextureUI, &rc, &D3DXVECTOR3(m_stImage_info.Width/2, m_stImage_info.Height/2, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(247, 246, 251, 255));
	m_pSprite->End();
	*/

	if (m_pUIRoot)
		m_pUIRoot->Render(m_pSprite);
}

void cMainGame::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUIRoot->FindChildByTag(E_TEXT_VIEW);

	switch (pSender->GetTag())
	{
	case E_BUTTON_OK:
		pTextView->SetText("OK��ư ������!");
		break;
	case E_BUTTON_CANCEL:
		pTextView->SetText("��! ���� ��ȸ��......");
		break;
	case E_BUTTON_EXIT:
		m_pUIRoot->m_isHidden = true;
		break;
	}
}

void cMainGame::Setup_Multitexture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice,	"./MultiTextures/Albedo00.jpg", &m_pTex0);
	D3DXCreateTextureFromFile(g_pD3DDevice,	"./MultiTextures/FieldStone_DM.TGA", &m_pTex1);
	D3DXCreateTextureFromFile(g_pD3DDevice, "./MultiTextures/alpha_tex.tga", &m_pTex2);
	ST_PT_VERTEX v;
	
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(0, 0);
	m_vecTexMulti.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(0, 1);
	m_vecTexMulti.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(1, 1);
	m_vecTexMulti.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(0, 0);
	m_vecTexMulti.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(1, 1);
	m_vecTexMulti.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	v.texture1 = D3DXVECTOR2(0, 1);
	m_vecTexMulti.push_back(v);

}		    

void cMainGame::Render_Multitexture()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);	
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);


	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


	g_pD3DDevice->SetTexture(0, NULL);

	g_pD3DDevice->SetTexture(1, NULL);
	{
		g_pD3DDevice->SetTexture(0, m_pTex2);

		D3DXMATRIXA16		matS;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 0.5f, 1.0f, 1.0f);

		matWorld *= matS;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	}


	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTexMulti.size() / 3, &m_vecTexMulti[0], sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetTexture(2, NULL);


}
