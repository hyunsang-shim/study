#include "cGameManager.h"

cGameManager::cGameManager()
{	
}

cGameManager::~cGameManager()
{
}

int cGameManager::getCurrentScene()
{
	return this->CurrentScene;
}

void cGameManager::SetCurrentScene(int scene)
{
	this->CurrentScene = scene;
}

void cGameManager::SetInputLabel(HWND hwnd)
{
	RECT tmpRect;
	GetClientRect(hwnd, &tmpRect);

	this->InputLabel.left = tmpRect.right / 2 - 100;
	this->InputLabel.right = tmpRect.left + 100;
	this->InputLabel.top = tmpRect.bottom / 4;
	this->InputLabel.bottom = tmpRect.top + 50;
}

RECT cGameManager::GetInputLabel()
{
	return this->InputLabel;
}

void cGameManager::SetInputBox(HWND hwnd)
{
	RECT tmpRect = GetInputLabel();

	InputBox.left = tmpRect.left - 50;
	InputBox.top = tmpRect.top + 30;
	InputBox.bottom = InputBox.top + 40;
	InputBox.left = InputBox.left + 100;
}

RECT cGameManager::GetInputBox()
{
	return this->InputBox;
}