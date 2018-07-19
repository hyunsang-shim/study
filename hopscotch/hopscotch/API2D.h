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

	const int IMAGE_SIZE_X = 100;
	const int IMAGE_SIZE_Y = 120;
	POINT DrawStart = { 0,0 };
	
	int cur_posX = 0;
	int cur_posY = 0;
	int FacingDir = FACING_DOWN;

	int CurFrame = RUN_FRAME_MIN;
	RECT rectView;
	TCHAR *strText;

public:
	const int RUN_FRAME_MAX = IMAGE_SIZE_X / SPRITE_WIDTH - 1;
	const int RUN_FRAME_MIN = 0;
	void Init(HWND hwnd);
	void Update(HWND hwnd);
	void UpdataAnimation();
	void UpdateUI(HWND hwnd);
	void UpdateText();
	void Draw(HDC hdc);
	void DrawAnimation(HDC hdc);
	void PrintText(HDC hdc);
	void SetPosX(int x);
	void SetPosY(int y);
	void SetDrawStart(POINT StartPos);
	POINT GetDrawStart();
	int GetPosX();
	int GetPosY();
	void AddFrame(int x);
	void setFacingDir(int FacingDir);
	int getFacingDir();
	void DrawLine(HWND hWnd);
};

