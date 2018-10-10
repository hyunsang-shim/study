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
{
	g_pDeviceManager;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}

cMainGame::~cMainGame()
{	
	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
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

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup() 
{
	srand(time(NULL));

	//m_pCubePC = new cCubePC;
	//m_pCubePC->Setup();

	m_pMap = new cMap;
	m_pMap->Setup();	
	

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	InitMaterial();
	InitLights();


	/*m_pHexagon = new cHexagon;
	m_pHexagon->Setup();
	m_vWaypoints = m_pHexagon->GetPoints();*/

	
	//for (int i = 0; i < 6; i++)
	//{
	//	if (i % 2 == 0)
	//	{
	//		// 일반 경로를 따라가는 박스맨 저장소에 넣을 박스맨들을 생성 & 넣는다.
	//		BESIER_BOXMAN normalboxman;
	//		normalboxman.boxman = new cBoxman;
	//		normalboxman.boxman->Setup(_T("D.VA.png"));
	//		normalboxman.m_vBoxPosition.x = m_vWaypoints[i].x;
	//		normalboxman.m_vBoxPosition.y = m_vWaypoints[i].y;
	//		normalboxman.m_vBoxPosition.z = m_vWaypoints[i].z;
	//		m_vecNormalBoxman.push_back(normalboxman);
	//	}
	//	else
	//	{
	//		// 베지어 경로를 따라가는 박스맨 저장소에 넣을 박스맨들을 생성 & 넣는다.
	//		BESIER_BOXMAN besierboxman;
	//		besierboxman.boxman = new cBoxman;
	//		besierboxman.boxman->Setup(_T("Megumin.png"));
	//		besierboxman.m_vBoxPosition.x = m_vWaypoints[i].x;
	//		besierboxman.m_vBoxPosition.y = m_vWaypoints[i].y;
	//		besierboxman.m_vBoxPosition.z = m_vWaypoints[i].z;
	//		m_vecBesierBoxman.push_back(besierboxman);
	//
	//	}
	//	}
	

	// 스킨 제작자 주소 표시
	m_pFont = NULL;
	HRESULT hr = D3DXCreateFont(g_pD3DDevice, 20, 10, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, _T("Consolas"), &m_pFont);

	message = "D.VA 스킨 출처 : https://blog.naver.com/netkama26/220746453079\n";
	message += "조작:\nW - 앞으로\t S - 뒤로\n";
	message += "A - 왼쪽으로 회전 \t D - 오른쪽으로 회전\n";
	message += "Space Bar - 점프 \tShift - 달리기\n";
	message += "C - 카메라 모드 토글(고정 카메라 <= > TPS 카메라)\n";
	message += "L - 방향성 광원 토글(켜기 <= > 끄기)";

	if (!SUCCEEDED(hr))
	{
		TCHAR tmp[128] = { _T("Can not Create and/or Initialize Font. Requested font face name : Consolas") };
	
		MessageBox(g_hWnd, _T("Error : Creating Font Failed"), tmp, MB_OK);
		return;
	}

	GetClientRect(g_hWnd, &m_RectTxtArea);

	//m_pCubeman = new cCubeman;
	//m_pCubeman->Setup();
}

void cMainGame::Update(){
	

	//박스의 회전
	if (GetKeyState('A') & 0x8000)
	{
		m_isRotating = true;
		m_fBoxRotY -= 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_isRotating = true;
		m_fBoxRotY += 0.1f;
	}
	else 
		m_isRotating = false;
	
	// 박스의 이동
	
//	double fMin = m_pGrid->GetGridMinMax().left;
//	double fMax = m_pGrid->GetGridMinMax().right;

	if (GetKeyState('W') & 0x8000)
	{
		m_isMoving = true;
		if (GetKeyState(VK_SHIFT) & 0x8000)
		{
			/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
				m_vvecBoxPosition[i] = m_vvecBoxPosition[i] + (m_vBoxDirection * -0.18f);
				m_isRunning = true;*/
			m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * -0.18f);
			m_isRunning = true;
		}
		else
		{
			/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
				m_vvecBoxPosition[i] = m_vvecBoxPosition[i] + (m_vBoxDirection * -0.1f);
			m_isRunning = false;*/
			m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * -0.1f);
			m_isRunning = false;

		}
		
		// 캐릭터가 그리드 밖으로 못나가도록 범위를 지정한다.
		/*
		for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			if (m_vvecBoxPosition[i].x >= fMax)
				m_vvecBoxPosition[i].x = fMax;
			else if (m_vvecBoxPosition[i].x <= fMin)
				m_vvecBoxPosition[i].x = fMin;

			if (m_vvecBoxPosition[i].z >= fMax)
				m_vvecBoxPosition[i].z = fMax;
			else if (m_vvecBoxPosition[i].z <= fMin)
				m_vvecBoxPosition[i].z = fMin;
		}
		if (m_vBoxPosition.x >= fMax)
			m_vBoxPosition.x = fMax;
		else if (m_vBoxPosition.x <= fMin)
			m_vBoxPosition.x = fMin;

		if (m_vBoxPosition.z >= fMax)
			m_vBoxPosition.z = fMax;
		else if (m_vBoxPosition.z <= fMin)
			m_vBoxPosition.z = fMin;
			*/

	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_isMoving = true;		
		if (GetKeyState(VK_SHIFT) & 0x8000)
		{
			/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
			{
				m_vvecBoxPosition[i] = m_vvecBoxPosition[i] + (m_vBoxDirection * 0.18f);
				m_isRunning = true;
			}*/
			m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.18f);
			m_isRunning = true;
		}
		else
		{
			/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
			{
				m_vvecBoxPosition[i] = m_vvecBoxPosition[i] + (m_vBoxDirection * 0.1f);
				m_isRunning = false;
			}*/
			m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.1f);
			m_isRunning = false;
		}

		/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			if (m_vvecBoxPosition[i].x >= fMax)
				m_vvecBoxPosition[i].x = fMax;
			else if (m_vvecBoxPosition[i].x <= fMin)
				m_vvecBoxPosition[i].x = fMin;

			if (m_vvecBoxPosition[i].z >= fMax)
				m_vvecBoxPosition[i].z = fMax;
			else if (m_vvecBoxPosition[i].z <= fMin)
				m_vvecBoxPosition[i].z = fMin;
		}*/
/*
		if (m_vBoxPosition.x >= fMax)
			m_vBoxPosition.x = fMax;
		else if (m_vBoxPosition.x <= fMin)
			m_vBoxPosition.x = fMin;

		if (m_vBoxPosition.z >= fMax)
			m_vBoxPosition.z = fMax;
		else if (m_vBoxPosition.z <= fMin)
			m_vBoxPosition.z = fMin;*/
	}
	else
		m_isMoving = false;
		
	// 박스의 점프
	/*
	if (m_isJumping && !m_isJumping_Top)
	{
		for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			if (m_vvecBoxPosition[i].y < 1.0 + EPSILON)
				m_vvecBoxPosition[i].y += 0.125f;
			else
			{
				m_isJumping_Top = true;
			}
		}
	}
	else if (m_isJumping && m_isJumping_Top)
	{
		for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			if (m_vvecBoxPosition[i].y >= 0.0f + EPSILON)
				m_vvecBoxPosition[i].y -= 0.125f;
			else
			{
				m_vvecBoxPosition[i].y = 0.0000000f;
				m_isJumping = false;
				m_isJumping_Top = false;
			}
		}
	}
	*/

	// 캐릭터에 이동 상태를 전달한다.		
	/*
	for (int i = 0; i < m_vvecBoxPosition.size(); i++)
	{
		m_vpBoxman[i]->SetMoveState(m_isMoving | m_isRotating, m_isRunning);
		m_vpBoxman[i]->SetjumpState(m_isJumping, m_isJumping_Top);
	}
	*/

	// 캐릭터(Boxmax)의 루트 역할을 하는 박스.	
	if (m_pCubePC)
	{
		D3DXMATRIXA16 matRotY;
		D3DXMatrixIdentity(&matRotY);
		D3DXMatrixRotationY(&matRotY, m_fBoxRotY);
		m_vBoxDirection = D3DXVECTOR3(0, 0, 1.0f);
		D3DXVec3TransformNormal(&m_vBoxDirection, &m_vBoxDirection, &matRotY);		
		m_pCubePC->SetBoxScale(0.01f);					// 테스트용으로 만든 것이 10짜리니까 0.1로 
		m_pCubePC->SetBoxRotationY(m_fBoxRotY);
		//printf("cMainGame : %f\t", m_fBoxRotY);
		m_pCubePC->SetBoxPosition(m_vBoxPosition);		
		/*for (int i = 0; i < m_vvecBoxPosition.size(); i++)
		{
			m_pCubePC->SetBoxPosition(m_vvecBoxPosition[i]);
		}*/
		m_pCubePC->Update();
	}

	//베지어 곡선 경로 boxman 업데이트
	/*for (int i = 0; i < 1; i++)
	{
		m_vecBesierBoxman[i].boxman->SetRootScale(m_fBoxScale);
		m_vecBesierBoxman[i].boxman->Update();
	}*/

// 일반 경로 boxman 업데이트
	/*for (int i = 0; i <1; i++)
	{
		m_vecNormalBoxman[i].boxman->SetRootScale(m_fBoxScale);
		m_vecNormalBoxman[i].boxman->Update();
	}*/
	

	//카메라 업데이트
	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);
		m_pCamera->Update();
	}


	// 박스의 스케일 조정 (파일 읽기 적용 시
	


	// 강사님 캐릭터 그리기
	/*
	if (m_pCubeman)
		m_pCubeman->Update();
	*/
}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);
	g_pD3DDevice->BeginScene();


	// Draw Something
	m_pGrid->Render();
	m_pMap->Render();
	//m_pHexagon->Render();	
	
	//베지어 곡선 경로 boxman 그리기
	for (int i = 0; i < 1; i++)
	{
		//m_vecBesierBoxman[i].boxman->Render();
	}

	// 일반 경로 boxman 그리기
	for (int i = 0; i <1; i++)
	{
		//m_vecNormalBoxman[i].boxman->Render();
	}


	//g_pD3DDevice->SetMaterial(&m_matWhite);  // 파일에서 불러온 매터리얼 확인을 위해 주석처리 함
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
	m_pMap->Render();

	if (m_pFont)
	{
		m_pFont->DrawTextA(NULL, message.c_str(), -1, &m_RectTxtArea, DT_LEFT, D3DCOLOR_XRGB(200, 200, 200));
	}

	// 강사님 추상화 클래스 방식
	/* 
	if (m_pCubeman)
		m_pCubeman->Render();
	
	 sample code
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
			m_fCamTransY += m_pCamera->GetCamPosY().y + fDeltaY / 100.0f ;
			
			m_ptPrevMouse = ptCurMouse;

			m_pCamera->SetCameraPosY(m_fCamTransY);

		}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);

		if (m_fCameraDistance < EPSILON)
			m_fCameraDistance = EPSILON;

		// 카메라 클래스에 카메라 거리값을 넘겨준다.
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
