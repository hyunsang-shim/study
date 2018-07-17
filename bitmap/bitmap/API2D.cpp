#include "API2D.h"
#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "msimg32.lib")

API2D::API2D() :posX(10), posY(10), CurFrame(1)
{
	strText = NULL;	
}


API2D::~API2D()
{
}

void API2D::Init(HWND hWnd)
{
	posX = 10;
	posY = 10;
	GetClientRect(hWnd, &rectView);

	hBit = (HBITMAP)LoadImage(NULL, TEXT("prince.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(BITMAP), &bit);

	hBit2 = (HBITMAP)LoadImage(NULL, TEXT("zero_run.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit2, sizeof(BITMAP), &bit2);

}

void API2D::Update()
{
	UpdataText();
	UpdataAnimation();

}

void API2D::UpdataAnimation()
{
	if (this->isRight)
	{
		CurFrame++;

		if (CurFrame > RUN_FRAME_MAX)
			CurFrame = RUN_FRAME_MIN;
	}
	else
	{
		CurFrame--;

		if (CurFrame < 0)
			CurFrame = RUN_FRAME_MAX-2;
	}

}

void API2D::UpdataText()
{
}

void API2D::Draw(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	DrawAnimation(hdc);

}

void API2D::DrawAnimation(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit2);

	bx = SPRITE_SIZE_X;
	by = SPRITE_SIZE_Y;

	int StartX = CurFrame * bx;

	TransparentBlt(hdc, cur_posX, cur_posY, bx, by, hMemDC,
		StartX, dirY, bx, by,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void API2D::PrintText(HDC hdc)
{
}

void API2D::SetPosX(int x)
{
	this->cur_posX += x;
}

void API2D::SetPosY(int y)
{
	this->cur_posY += y;
}

int API2D::GetPosX()
{
	return cur_posX;
}

int API2D::GetPosY()
{
	return cur_posY;
}

void API2D::setDir(bool isRight)
{
	if (this->isRight != isRight)
	{
		this->isRight = isRight;

		if (isRight == false)
		{
			CurFrame = RUN_FRAME_MAX - 2;
			this->dirY = SPRITE_SIZE_Y;
		}
		else
		{
			CurFrame = RUN_FRAME_MIN;
			this->dirY = 0;
		}
		if (this->isRight == false && isRight == true)
			dirY = 0;

	}
}
