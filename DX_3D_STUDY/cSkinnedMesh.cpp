#include "stdafx.h"
#include "cSkinnedMesh.h"

#include "cAllocateHierarchy.h"
#include "cSkinnedMeshManager.h" // OBB �浹 ó���� ���� �߰� 2018-10-26


cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
	, m_pPrevAnimSet(NULL)
	, m_pNextAnimSet(NULL)
	, m_vMax(0, 0, 0)					// OBB �浹 ó���� ���� �߰� 2018-10-26
	, m_vMin(0, 0, 0)					// OBB �浹 ó���� ���� �߰� 2018-10-26
{	
	D3DXMatrixIdentity(&m_matWorldTM);	// OBB �浹 ó���� ���� �߰� 2018-10-26
}

cSkinnedMesh::cSkinnedMesh(char * szFolder, char * szFilename)	
	: m_pAnimController(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
	, m_pPrevAnimSet(NULL)
	, m_pNextAnimSet(NULL)
	, m_vMax(0, 0, 0)				// OBB �浹 ó���� ���� �߰� 2018-10-26
	, m_vMin(0, 0, 0)				// OBB �浹 ó���� ���� �߰� 2018-10-26
{
	D3DXMatrixIdentity(&m_matWorldTM);			// OBB �浹 ó���� ���� �߰� 2018-10-26
	cSkinnedMesh* pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);	// OBB �浹 ó���� ���� �߰� 2018-10-26
	m_pRoot = pSkinnedMesh->m_pRoot;

	m_vMin = pSkinnedMesh->m_vMin;
	m_vMax = pSkinnedMesh->m_vMax;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
}

cSkinnedMesh::~cSkinnedMesh()
{	
	SAFE_RELEASE(m_pAnimController);
	SAFE_RELEASE(m_pPrevAnimSet);
	SAFE_RELEASE(m_pNextAnimSet);
}

void cSkinnedMesh::Setup(char * szFolder, char * szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + string("/") + string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);
	HRESULT hr;

	hr = D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimController);


	// OBB �浹 ó���� ���� �߰� 2018-10-26
	{
		m_vMin = ah.GetMin();
		m_vMax = ah.GetMax();
	}

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Update()
{
	
	{
		if (m_isAnimBlend)
		{
			m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();

			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_isAnimBlend = false;
				m_pAnimController->SetTrackWeight(0, 1.0f);
				m_pAnimController->SetTrackWeight(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimController->SetTrackWeight(0, fWeight);
				m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
			}
		}
	}

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{

	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombineTransformationMatrix = pBone->TransformationMatrix;
	if (pParent)
	{
		pBone->CombineTransformationMatrix *= ((ST_BONE*)pParent)->CombineTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}

	

}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombineTransformationMatrix);

			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); i++)
			{
				
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}
	g_pD3DDevice->SetTexture(0, NULL);

}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	// �ش� �����ӿ� �����ϴ� ���� ��Ʈ������ ã�� �����ϴ� ����
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombineTransformationMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; i++)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dst = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dst);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrices, NULL, src, dst);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);

}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;


	LPD3DXANIMATIONSET pAnimSet = NULL;

	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	m_pAnimController->GetPriorityBlend();

	SAFE_RELEASE(pAnimSet);
}

int cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	int WorkState = -1;
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;
	

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);				// ���� �������� �ִ� ����
	m_pAnimController->GetTrackAnimationSet(0, &m_pPrevAnimSet);		// ���� �������� �ִϸ��̼� ��	
	m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// ������ �ִϙV ������ ��´�
	m_fCurAnimPosRate = m_pPrevAnimSet->GetPeriodicPosition(stTrackDesc.Position) / m_pPrevAnimSet->GetPeriod();
	printf("Cur Ani :%s\n", m_pPrevAnimSet->GetName());
	//printf("%f\n", fAnimPosRate);
	const char* isConvertable = strstr(m_pPrevAnimSet->GetName(), "Attack");
	if (isConvertable == NULL || (isConvertable && m_fCurAnimPosRate > BLENDING_START_PLAY_RATE))				// ���� �ִϰ� ���� ���̸� �ٲ��� �ʰ� �Ѿ��.
	{
		printf("Ani idx #%d [ %s(%.3f%% elapsed) -> %s\n", nIndex, m_pPrevAnimSet->GetName(), m_fCurAnimPosRate, m_pNextAnimSet->GetName());
		m_pAnimController->SetTrackAnimationSet(1, m_pPrevAnimSet);		// 1�� Ʈ���� �ִϸ� ����
		m_pAnimController->SetTrackDesc(1, &stTrackDesc);				// 1�� Ʈ���� �ִ� ������ ����

//		m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// ������ �ִϙV ������ ��´�
		m_pAnimController->SetTrackAnimationSet(0, m_pNextAnimSet);		// ���� �ִϸ� 0�� Ʈ���� �V
		m_pAnimController->SetTrackPosition(0, 0.0f);					// 0�� Ʈ���� ó������ ����ϵ��� �V

		m_pAnimController->SetTrackWeight(0, 0.0f);						// 0�� �ִ�(�ٲ�� �� �ִ�)�� ����ġ 0����
		m_pAnimController->SetTrackWeight(1, 1.0f);						// 1�� �ִ�(�ٲ� �� �ִ�)�� ����ġ 1��

		m_isAnimBlend = true;
		m_fPassedBlendTime = 0.0f;
		WorkState = 1;
	}
	else
	{
		m_pAnimController->SetTrackAnimationSet(1, m_pPrevAnimSet);		// 1�� Ʈ���� �ִϸ� ����
		m_pAnimController->SetTrackDesc(1, &stTrackDesc);				// 1�� Ʈ���� �ִ� ������ ����

																		//		m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// ������ �ִϙV ������ ��´�
		m_pAnimController->SetTrackAnimationSet(0, m_pNextAnimSet);		// ���� �ִϸ� 0�� Ʈ���� �V
		m_pAnimController->SetTrackPosition(0, 0.0f);					// 0�� Ʈ���� ó������ ����ϵ��� �V

		m_pAnimController->SetTrackWeight(0, 0.0f);						// 0�� �ִ�(�ٲ�� �� �ִ�)�� ����ġ 0����
		m_pAnimController->SetTrackWeight(1, 1.0f);						// 1�� �ִ�(�ٲ� �� �ִ�)�� ����ġ 1��

		m_isAnimBlend = false;
		m_fPassedBlendTime = 0.0f;
		WorkState = 99;
	}

	return WorkState;

}

float cSkinnedMesh::GetCurAnimPosRate()
{
	LPD3DXANIMATIONSET pAnimSet = NULL;	
	m_pAnimController->GetTrackAnimationSet(0, &pAnimSet);

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);

	return pAnimSet->GetPeriodicPosition(stTrackDesc.Position) / pAnimSet->GetPeriod();
}

void cSkinnedMesh::Load(char * szFolder, char * szFilename)
{
	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFilename));

	HRESULT hr = D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRoot,
		&m_pAnimController);

//	printf("%s", hr == S_OK ? "Zealot if successfully loaded" : "Failed to Load zealot");


	m_vMin = ah.GetMin();
	m_vMax = ah.GetMax();

	if (m_pRoot) SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	//SAFE_RELEASE(m_pAnimController);
}

void cSkinnedMesh::UpdateAndRender()
{
	if (m_pAnimController)
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	}
	if (m_pRoot)
	{
		Update((ST_BONE*)m_pRoot, &m_matWorldTM);
		Render(m_pRoot);
	}
}

void cSkinnedMesh::Update(ST_BONE * pCurrent, D3DXMATRIXA16 * pmatParent)
{
	if (pCurrent == NULL)
		pCurrent = (ST_BONE*)m_pRoot;

	pCurrent->CombineTransformationMatrix = pCurrent->TransformationMatrix;

	if (pmatParent)
	{
		pCurrent->CombineTransformationMatrix = pCurrent->CombineTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
	{
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}
	if (pCurrent->pFrameFirstChild)
	{
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombineTransformationMatrix));
	}
}

void cSkinnedMesh::SetRandomTrackPosition()
{

	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}

void cSkinnedMesh::SetTransform(D3DXMATRIXA16 * pmat)
{
	m_matWorldTM = *pmat;
}
