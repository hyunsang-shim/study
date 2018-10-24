#pragma once

#define g_pTimeManager cTimerManager::GetInstance()
class cTimerManager
{
public:


private:
	SINGLETONE(cTimerManager);

private:
	DWORD m_dwLastUpdateTime;
	float m_fEllapsedTime;

public :
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};

