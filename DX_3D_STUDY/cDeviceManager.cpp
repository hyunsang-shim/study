#include "stdafx.h"


cDeviceManager::cDeviceManager()
	:m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{	

	// 아래는 m_pD3D->AddRef();와 같다.
	// 해제는 m_pD3D->Release()와 같은데, SAFE_RELEASE(p) 매크로로 정의 해 두었다.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		stCaps;
	int			nVertexProcessing;

	// DX에서 HAL을 사용 할 수 있는지 정보를 얻어온다.
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);


	//현재 버전의 DX를 사용할 수 있는 하드웨어라면
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// 하드웨어를 이용한 렌더링 
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//사용 불가하다면 소프트웨어 렌더링
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}


	D3DPRESENT_PARAMETERS		stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;

	//stD3DPP.BackBufferFormat = D3DFMT_A8R8G8B8; // 풀스크린 모드일 때
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;




	// 장치 생성 실패에 대한 예외처리는 차후 각자 알아서
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
