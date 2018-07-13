#include "cGameManager.h"
#include <TCHAR.H>
#include <windows.h>
#include <cstdlib>

cGameManager::cGameManager()
{}

cGameManager::~cGameManager()
{}

int cGameManager::getCurrentScene()
{
	return this->CurrentScene;
}

void cGameManager::SetCurrentScene(int scene)
{
	this->CurrentScene = scene;
}

void cGameManager::SetInputArea(HWND hwnd)
{
	RECT tmpRect;
	GetClientRect(hwnd, &tmpRect);

	this->posInputLabel.left = tmpRect.right / 2-50;
	this->posInputLabel.right = tmpRect.left + 100;
	this->posInputLabel.top = tmpRect.bottom / 4;
	this->posInputLabel.bottom = tmpRect.top + 50;

	this->posInputBox.left = posInputLabel.left;
	this->posInputBox.top = posInputLabel.top + 30;
	this->posInputBox.bottom = posInputBox.top + 40;
	this->posInputBox.right = posInputBox.left + 100;
}

RECT cGameManager::GetInputLabel()
{
	return this->posInputLabel;
}

RECT cGameManager::GetInputBox()
{
	return this->posInputBox;
}

void cGameManager::SetPLAYER_ID(TCHAR* id)
{
	for (int i = 0; i < ID_MAX_SIZE; i++)
	{
		PLAYER_ID[i] = id[i];
	}

}

void cGameManager::SetPlayer_Dead()
{
	this->isPlayerDead = true;
}

TCHAR * cGameManager::GetPLAYER_ID()
{
	return PLAYER_ID;
}

int cGameManager::GetPLAYER_SCORE()
{
	return this->PLAYER_SCORE;
}

RECT cGameManager::GetPosDisplayLabel_ID()
{
	return posDisplayLabel_ID;
}

RECT cGameManager::GetPosDisplayLabel_Score()
{
	return posDisplayLabel_Score;
}

void cGameManager::SetGuard(HDC hdc, RECT *Screen, stGUARD* thisGuard, int id)
{
	LONG width = Screen->right / NUM_OF_GUARDS;

	//위치를 세팅
	thisGuard->MyPos = { 		
		Screen->left + id * width,			Screen->bottom - GUARD_POS_TOP_MODIFIER - GUARD_HEIGHT,
		Screen->left + id * width + width,	Screen->bottom - GUARD_POS_TOP_MODIFIER + GUARD_HEIGHT 	};

	//HP최대값 & 현재값 세팅
	thisGuard->MaxHP = thisGuard->CurHP = DEFAULT_GUARD_HP;
	//HP 표시 위치 세팅
	thisGuard->Label_HP.cx = thisGuard->MyPos.left + (thisGuard->MyPos.right - thisGuard->MyPos.left) / 2;
	thisGuard->Label_HP.cy = thisGuard->MyPos.top + LABEL_MARGIN;

	//모습을 그린다.
	/*Rectangle(hdc, 
		thisGuard->MyPos.left, 
		thisGuard->MyPos.top, 
		thisGuard->MyPos.right, 
		thisGuard->MyPos.bottom);*/
}

void cGameManager::SetPosDisplayLabel_ID(RECT *screen)
{
	posDisplayLabel_ID = { screen->left +5, screen->top + 5, screen->left + 100, screen->top + 50 };
}

void cGameManager::SetPosDisplayLabel_Score(RECT *screen)
{
	posDisplayLabel_Score = { screen->right / 2 - 100, screen->top + 5, screen->right / 2 + 100, screen->top + 50 };
}

void cGameManager::AddScore(UINT score)
{
	this->PLAYER_SCORE += score;
}

