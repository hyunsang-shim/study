#include "stdafx.h"
#include "cAseLoader_inst.h"

#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoader_inst::cAseLoader_inst()
	: m_fp(NULL)
{
}

cAseLoader_inst::~cAseLoader_inst()
{
}

cFrame * cAseLoader_inst::Load(IN char * szFullPath)
{
	
	cFrame* pRoot = NULL;


	fopen_s(&m_fp, szFullPath, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			ProcessScene();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOMOBJECT();
			if (pRoot == NULL)
			{
				pRoot = pFrame;
				Set_SceneFrame(pRoot);
			}
		}
	}

	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	pRoot->CalcOriginalLocalTM(NULL);

	return pRoot;



}

char * cAseLoader_inst::GetToken()
{

	int nReadCnt = 0;
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp)) break;

		if (c == '\"')
		{
			if (isQuote) break;

			isQuote = true;
			continue;
		}


		if (!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		m_szToken[nReadCnt++] = c;
	}

	if (nReadCnt == 0)
		return NULL;

	m_szToken[nReadCnt] = '\0';

	return m_szToken;

	
}

int cAseLoader_inst::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader_inst::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader_inst::IsWhite(IN char c)
{
	return c < 33;
}

bool cAseLoader_inst::IsEqual(IN char * str1, IN char * str2)
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader_inst::SkipBlock()
{
	int nLevel = 0;

	do	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMATERIAL_LIST()
{
	int nLevel = 0;

	do
	{
		char *szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each(auto p in m_vecMtlTex)
			{
				SAFE_RELEASE(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMATERIAL(OUT cMtlTex * pMtlTex)
{
	D3DMATERIAL9			stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
		
		int nLevel = 0;
	do
	{
		char *szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);

	pMtlTex->SetMaterial(stMtl);
}

void cAseLoader_inst::ProcessMAP_DIFFUSE(OUT cMtlTex * pMtlTex)
{	
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP));
		{
			szToken = GetToken();
			pMtlTex->SetTexture(g_pTextureManager->GetTexture(szToken));
		}
	} while (nLevel > 0);
}

cFrame * cAseLoader_inst::ProcessGEOMOBJECT()
{
	int nLevel = 0;
	cFrame *pFrame = new cFrame;

	do
	{
		char *szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNode_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			pFrame->SetmtlTex(m_vecMtlTex[nMtlIndex]);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANITMATION(pFrame);
		}
	} while (nLevel > 0);

	return pFrame;
}

void cAseLoader_inst::ProcessMESH(OUT cFrame * pFrame)
{
	
	vector<D3DXVECTOR3>			vecV;
	vector<D3DXVECTOR2>			vecVT;
	vector<ST_PNT_VERTEX>		vecVertex;
	int nLevel = 0;


	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if ( IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST ))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMAL(vecVertex);
		}
	} while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pFrame->GetWorldTM());
	for (size_t i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].normal, &vecVertex[i].normal, &matInvWorld);
	}

	pFrame->SetVertex(vecVertex);
}

void cAseLoader_inst::ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}		
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMESH_FACE_LIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[GetInteger()];

			GetToken();
			vecVertex[nFaceIndex * 3 + 2].p = vecV[GetInteger()];

			GetToken();
			vecVertex[nFaceIndex * 3 + 1].p = vecV[GetInteger()];
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMESH_TFACELIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].texture = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 2].texture = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 1].texture = vecVT[GetInteger()];			
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessMESH_NORMAL(OUT vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = { 0,2,1 };
	int nModCount = 0;

	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3			n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();

			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].normal = n;
		}
	} while (nLevel > 0);
}

void cAseLoader_inst::ProcessNode_TM(OUT cFrame * pFrame)
{
	D3DXMATRIXA16		matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}

		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	} while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);

}

void cAseLoader_inst::ProcessTM_ANITMATION(OUT cFrame * pFrame)
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}
	} while(nLevel > 0);
}

//////
void cAseLoader_inst::ProcessCONTROL_POS_TRACK(OUT cFrame * pFrame)
{
	vector<ST_POS_SAMPLE> vecPosTrack;

	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetInteger();
			s.v.x = GetFloat();			
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetPosTrack(vecPosTrack);

}

//////
void cAseLoader_inst::ProcessCONTROL_ROT_TRACK(OUT cFrame * pFrame)
{
	vector<ST_ROT_SAMPLE> vecRotTrack;

	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;

			s.n = GetInteger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			s.q.x *= sinf(s.q.w / 2.0f);
			s.q.z *= sinf(s.q.w / 2.0f);
			s.q.y *= sinf(s.q.w / 2.0f);
			s.q.w = cosf(s.q.w / 2.0f);

			if (!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q - s.q;
			}
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);

}

//////
void cAseLoader_inst::ProcessScene()
{
	int nLevel = 0;
	do
	{
		char *szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_LASTFRAME))
		{
			m_dwLastFrame= GetInteger(); 
		}
		else if (IsEqual(szToken, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetInteger();
		}
		else if (IsEqual(szToken, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetInteger();
		}

	} while (nLevel > 0);
}

void cAseLoader_inst::Set_SceneFrame(OUT cFrame * pRoot)
{
	pRoot->m_dwFirstFrame = m_dwFirstFrame;
	pRoot->m_dwLastFrame = m_dwLastFrame;
	pRoot->m_dwFrameSpeed = m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;
}