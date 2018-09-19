#pragma once
#include "stdafx.h"
#include "cMainGame.h"

class cCubePC;
class cCamera;

cMainGame::cMainGame()
	: m_pCubePC(NULL),
	m_vEye(0, 0, -5),
	m_vLookAt(0, 0, 0),
	m_vUp(0, 1, 0),
	m_vBoxPosition(0, 0, 0),
	m_fCameraDistance(5.0f),
	m_isLButtonDown(false),
	m_vCamRotAngle(0, 0, 0),
	m_fBoxRotY(0.0f),
	m_vBoxDirection(0, 0, 1),
	m_fBoxScale(1.0f)

{
	g_pDeviceManager;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

}


cMainGame::~cMainGame()
{	
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup() 
{
	srand(time(NULL));

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();


	SetGrid();

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
	SetGrid();
	DrawGrid();
	m_pCubePC->Render();	
	

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::SetGrid()
{
	// 그리드 표시용
	int nNumHalfTile = 10;
	double fInterval = 1.0f;
	double fMax = nNumHalfTile * fInterval;
	double fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		ST_PC_VERTEX	v;

		if (i % 5 == 0)
			v.color = D3DCOLOR_XRGB(200,200,200);
		else		
			v.color = D3DCOLOR_XRGB(120,120,120);

		v.p = D3DXVECTOR3(fMin, 0, i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval);			m_vecGridVertex.push_back(v);


		v.p = D3DXVECTOR3(i * fInterval, 0, fMin);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin);			m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax);			m_vecGridVertex.push_back(v);

	}

	// 가운데 선은 비어있게 되니까 채워준다.
	// z축은 빨간색
	ST_PC_VERTEX	v;
	v.color = D3DCOLOR_XRGB(255, 0,0);
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecGridVertex.push_back(v);
	

	// X축은 파란색
	v.color = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(fMin, 0, 0 );
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecGridVertex.push_back(v);
	

	// y축은 녹색
	v.color = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(0, fMax, 0);
	m_vecGridVertex.push_back(v);
}

void cMainGame::DrawGrid()
{
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecGridVertex.size() / 2, &m_vecGridVertex[0], sizeof(ST_PC_VERTEX));
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
