#pragma once
#include "WINAPI_2D.h"

#define SCREEN_WIDTH 816
#define SCREEN_HEIGHT 624


class cManager
{
public:
	cManager();
	void SetCurScene(int SceneName);
	int GetCurScene();
	void SetCurMenu(int menu); 
	int GetCurMenu();
	void SetLastScene(int SceneName);
	int GetLastScene();
	bool HaveSaveFile();
	int GetDirection_PC();
	void SetDirection_PC(int direction);
	void SetMyHWND(HWND hWnd);
	int GetSpeed_PC();
	HWND GetMyHWND();
	~cManager();
	

public:
	static cManager* GetInstance()
	{
		static cManager instance;

		return &instance;
	}

private:
	int CurScene;
	int CurMenu = menuNew;
	int lastScene = TitleScene;	
	int PC_Direction = FacingRight;
	int PC_Speed = 6;
	HWND MyHWND;
	HINSTANCE hInst;
	
};

