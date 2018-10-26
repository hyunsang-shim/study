// OBB 충돌을 위해 추가 2018-10-26
// 강사님 소스 제공
#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
public:
	SINGLETONE(cSkinnedMeshManager);

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename);
	void Destroy();

private:
	map<string, cSkinnedMesh*> m_mapSkinnedMesh;
};