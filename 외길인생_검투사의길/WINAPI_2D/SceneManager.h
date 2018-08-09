#pragma once
#include "cManager.h"
#include <vector>

class SceneManager : public cManager
{
public:
	SceneManager();
	~SceneManager();
	void UnloadScene();
	void LoadScene(int destSceneidx);
	void DrawScene(HDC hdc);
	void ChangeScene(int destSceneidx);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawToFront(HDC destDC, HDC srcDC);
	void DrawTitleScene(HDC hdc);
	void DrawTownScene(HDC hdc);
	void KeyInput(WPARAM wParam);
	bool PeekNextPlace(POINT nextPos);
	std::vector<HBITMAP> resources;



private:	
	POINT PC_POS;
	short TownMap[15][18] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,
		0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
		0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	//for town map movement test
	int tmpflag = 1;
};

