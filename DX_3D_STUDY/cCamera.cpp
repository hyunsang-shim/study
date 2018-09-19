#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	:m_vEye(0,5,-5)
	 , m_vLookAt(0,0,0)
	 , m_vUp(0,1,0)
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
	ī�޶� ȭ���� ĳ���� ������ � ���� ȸ���ؾ� �ϹǷ� ���⿡�� ������Ʈ �� �� �ֵ���
	*/
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, 0.0f);
	D3DXMatrixRotationY(&matRY, 0.0f);

	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 5, -5);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);


}
