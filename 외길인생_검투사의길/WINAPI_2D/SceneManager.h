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
	bool PeekNextCoord(POINT CurPos);
	void MoveCharacter(POINT nextPoint);
	void SetPC_POS(int row, int col);
	POINT GetPC_POS();
	void SetPC_COORD(int row, int col);
	POINT GetPC_COORD();
	void SetPC_COORD_NEXT(int row, int col);
	POINT GetPC_COORD_NEXT();
	std::vector<HBITMAP> resources;



private:	
	POINT PC_POS;
	POINT PC_COORD;
	POINT PC_COORD_NEXT;
	short TownMap[14][17] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,
		0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
		0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	//for town map movement test
	int tmpflag = -1;
};

