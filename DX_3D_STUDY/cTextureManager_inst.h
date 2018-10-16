#pragma once

#define g_pTextureManager cTextureManager_inst::GetInstance()


class cTextureManager_inst
{
//public:
//	cTextureManager_inst();
//	~cTextureManager_inst();


private:
	SINGLETONE(cTextureManager_inst);
private:
	map<string, LPDIRECT3DTEXTURE9>		m_mapTexture;
public:
	LPDIRECT3DTEXTURE9					GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9					GetTexture(string& szFullPath);
	void Destroy();
};

