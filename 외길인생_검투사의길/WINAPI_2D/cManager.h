#pragma once
#include "WINAPI_2D.h"




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
	void SetPC_State(int state);
	int GetPC_State();
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
	int PC_Speed = 4;
	int PC_State = Idle;
	HWND MyHWND;
	HINSTANCE hInst;
	
};

