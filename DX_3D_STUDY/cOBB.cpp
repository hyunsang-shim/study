#include "stdafx.h"
#include "cOBB.h"
#include "cSkinnedMesh.h"


cOBB::cOBB()
{
}


cOBB::~cOBB()
{
}

void cOBB::Setup(cSkinnedMesh * pSkinnedMesh)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();
	m_vOrgCenterPos = (vMin + vMax / 2.0f);

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLength[0] = fabs(vMax.x - vMin.x);
	m_fAxisLength[1] = fabs(vMax.y - vMin.y);
	m_fAxisLength[2] = fabs(vMax.z - vMin.z);


	m_fAxisLength_Half[0] = m_fAxisLength[0] / 2.0f;
	m_fAxisLength_Half[1] = m_fAxisLength[1] / 2.0f;
	m_fAxisLength_Half[2] = m_fAxisLength[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);

}

void cOBB::Update(D3DXMATRIXA16 * pmatWorld)
{

	if (pmatWorld)
		m_matWorldTM = *pmatWorld;

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(
			&m_vAxisDir[i],
			&m_vOrgAxisDir[i],
			&m_matWorldTM);

		D3DXVec3TransformCoord(
			&m_vCenterPos,
			&m_vOrgCenterPos,
			&m_matWorldTM);
	}
}

bool cOBB::IsCollision(cOBB * pOBB1, cOBB * pOBB2)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;

	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutOff)
				existsParallelPair = true;
		}

		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);		// 투영 거리

		r = abs(dist[a]);

		r0 = pOBB1->m_fAxisLength_Half[a];

		r1 = pOBB2->m_fAxisLength_Half[0] * absCos[a][0] +
			pOBB2->m_fAxisLength_Half[1] * absCos[a][1] +
			pOBB2->m_fAxisLength_Half[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;
	}

	for (int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));

		r0 = pOBB1->m_fAxisLength_Half[0] * absCos[0][b] +
			pOBB1->m_fAxisLength_Half[1] * absCos[1][b] +
			pOBB1->m_fAxisLength_Half[2] * absCos[2][b];

		r1 = pOBB2->m_fAxisLength_Half[b];

		if (r > r0 + r1) return false;
	}

	if (existsParallelPair) return true;

	// 0
	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[2][0] + pOBB2->m_fAxisLength_Half[2] * absCos[0][0];
	r1 = pOBB2->m_fAxisLength_Half[0] * absCos[1][2] + pOBB2->m_fAxisLength_Half[2] * absCos[0][1];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[2][1] + pOBB2->m_fAxisLength_Half[2] * absCos[0][1];
	r1 = pOBB2->m_fAxisLength_Half[1] * absCos[1][2] + pOBB2->m_fAxisLength_Half[2] * absCos[1][0];
	if (r > r0 + r1) return false;

	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[2][2] + pOBB2->m_fAxisLength_Half[2] * absCos[0][2];
	r1 = pOBB2->m_fAxisLength_Half[1] * absCos[1][1] + pOBB2->m_fAxisLength_Half[1] * absCos[1][0];
	if (r > r0 + r1) return false;

	// 1
	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[1][0] + pOBB2->m_fAxisLength_Half[1] * absCos[0][0];
	r1 = pOBB2->m_fAxisLength_Half[1] * absCos[2][2] + pOBB2->m_fAxisLength_Half[2] * absCos[2][1];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[1][1] + pOBB2->m_fAxisLength_Half[1] * absCos[0][1];
	r1 = pOBB2->m_fAxisLength_Half[0] * absCos[2][2] + pOBB2->m_fAxisLength_Half[2] * absCos[2][0];
	if (r > r0 + r1) return false;

	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	r0 = pOBB1->m_fAxisLength_Half[0] * absCos[1][2] + pOBB2->m_fAxisLength_Half[1] * absCos[0][2];
	r1 = pOBB2->m_fAxisLength_Half[0] * absCos[2][2] + pOBB2->m_fAxisLength_Half[2] * absCos[2][0];
	if (r > r0 + r1) return false;

	// 2
	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	r0 = pOBB1->m_fAxisLength_Half[1] * absCos[2][0] + pOBB2->m_fAxisLength_Half[1] * absCos[1][0];
	r1 = pOBB2->m_fAxisLength_Half[1] * absCos[0][2] + pOBB2->m_fAxisLength_Half[2] * absCos[0][1];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
	r0 = pOBB1->m_fAxisLength_Half[1] * absCos[2][1] + pOBB2->m_fAxisLength_Half[2] * absCos[1][1];
	r1 = pOBB2->m_fAxisLength_Half[0] * absCos[0][2] + pOBB2->m_fAxisLength_Half[2] * absCos[0][0];
	if (r > r0 + r1) return false;

	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	r0 = pOBB1->m_fAxisLength_Half[1] * absCos[2][2] + pOBB2->m_fAxisLength_Half[2] * absCos[1][2];
	r1 = pOBB2->m_fAxisLength_Half[0] * absCos[0][1] + pOBB2->m_fAxisLength_Half[1] * absCos[0][0];
	if (r > r0 + r1) return false;
	
	return true;
}

void cOBB::OBBBox_Render(D3DCOLOR c)
{
	// 주어진 중점을 기준으로 8개의 정점을 구해 낸 다음 버택스를 만든다.
	// 만들어진 버택스를 버택스 버퍼에 넣고. 인덱스 버퍼를 통해 육면체를 그린다.
	// 그린 후, 색깔은 주어진 값에 맞춰 입력한다.

	//{
	//	vector<LPDIRECT3DVERTEXBUFFER9>	VB_tmp;


	//	LPDIRECT3DVERTEXBUFFER9 tmpLPVB;
	//	g_pD3DDevice->CreateVertexBuffer(8 * sizeof(ST_PC_VERTEX), 0, ST_PC_VERTEX::FVF, D3DPOOL_MANAGED, &VB, NULL);		

	//	ST_PC_VERTEX* tmpPC = NULL;
	//	m_vpVBforIB_SubMesh[i]->Lock(0, 0, (LPVOID*)&pV_tmpPC, 0);
	//	for (int j = 0; j < subMesh[i].vecVertex.size(); j++)
	//	{
	//		pV_tmpPNT[j].p = subMesh[i].vecVertex[j];
	//		pV_tmpPNT[j].normal = subMesh[i].vecVertex[subMesh[i].vec_nFaceIndex[j]];
	//		pV_tmpPNT[j].texture = subMesh[i].vecUV[subMesh[i].vec_nUV_Index[j]];
	//	}

	//	m_nVB_SubMesh.push_back(subMesh[i].vecVertex.size());
	//	m_vpVBforIB_SubMesh[i]->Unlock();
	//	

	//}
	////// 인덱스 버퍼
	//{
	//	m_vpIB_SubMesh.resize(subMesh.size());

	//	for (int i = 0; i < subMesh.size(); i++)
	//	{

	//		// 인덱스 버퍼 세팅
	//		WORD *piB;
	//		g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * subMesh[i].vec_nFaceIndex.size(), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_vpIB_SubMesh[i], NULL);
	//		m_vpIB_SubMesh[i]->Lock(0, 0, (void**)&piB, 0);

	//		for (int j = 0; j < subMesh[i].vec_nFaceIndex.size(); j++)
	//		{
	//			piB[j] = subMesh[i].vec_nFaceIndex[j];
	//		}
	//		m_nIB_SubMesh.push_back(subMesh[i].vec_nFaceIndex.size());
	//		m_vpIB_SubMesh[i]->Unlock();
	//	}

	//}
}
