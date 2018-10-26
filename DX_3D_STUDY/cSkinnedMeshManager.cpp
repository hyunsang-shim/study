// OBB 충돌을 위해 추가 2018-10-26
// 강사님 소스 제공
#include "stdafx.h"
#include "cSkinnedMeshManager.h"
#include "cSkinnedMesh.h"


cSkinnedMeshManager::cSkinnedMeshManager()
{
}


cSkinnedMeshManager::~cSkinnedMeshManager()
{
}

cSkinnedMesh * cSkinnedMeshManager::GetSkinnedMesh(char * szFolder, char * szFilename)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFilename));

	if (m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFilename);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}

	return m_mapSkinnedMesh[sFullPath];
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}
}
