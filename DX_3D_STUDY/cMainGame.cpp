#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	:m_pD3D(NULL)
	, m_pD3DDevice(NULL)

{
}


cMainGame::~cMainGame()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
}

void cMainGame::Setup()
{
}

void cMainGame::Update()
{
}

void cMainGame::Render()
{
}
