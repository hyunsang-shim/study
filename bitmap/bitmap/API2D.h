#pragma once
#include <Windows.h>
class API2D
{
public:
	API2D();
	~API2D();	

private:
	HBITMAP hBit, oldBit;
	BITMAP bit;

	HBITMAP hBit2, oldBit2;
	BITMAP bit2;

	const int IMAGE_SIZE_X = 912;
	const int IMAGE_SIZE_Y = 104;
	const int SPRITE_SIZE_X = 57;
	const int SPRITE_SIZE_Y = 52;
	const int RUN_FRAME_MAX = IMAGE_SIZE_X / SPRITE_SIZE_X - 1;
	const int RUN_FRAME_MIN = 2;
	int cur_posX = 0;
	int cur_posY = 0;
	int dirY = 0;
	bool isRight = true;
	
	int CurFrame = RUN_FRAME_MIN;
	RECT rectView;
	int posX, posY;
	TCHAR *strText;

public:
	void Init(HWND hwnd);
	void Update();
	void UpdataAnimation();
	void UpdataText();
	void Draw(HDC hdc);
	void DrawAnimation(HDC hdc);
	void PrintText(HDC hdc);
	void SetPosX(int x);
	void SetPosY(int y);
	int GetPosX();
	int GetPosY();
	void setDir(bool isRight);
};

