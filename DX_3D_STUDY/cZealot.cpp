#include "stdafx.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"

class cOBB;

cZealot::cZealot()
	: m_pSkinnedMesh(NULL)
	, m_pOBB(NULL)
	, m_pCharacterController(NULL)
{
}


cZealot::~cZealot()
{
	SAFE_RELEASE(m_pCharacterController);
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pOBB);
}

void cZealot::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.x");	
	m_pSkinnedMesh->SetRandomTrackPosition();		// ���ص� OK 

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedMesh);
}

void cZealot::Setup(D3DXVECTOR3 startPos)
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.x");
	m_pSkinnedMesh->SetRandomTrackPosition();		// ���ص� OK 

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedMesh);

}

void cZealot::Update()
{
	// �� ��ǥ�� �ݿ� �Ϸ��� ���ڷ� ���� �޾Ƽ� �Ѱ��־� ó���ϵ��� �Ѵ�.
	// iMap Ŭ���� �ۼ� �����ؼ� �ϼ��� ��.
	if (m_pCharacterController)
		m_pCharacterController->Update();

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ? m_pCharacterController->GetTransform() : NULL);

}

void cZealot::Render(D3DCOLOR c)
{
	if (m_pCharacterController)
		m_pSkinnedMesh->SetTransform(m_pCharacterController->GetTransform());

	m_pSkinnedMesh->UpdateAndRender();

	if (m_pOBB)
		m_pOBB->OBBBox_Render(c);

}

cOBB * cZealot::GetOBB()
{
	return m_pOBB;
}
