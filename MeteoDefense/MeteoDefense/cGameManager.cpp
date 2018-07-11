#include "cGameManager.h"
#include <windows.h>
#include <string>




cGameManager::cGameManager()
{
}

TCHAR cGameManager::getID()
{
	return *id;
}


void cGameManager::setID(TCHAR *newid)
{	
	for (int i = 0; i < lstrlen(id); i++)
		this->id[i] = newid[i];
}

cGameManager::~cGameManager()
{
}
