#pragma once
//#include "stdafx.h"
#define g_pDeviceManager	cDeviceManager::GetInstance()
#define g_pD3DDevice			g_pDeviceManager->GetDevice()

class cDeviceManager
{
public:
	
	SINGLETONE(cDeviceManager)

	LPDIRECT3DDEVICE9		GetDevice();
	void Destroy();

private:
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;


};

