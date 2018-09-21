#include "stdafx.h"
#include "cCubeBody.h"


cCubeBody::cCubeBody()
{
}


cCubeBody::~cCubeBody()
{
}

void cCubeBody::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16			matS, matT, mat;

	D3DXMatrixcaling(&matS, 0.4f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}
}