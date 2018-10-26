// OBB �浹�� ���� �߰� 2018-10-26
// ����� �ҽ� ����
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