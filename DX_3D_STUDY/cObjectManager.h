#pragma once

/* 강사님 ASE 로더*/
class cObject;

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
public:
	/*cObjectManager();
	~cObjectManager();*/
private:
	SINGLETONE(cObjectManager);
private:
	set<cObject*> m_setObject;
public :
	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}

	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}

	void Destroy()
	{
		m_setObject.clear();
		//assert(m_setObject.empty());	// 없어도 OK
	}
};

