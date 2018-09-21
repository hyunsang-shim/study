#include "stdafx.h"
#include "cCubeman.h"

#include "cCubeBody.h"
#include "cCubeHead.h"
#include "cCubeLeftArm.h"
#include "cCubeRightArm.h"
#include "cCubeLeftLeg.h"
#include "cCubeRightLeg.h"

cCubeman::cCubeman()
	: m_pRoot(NULL)
{
}


cCubeman::~cCubeman()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cCubeman::Setup()
{
	cCharacter::Setup();

	cBody*		pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);

	m_pRoot = pBody;

	cCubehead* pHead = new cCubeHead;

	pHead->Setup();
	m_pRoot->Addchild(pHead);

	cCubeLeftArm* pLeftArm = new cCubeLeftArm;
	pLeftArm->Setup();
	m_pRoot->AddChild(pLeftArm);

	cCubeRightArm* pRightArm = new cCubeRightArm;
	pRightArm->Setup();
	m_pRoot->AddChild(pRightArm);


	cCubeLeftLeg* pLeftLeg = new cCubeLeftLeg;
	pLeftLeg->Setup();
	m_pRoot->AddChild(pLeftLeg);

	cCubeRightLeg* pRightLeg = new cCubeRightLeg;
	pRightLeg->Setup();
	m_pRoot->AddChild(pRightLeg);


}

void cCubeman::Update()
{
	cCharacter::Update();

	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeman::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		cCharacter::Render();

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		if (m_pRoot)
			m_pRoot->Render();
	}
}
