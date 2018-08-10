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


HWND cManager::GetMyHWND()
{
	return this->MyHWND;
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

int cManager::GetDirection_PC()
{
	return PC_Direction;
}

void cManager::SetDirection_PC(int direction)
{
	//if (PC_Direction != direction)
		PC_Direction = direction;
}

void cManager::SetMyHWND(HWND hWnd)
{
	MyHWND = hWnd;
}

int cManager::GetSpeed_PC()
{
	return PC_Speed;
}

void cManager::SetPC_State(int state)
{
	PC_State = state;
}

int cManager::GetPC_State()
{
	return PC_State;
}
