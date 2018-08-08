#pragma once
#include "SceneManager.h"


class cTownScene : public SceneManager
{
public:
	cTownScene();
	void LoadScene(HINSTANCE hInst, HDC hdc);
	void UnloadScene();
	void DrawScene(HDC hdc);
	void ProcessKeyInput(HWND hWnd, WPARAM wParam);

	~cTownScene();

private:
	HBITMAP bg_town;
	HBITMAP character_PC;
	POINT PC_pos;
	int CurPcFrame = 0;
};

