#include "stdafx.h"
#include "cTimerManager.h"


cTimerManager::cTimerManager()
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimerManager::~cTimerManager()
{
}


void cTimerManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fEllapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float cTimerManager::GetElapsedTime()
{
	return m_fEllapsedTime;
}

float cTimerManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}
