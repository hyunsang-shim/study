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
	int GetBattleState_PC();
	int GetBattleState_Mob();
	void SetBattleState_PC(int state);
	void SetBattleState_Mob(int state);
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
	int BattleState_PC = Ready;
	int BattleState_Mob = Ready;
	HWND MyHWND;
	HINSTANCE hInst;
	
};

