#pragma once
#include "stdafx.h"
#include "cMainGame.h"

class cCubePC;
class cCamera;
class cGrid;

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_vEye(0, 0, -5)
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


	SetGrid();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update(){


	//�ڽ��� ȸ��
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}



	// �ڽ��� �̵�

	if (GetKeyState('W') & 0x8000)
	{
		m_vBoxPosition = m_vBoxPosition + (m_vBoxDirection * 0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vBoxPosition = m_vBoxPosition - (m_vBoxDirection * 0.1f);
	}



	//�ڽ��� ������
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
	m_pCubePC->Render();	

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::SetGrid()
{
	

}

void cMainGame::DrawGrid()
{
	

	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecIndVertex.size() / 3, &m_vecIndVertex[0], sizeof(ST_PC_VERTEX));
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

			// x �� �̵��� (ȭ�� ��ǥ�� �¿�) -> 3D ��ǥ���� Y�� �̵��ӿ� ����
			// 1:1 ���� ��Ű�� ȸ�� ���� �ſ� Ŀ���Ƿ�, ���� ������ �����ش�.
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

		// ī�޶� Ŭ������ ī�޶� �Ÿ����� �Ѱ��ش�.
		m_pCamera->SetCameraDistance(m_fCameraDistance);

		break;		
	}
}
