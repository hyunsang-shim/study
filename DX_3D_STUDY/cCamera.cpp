#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	:m_vEye(3, 5, -5)
	, m_vLookAt(0, 1, 0)
	, m_vUp(0, 1, 0)
	, m_fCameraDistance(10.0f)
	, m_vCamRotAngle(0,0,0)
	, m_vBoxPosition(0,0,0)
	, m_isFollow(false)
	, m_vLookAt_FIXED(0, 1, 0)
	, m_vEye_FIXED(3, 5, -5)
	, m_vLookAt_FOLLOW(0, 1, 0)
	, m_vEye_FOLLOW(3, 5, -5)
{
}

cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	/*
	ī�޶� ȭ���� ĳ���� ������ � ���� ȸ���ؾ� �ϹǷ� ���⿡�� ������Ʈ �� �� �ֵ���
	*/
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	// �� �����ӿ� ���� ī�޶� �Ÿ��� ����
	m_vEye = D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);

	// ī�޶� ��忡 ���� ���󰡱� ��� ����
	if (m_isFollow)
	{		
		// ���󰡱� ���� ĳ������ �ڿ��� �ٶ󺸵��� �Ѵ�.						
		D3DXVec3Add(&m_vEye, &m_vEye, &m_vBoxPosition);

		m_vLookAt = m_vBoxPosition;
		m_vLookAt.y = m_vBoxPosition.y + 1;

		m_vEye_FIXED = m_vEye_FOLLOW = m_vEye;
		m_vLookAt_FIXED = m_vLookAt_FOLLOW = m_vLookAt;
	}


	D3DXMATRIXA16 matView;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
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

D3DXVECTOR3 cCamera::GetCamPos()
{
	return m_vEye;
}

void cCamera::SetCameraPosY(double posY)
{
	m_vEye.y = posY;
}

void cCamera::SetBoxPosition(D3DXVECTOR3 position)
{
	m_vBoxPosition.x = position.x;
	m_vBoxPosition.y = position.y;
	m_vBoxPosition.z = position.z;
}

void cCamera::ChangeCameraMode(bool value)
{
	if (value == true)
	{
		m_isFollow = true;
	}
	else
	{			
		m_isFollow = false;
	}

}


D3DXVECTOR3 cCamera::GetCamEye()
{
	return D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);;
}
