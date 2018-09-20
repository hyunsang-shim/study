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
	, m_vecOriginalBox(NULL)
	, m_vEye(3, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vBoxPosition(0, 0, 0)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fBoxRotY(0.0f)
	, m_vBoxDirection(0, 0, 1)
	, m_fBoxScale(1.0f)

{
	g_pDeviceManager;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}


cMainGame::~cMainGame()
{	
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
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
	m_vecOriginalBox = m_pCubePC->GetOriginVertexList();
	m_pBoxman->Setup();


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update(){


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
		m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vBoxPosition = m_vBoxPosition - (m_vBoxDirection * 0.1f);
	}



	//박스의 스케일
	if (GetKeyState('Z') & 0x8000)
	{
		m_fBoxScale += 0.1f;
		if (m_fBoxScale > 2.0f)
			m_fBoxScale = 2.0f;
	}

	if (GetKeyState('X') & 0x8000)
	{

		m_fBoxScale -= 0.1f;
		if (m_fBoxScale < 0.2f)
			m_fBoxScale = 0.2f;
	}


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

		m_pBoxman->SetRootDirection(vBoxmanRootDirection);

		m_pBoxman->SetRootRotationY(m_fBoxRotY);


	}

	if (m_pCamera)
	{
		m_pCamera->SetBoxPosition(m_vBoxPosition);

		m_pCamera->Update();
	}

	
}

void cMainGame::Render()
{	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET + D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(64,64,64), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	// Draw Sonething
	m_pGrid->Render();
	//m_pCubePC->Render();	
	m_pBoxman->Render();

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
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);

		if (m_fCameraDistance < EPSILON)
			m_fCameraDistance = EPSILON;

		// 카메라 클래스에 카메라 거리값을 넘겨준다.
		m_pCamera->SetCameraDistance(m_fCameraDistance);

		break;		
	}
}
