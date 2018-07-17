#pragma once
#include <Windows.h>
#include "Manager.h"

enum facingDirection {
	FACING_DOWN = 1,
	FACING_LEFT,
	FACING_RIGHT,
	FACING_UP
};
class API2D : public Manager
{
public:
	API2D();
	~API2D();

private:
	HBITMAP hBit, oldBit;
	BITMAP bit;

	HBITMAP hBit2, oldBit2;
	BITMAP bit2;

	const int IMAGE_SIZE_X = 75;
	const int IMAGE_SIZE_Y = 120;
	const int SPRITE_SIZE_X = 25;
	const int SPRITE_SIZE_Y = 30;
	SIZE DrawStart = { 0 };
	
	int cur_posX = 50;
	int cur_posY = 50;
	int FacingDir = 1;

	int CurFrame = RUN_FRAME_MIN;
	RECT rectView;
	int posX, posY;
	TCHAR *strText;

public:
	const int RUN_FRAME_MAX = IMAGE_SIZE_X / SPRITE_SIZE_X - 1;
	const int RUN_FRAME_MIN = 0;
	void Init(HWND hwnd);
	void Update(HWND hwnd);
	void UpdataAnimation();
	void UpdateText();
	void Draw(HDC hdc);
	void DrawAnimation(HDC hdc);
	void PrintText(HDC hdc);
	void SetPosX(int x);
	void SetPosY(int y);
	void SetDrawStart(SIZE StartPos);
	SIZE GetDrawStart();
	int GetPosX();
	int GetPosY();
	void AddFrame(int x);
	void setDir(int FacingDir);
};

