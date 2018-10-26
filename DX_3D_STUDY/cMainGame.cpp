#pragma once
#include "stdafx.h"
#include "cMainGame.h"
#include "cSkinnedMesh.h"
#include "cZealot.h"
#include "cOBB.h"

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
	, m_pLoadFromX(NULL)			// x 파일 불러오기
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
	, m_pRootFrame(NULL)		// 강사님 ASE 로더
	, m_pSkinnedMesh(NULL)
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

	// 강사님 ASE 로더
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
}


void cMainGame::Setup() 
{
	srand(time(NULL));

	/*m_pASE_Char = new cASE_Char;
	m_pASE_Char->Setup();*/

	// 메시 렌더링 예제
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

	//m_pBoxman = new cBoxman;
	//m_pBoxman->Setup(_T("D.VA.png"));
		
	//m_pMap = new cMap;
	//m_pMap->Setup();

	//m_pHeightmap = new cHeightMap;
	//m_pHeightmap->Setup("HeightMap/HeightMap.raw");

	// 강사님 ASE로더
	//cASELoader_inst loader;
	//m_pRootFrame = loader.Load("woman/woman_01_all.ASE");

	{
		m_pLoadFromX = new cLoadXFile;
		m_pLoadFromX->Setup("Xfile/bigship1.x");
	}

	// Skinned Mesh Setup
	{
		//m_pSkinnedMesh = new cSkinnedMesh;
		//m_pSkinnedMesh->Setup("Zealot", "zealot.X");
	}

	{
//		m_pFrustum = new cFrustumCulling;
//		m_pFrustum->Setup();
	}

	// OBB 충돌 판정 예제
	{
		m_pHoldZealot = new cZealot;
		m_pHoldZealot->Setup();
		

		m_pMoveZealot = new cZealot;
		m_pMoveZealot->Setup();
		cCharacter* pCharacter = new cCharacter;
		m_pMoveZealot->SetCharacterController(pCharacter);
		SAFE_RELEASE(pCharacter);
	}

}

void cMainGame::Update(){
	


	// 캐릭터(Boxmax)의 루트 역할을 하는 박스.	
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

		//
		// Boxman 이동 관련 처리
		//
		//박스의 회전
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

		// 박스의 이동
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

			// 캐릭터가 그리드 밖으로 못나가도록 범위를 지정한다.
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

		// 박스의 점프

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

		// 캐릭터에 이동 상태를 전달한다.		
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

	//카메라 업데이트
	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);
		m_pCamera->Update();
	}

	// map update
	if (m_pMap)
		m_pMap->Update();

	if (m_pBoxman)
		m_pBoxman->Update();

	// 강사님 캐릭터 그리기
	/*
	if (m_pCubeman)
		m_pCubeman->Update();
	*/

	// 강사님 ASE로더
	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);

//	if (m_pSkinnedMesh)
//		m_pSkinnedMesh->Update();

	// OBB 충돌 판정 예제
	{
		if (m_pHoldZealot)
			m_pHoldZealot->Update();

		if (m_pMoveZealot)
			m_pMoveZealot->Update();
	}

}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);
	g_pD3DDevice->BeginScene();
		

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);



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

	// 강사님 추상화 클래스 방식
	/* 
	if (m_pCubeman)
		m_pCubeman->Render();
	
	// sample code
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16	matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetTexture(0, m_pTexture);	// 텍스쳐 사용 선언
		g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

		g_pD3DDevice->SetTexture(0, NULL);	// 텍스쳐 사용 하지 않음 선언
	}
	*/
	// Draw and Set Lights
	{
		g_pD3DDevice->SetMaterial(&m_matWhite);  // 파일에서 불러온 매터리얼 확인을 위해 주석처리 함
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

	}



	if (m_pCubePC)
		m_pCubePC->Render();

	if (m_pMap)
		m_pMap->Render();

	if (m_pHexagon)
		m_pHexagon->Render();

	if (m_pBoxman)
		m_pBoxman->Render();

	g_pD3DDevice->SetMaterial(&m_matWhite);

	if (m_pASE_Char)
		m_pASE_Char->Render();


	if (m_pRootFrame)
		m_pRootFrame->Render();

	// 메시 렌더링 예제
	//Mesh_Render();

	//if (m_pHeightmap)
	//	m_pHeightmap->Render();

	if (m_pLoadFromX)
		m_pLoadFromX->Render();

	// OBB 충돌 판정 예제
	{
		D3DCOLOR c = cOBB::IsCollision(m_pHoldZealot->GetOBB(),	m_pMoveZealot->GetOBB()) ? D3DCOLOR_XRGB(200, 0, 0) : D3DCOLOR_XRGB(128, 128, 128);

		if (m_pHoldZealot)
			m_pHoldZealot->Render(c);

		if (m_pMoveZealot)
			m_pMoveZealot->Render(c);

	}



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

			// x 축 이동량 (화면 좌표상 좌우) -> 3D 좌표상의 Y축 이동임에 주의
			// 1:1 대응 시키면 회전 값이 매우 커지므로, 값을 적당히 나눠준다.
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

			// y축 이동량에 기반하여 카메라를 위 또는 아래로 이동시킨다.
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

		// 카메라 클래스에 카메라 거리값을 넘겨준다.
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
