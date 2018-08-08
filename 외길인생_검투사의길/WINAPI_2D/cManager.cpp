#include "stdafx.h"
#include "cManager.h"


cManager::cManager()
{
	CurScene = TitleScene;
	hInst = GetModuleHandle(NULL);
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

void cManager::SetLastScene(int SceneName)
{
	this->lastScene = SceneName;
}

int cManager::GetLastScene()
{
	return this->lastScene;
}

bool cManager::HaveSaveFile()
{
	return false;
}




