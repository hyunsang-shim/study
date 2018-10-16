#pragma once
#include "stdafx.h"
#include "cMainGame.h"

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
	//	, m_pCubeman(NULL)
	, m_vEye(3, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vBoxPosition(0,0,-1)
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
{
	g_pDeviceManager;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pTexture);

	
	SAFE_DELETE(m_pHexagon);
	SAFE_DELETE(m_pASE_Char);

	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pMap);
	//SAFE_DELETE(m_pCubeman);

	if (m_vecBesierBoxman.size() >= 1)
	{
		for (int i = 0; i < m_vecBesierBoxman.size(); i++)
			SAFE_DELETE(m_vecBesierBoxman[i].boxman);
	}

	if (m_vecNormalBoxman.size() >= 1)
	{
		for (int i = 0; i < m_vecNormalBoxman.size(); i++)
			SAFE_DELETE(m_vecNormalBoxman[i].boxman);
	}

	// ����� ASE �δ�
	m_pRootFrame->Destroy();	
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();



	g_pDeviceManager->Destroy();
}

void cMainGame::Setup() 
{
	srand(time(NULL));

	/*m_pASE_Char = new cASE_Char;
	m_pASE_Char->Setup();*/

	
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	InitMaterial();
	InitLights();
	
	GetClientRect(g_hWnd, &m_RectTxtArea);


	// ����� ASE�δ�
	cAseLoader_inst loader;
	m_pRootFrame = loader.Load("woman/woman_01_all.ASE");

}

void cMainGame::Update(){
	


	// ĳ����(Boxmax)�� ��Ʈ ������ �ϴ� �ڽ�.	
	if (m_pCubePC)
	{
		D3DXMATRIXA16 matRotY;
		D3DXMatrixIdentity(&matRotY);
		D3DXMatrixRotationY(&matRotY, m_fBoxRotY);
		m_vBoxDirection = D3DXVECTOR3(0, 0, 1.0f);
		D3DXVec3TransformNormal(&m_vBoxDirection, &m_vBoxDirection, &matRotY);		
		m_pCubePC->SetBoxScale(1.0f);
		m_pCubePC->SetBoxRotationY(m_fBoxRotY);
		//printf("cMainGame : %f\t", m_fBoxRotY);
		m_pCubePC->SetBoxPosition(m_vBoxPosition);		
		/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			m_pCubePC->SetBoxPosition(m_vvecBoxPosition[i]);
		}*/
		m_pCubePC->Update();
	}

	//ī�޶� ������Ʈ
	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);
		m_pCamera->Update();
	}


	// map update
	if (m_pMap)
		m_pMap->Update();


	// ����� ĳ���� �׸���
	/*
	if (m_pCubeman)
		m_pCubeman->Update();
	*/

	// ����� ASE�δ�
	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);
}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);
	g_pD3DDevice->BeginScene();


	// Draw Something
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pMap)
		m_pMap->Render();

	if (m_pHexagon)
		m_pHexagon->Render();	

	if (m_pCubePC)
		m_pCubePC->Render();

	g_pD3DDevice->SetMaterial(&m_matWhite);

	if (m_pASE_Char)
		m_pASE_Char->Render();
	

	if (m_pRootFrame)
		m_pRootFrame->Render();
		
	
	//������ � ��� boxman �׸���
	for (int i = 0; i < 1; i++)
	{
		//m_vecBesierBoxman[i].boxman->Render();
	}

	// �Ϲ� ��� boxman �׸���
	for (int i = 0; i <1; i++)
	{
		//m_vecNormalBoxman[i].boxman->Render();
	}


	//g_pD3DDevice->SetMaterial(&m_matWhite);  // ���Ͽ��� �ҷ��� ���͸��� Ȯ���� ���� �ּ�ó�� ��
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


	//m_pBoxman->Render();
	//m_pCubePC->Render();

	//if (m_pFont)
	//{
	//	m_pFont->DrawTextA(NULL, message.c_str(), -1, &m_RectTxtArea, DT_LEFT, D3DCOLOR_XRGB(200, 200, 200));
	//}

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

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

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
	SpotLight.Position = D3DXVECTOR3(2.0f, 25.0f, 2.0f);
	SpotLight.Direction = D3DXVECTOR3(0, -1.0f, 0);
	SpotLight.Range = 25.0f;
	SpotLight.Falloff = 1.0f;
	SpotLight.Attenuation0 = 0.001f;
	SpotLight.Attenuation1 = 0.001f;
	SpotLight.Attenuation2 = 0.001f;
	SpotLight.Theta = D3DX_PI / 4;
	SpotLight.Phi = D3DX_PI / 2;


	PointLight.Type = D3DLIGHT_POINT;
	PointLight.Diffuse = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Ambient = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Specular = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
	PointLight.Position = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	PointLight.Range = 15.0f;
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
			m_fCamTransY += m_pCamera->GetCamPosY().y + fDeltaY / 100.0f ;
			
			m_ptPrevMouse = ptCurMouse;

			m_pCamera->SetCameraPosY(m_fCamTransY);

		}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);

		if (m_fCameraDistance < EPSILON)
			m_fCameraDistance = EPSILON;

		// ī�޶� Ŭ������ ī�޶� �Ÿ����� �Ѱ��ش�.
		m_pCamera->SetCameraDistance(m_fCameraDistance);
		break;	

		case WM_KEYDOWN:
			switch (wParam)
			{
				/*
								case VK_SPACE:
									if (m_isJumping)
										break;
									else
									{
										m_isJumping = true;
										m_isJumping_Top = false;
										m_pBoxman->SetjumpState(true, false);
									}
									break;
								case 'C':
									if (m_isCamFollow)
									m_isCamFollow = false;
									else
									m_isCamFollow = true;

									m_pCamera->ChangeCameraMode(m_isCamFollow);
									break;
				*/
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
