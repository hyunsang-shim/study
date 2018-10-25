#include "stdafx.h"
#include "cSkinnedMesh.h"

#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
	, m_pPrevAnimSet(NULL)
	, m_pNextAnimSet(NULL)
{	
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy	ah;
	D3DXFrameDestroy(m_pRoot, &ah);
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
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	// 해당 프레임에 대응하는 월드 매트릭스를 찾아 세팅하는 역학
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
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);				// 현재 진행중인 애니 정보
	m_pAnimController->GetTrackAnimationSet(0, &m_pPrevAnimSet);		// 현재 진행중인 애니메이션 셋	
	m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// 변경할 애니셑 정보를 얻는다
	m_fCurAnimPosRate = m_pPrevAnimSet->GetPeriodicPosition(stTrackDesc.Position) / m_pPrevAnimSet->GetPeriod();
	printf("Cur Ani :%s\n", m_pPrevAnimSet->GetName());
	//printf("%f\n", fAnimPosRate);
	const char* isConvertable = strstr(m_pPrevAnimSet->GetName(), "Attack");
	if (isConvertable == NULL || (isConvertable && m_fCurAnimPosRate > BLENDING_START_RATE))				// 공격 애니가 진행 중이면 바꾸지 않고 넘어간다.
	{
		printf("Ani idx #%d [ %s(%.3f%% elapsed) -> %s\n", nIndex, m_pPrevAnimSet->GetName(), m_fCurAnimPosRate, m_pNextAnimSet->GetName());
		m_pAnimController->SetTrackAnimationSet(1, m_pPrevAnimSet);		// 1번 트랙에 애니를 세팅
		m_pAnimController->SetTrackDesc(1, &stTrackDesc);				// 1번 트랙에 애니 정보를 세팅

//		m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// 변경할 애니셑 정보를 얻는다
		m_pAnimController->SetTrackAnimationSet(0, m_pNextAnimSet);		// 다음 애니를 0번 트랙에 셑
		m_pAnimController->SetTrackPosition(0, 0.0f);					// 0번 트랙을 처음부터 재상하도록 셑

		m_pAnimController->SetTrackWeight(0, 0.0f);						// 0번 애니(바뀌기 전 애니)의 가중치 0으로
		m_pAnimController->SetTrackWeight(1, 1.0f);						// 1번 애니(바뀐 후 애니)의 가중치 1로

		m_isAnimBlend = true;
		m_fPassedBlendTime = 0.0f;
		WorkState = 1;
	}
	else
	{
		m_pAnimController->SetTrackAnimationSet(1, m_pPrevAnimSet);		// 1번 트랙에 애니를 세팅
		m_pAnimController->SetTrackDesc(1, &stTrackDesc);				// 1번 트랙에 애니 정보를 세팅

																		//		m_pAnimController->GetAnimationSet(nIndex, &m_pNextAnimSet);		// 변경할 애니셑 정보를 얻는다
		m_pAnimController->SetTrackAnimationSet(0, m_pNextAnimSet);		// 다음 애니를 0번 트랙에 셑
		m_pAnimController->SetTrackPosition(0, 0.0f);					// 0번 트랙을 처음부터 재상하도록 셑

		m_pAnimController->SetTrackWeight(0, 0.0f);						// 0번 애니(바뀌기 전 애니)의 가중치 0으로
		m_pAnimController->SetTrackWeight(1, 1.0f);						// 1번 애니(바뀐 후 애니)의 가중치 1로

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
