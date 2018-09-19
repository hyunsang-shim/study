#include "stdafx.h"


cDeviceManager::cDeviceManager()
	:m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{	

	// �Ʒ��� m_pD3D->AddRef();�� ����.
	// ������ m_pD3D->Release()�� ������, SAFE_RELEASE(p) ��ũ�η� ���� �� �ξ���.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		stCaps;
	int			nVertexProcessing;

	// DX���� HAL�� ��� �� �� �ִ��� ������ ���´�.
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);


	//���� ������ DX�� ����� �� �ִ� �ϵ������
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// �ϵ��� �̿��� ������ 
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//��� �Ұ��ϴٸ� ����Ʈ���� ������
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}


	D3DPRESENT_PARAMETERS		stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;

	//stD3DPP.BackBufferFormat = D3DFMT_A8R8G8B8; // Ǯ��ũ�� ����� ��
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;




	// ��ġ ���� ���п� ���� ����ó���� ���� ���� �˾Ƽ�
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, nVertexProcessing, &stD3DPP, &m_pD3DDevice);

}


cDeviceManager::~cDeviceManager()
{
	Destroy();
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return  m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
}
