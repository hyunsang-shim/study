#include "stdafx.h"
#include "cTextureManager_inst.h"


cTextureManager_inst::cTextureManager_inst()
{
}


cTextureManager_inst::~cTextureManager_inst()
{
}

LPDIRECT3DTEXTURE9 cTextureManager_inst::GetTexture(char * szFullPath)
{

	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager_inst::GetTexture(string & szFullPath)
{
	return GetTexture((char*)szFullPath.c_str());
}

void cTextureManager_inst::Destroy()
{
	for each(auto it in m_mapTexture)
		SAFE_RELEASE(it.second);
	m_mapTexture.clear();
}
