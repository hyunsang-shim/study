#pragma once
#include "stdafx.h"
#include "cMainGame.h"

class cCubePC;
class cBoxman;
class cCamera;
class cGrid;

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pTexture(NULL)
	, m_vecOriginalBox(NULL)
	//	, m_pCubeman(NULL)
	, m_vEye(3, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vBoxPosition(0, 0, 0)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_isMButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fCamTransY(0)
	, m_fBoxRotY(0.0f)
	, m_vBoxDirection(0, 0, -1)
	, m_fBoxScale(1.0f)
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
	SAFE_DELETE(m_pBoxman)
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup() 
{
	srand(time(NULL));

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pBoxman = new cBoxman;	
	m_pBoxman->Setup();

	// 스킨 제작자 주소 표시
	m_pFont = NULL;
	HRESULT hr = D3DXCreateFont(g_pD3DDevice, 20, 10, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, _T("Consolas"), &m_pFont);

	message = "D.VA 스킨 출처 : https://blog.naver.com/netkama26/220746453079\n조작:\nW - 앞으로\t S - 뒤로\nA - 왼쪽으로 회전 \t D - 오른쪽으로 회전\nSpace Bar - 점프 \tShift - 달리기\nC - 카메라 모드 토글(고정 카메라 <=> TPS 카메라 )";
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
	m_pBoxman->SetMoveState(m_isMoving | m_isRotating, m_isRunning);
	m_pBoxman->SetjumpState(m_isJumping, m_isJumping_Top);



	if (m_pCubePC)
	{
		D3DXMATRIXA16 matRotY;
		D3DXMatrixIdentity(&matRotY);
		D3DXMatrixRotationY(&matRotY, m_fBoxRotY);
		m_vBoxDirection = D3DXVECTOR3(0, 0, 1.0f);
		D3DXVec3TransformNormal(&m_vBoxDirection, &m_vBoxDirection, &matRotY);
		m_pCubePC->SetBoxScale(m_fBoxScale);
		m_pCubePC->SetBoxRotationY(m_fBoxRotY);
		m_pCubePC->SetBoxPosition(m_vBoxPosition);

		m_pCubePC->Update();
	}

	if (m_pBoxman)
	{
		m_pBoxman->SetRootPosition(m_vBoxPosition);


		D3DXMATRIXA16 matRotY;
		D3DXVECTOR3 vBoxmanRootDirection(0, 0, 1.0f);
		D3DXMatrixIdentity(&matRotY);
		D3DXMatrixRotationY(&matRotY, m_fBoxRotY);				
		D3DXVec3TransformNormal(&vBoxmanRootDirection, &vBoxmanRootDirection, &matRotY);

		m_pBoxman->SetRootScale(m_fBoxScale);
		m_pBoxman->SetRootRotationY(m_fBoxRotY);
		m_pBoxman->SetRootPosition(m_vBoxPosition);
		m_pBoxman->SetRootDirection(vBoxmanRootDirection);

		m_pBoxman->Update();

	}

	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);
		m_pCamera->Update();
	}

	/*if (m_pCubeman)
		m_pCubeman->Update();	*/
}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	// Draw Something
	m_pGrid->Render();
	//m_pCubePC->Render();	
	m_pBoxman->Render();
	

	if (m_pFont)
	{
		m_pFont->DrawTextA(NULL, message.c_str(), -1, &m_RectTxtArea, DT_LEFT, D3DCOLOR_XRGB(200, 200, 200));
			//DrawTextW(NULL, LPCSTR(message.c_str()), lstrlen(message), &m_RectTxtArea, DT_LEFT, D3DCOLOR_XRGB(128, 128, 128));
	}
	/* 강사님 추상화 클래스 방식
	if (m_pCubeman)
		m_pCubeman->Render();*/
	
	// sample code
	//{
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//	D3DXMATRIXA16	matWorld;
	//	D3DXMatrixIdentity(&matWorld);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//	g_pD3DDevice->SetTexture(0, m_pTexture);	// 텍스쳐 사용 선언
	//	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

	//	g_pD3DDevice->SetTexture(0, NULL);	// 텍스쳐 사용 하지 않음 선언
	//}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

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
		}
		break;
	
	}
}
