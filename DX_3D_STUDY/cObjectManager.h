#pragma once

/* ����� ASE �δ�*/
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
		//assert(m_setObject.empty());	// ��� OK
	}
};

