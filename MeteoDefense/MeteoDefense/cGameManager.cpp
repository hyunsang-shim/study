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

RECT cGameManager::getIdLabel()
{
	RECT tmp;

	tmp.top = 10;
	tmp.left = 10;
	tmp.bottom = tmp.top + 20;
	tmp.right = tmp.left + ID_MAX_SIZE * FONT_SIZE;

	return tmp;
}

cGameManager::~cGameManager()
{
}
