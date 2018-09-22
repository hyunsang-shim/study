#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	:m_vEye(3, 5, -5),
	m_vLookAt(0, 0, 0),
	m_vUp(0, 1, 0),
	m_fCameraDistance(10.0f),
	m_vCamRotAngle(0,0,0),
	m_vBoxPosition(0,0,0)
{
}

cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16		matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	/*
	카메라 화면은 캐릭터 움직임 등에 따라 회전해야 하므로 여기에서 업데이트 될 수 있도록
	*/
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	// 휠 움직임에 따른 카메라 거리값 갱신
	m_vEye = D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);

	//m_vLookAt = m_vBoxPosition;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);


}

void cCamera::SetCameraDistance(double value)
{
	m_fCameraDistance = value;
}

void cCamera::SetCameraRotationAngle(D3DXVECTOR3 Angle)
{
	m_vCamRotAngle.x = Angle.x;
	m_vCamRotAngle.y = Angle.y;
}

void cCamera::SetBoxPosition(D3DXVECTOR3 position)
{
	m_vBoxPosition.x = position.x;
	m_vBoxPosition.y = position.z;
	m_vBoxPosition.z = position.z;
}
