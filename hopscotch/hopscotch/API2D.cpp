#include "stdafx.h"
#include "API2D.h"
#include "Manager.h"
#pragma comment(lib, "msimg32.lib")

API2D::API2D() : posX(10), posY(10), CurFrame(1)
{
	AddLifeStock(3);
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

	hBit2 = (HBITMAP)LoadImage(NULL, TEXT("PC_SPRITES.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit2, sizeof(BITMAP), &bit2);
}

void API2D::Update(HWND hwnd)
{
	UpdateText();
	UpdataAnimation();
}

void API2D::UpdataAnimation()
{
	if (getPLAYER_STATUS() == MOVING)
	{
		if (CurFrame > RUN_FRAME_MAX)
			CurFrame = RUN_FRAME_MIN;
	}
}

void API2D::UpdateText()
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
	int StartY = (FacingDir-1) * SPRITE_SIZE_Y;

	TransparentBlt(hdc, cur_posX, cur_posY, bx, by, hMemDC,
		StartX, StartY, bx, by,
		RGB(255, 0, 255));

	//남은 생명을 그린다.
	for (int i = 0; i < this->GetLifeStock(); i++)
		TransparentBlt(hdc, 10 + i * SPRITE_WIDTH, 25, SPRITE_WIDTH,SPRITE_HEIGHT,
			hMemDC,
			26, 0, 25, 30,
			RGB(255, 0, 255));

	if (DrawingPosXY.size() != NULL)
		for (int i = 0; i < DrawingPosXY.size(); i++)
		{
			MoveToEx(hdc, (int)DrawingPosXY[i].cx, (int)DrawingPosXY[i].cy, NULL);
			LineTo(hdc, DrawingPosXY[i].cx, DrawingPosXY[i].cy);
		}

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void API2D::PrintText(HDC hdc)
{
}

void API2D::SetPosX(int x)
{
	this->cur_posX = x;
}

void API2D::SetPosY(int y)
{
	this->cur_posY = y;
}

void API2D::SetDrawStart(SIZE StartPos)
{
	this->DrawStart.cx = StartPos.cx;
	this->DrawStart.cy = StartPos.cy;
}

SIZE API2D::GetDrawStart()
{
	
	return this->DrawStart;
}

int API2D::GetPosX()
{
	return cur_posX;
}

int API2D::GetPosY()
{
	return cur_posY;
}

void API2D::AddFrame(int x)
{
	if (CurFrame+x > RUN_FRAME_MAX)
	{
		CurFrame = RUN_FRAME_MIN;
	}
	else
		CurFrame += x;
}

void API2D::setDir(int FacingDir)
{
	this->FacingDir = FacingDir;
}


