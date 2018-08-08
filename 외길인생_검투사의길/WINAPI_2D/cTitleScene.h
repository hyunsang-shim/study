#pragma once
#include "SceneManager.h"

class cTitleScene : public SceneManager
{
public:
	cTitleScene();
	void LoadScene(HINSTANCE hInst, HDC hdc);
	//void UnLoadScene();
	void DrawScene(HDC hdc);
	void ProcessKeyInput(HWND hWnd, WPARAM wParam);
	~cTitleScene();

private:
	int curSelectorFrame = 0;
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 255));
	HBITMAP bg_title, txt1,txt2, menu1, menu2_on, menu2_off, menu3, selector;
	int selectorFrameMax = 4;


};

