#include "stdafx.h"
#include "cManager.h"


cManager::cManager()
{
	CurScene = TitleScene;
}

void cManager::SetCurScene(int SceneName)
{
	this->CurScene = SceneName;
}


cManager::~cManager()
{
}

int cManager::GetCurScene()
{
	return CurScene;
}

void cManager::SetCurMenu(int menu)
{
	CurMenu = menu;
}

int cManager::GetCurMenu()
{
	return CurMenu;
}
