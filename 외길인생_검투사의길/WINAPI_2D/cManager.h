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
	
	~cManager();
	



public:
	static cManager* GetInstance()
	{
		static cManager instance;

		return &instance;
	}

private:
	int CurScene = TitleScene;
	int CurMenu = menuNew;
};

