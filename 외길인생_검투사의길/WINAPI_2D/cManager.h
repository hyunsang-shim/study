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
	HINSTANCE hInst;
	
};

