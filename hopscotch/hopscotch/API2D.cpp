#include "stdafx.h"
#include "API2D.h"
#include "Manager.h"
#pragma comment(lib, "msimg32.lib")

API2D::API2D() : cur_posX(0), cur_posY(0), CurFrame(1)
{
	AddLifeStock(3);
	strText = NULL;
}


API2D::~API2D()
{
}

void API2D::Init(HWND hWnd)
{
	hBit = (HBITMAP)LoadImage(NULL, TEXT("masaru.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(BITMAP), &bit);

	hBit2 = (HBITMAP)LoadImage(NULL, TEXT("PC_SPRITES.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit2, sizeof(BITMAP), &bit2);

	DrawingPosXY.push_back({ 0, 0 });

}

void API2D::Update(HWND hwnd)
{
	UpdateText();
	DrawLine(hwnd);
	UpdataAnimation();
	UpdateUI(hwnd);
}

void API2D::UpdataAnimation()
{
	if (getPLAYER_STATUS() == MOVING || getPLAYER_STATUS() == DRAWING)
	{
		if (CurFrame > RUN_FRAME_MAX)
			CurFrame = RUN_FRAME_MIN;
	}
}

void API2D::UpdateText()
{}

void API2D::UpdateUI(HWND hWnd)
{

	//�÷��̾� �ܱ� ǥ��
	HDC hdc = GetDC(hWnd);
	HDC hMemDC2;
	HBITMAP hLifeBitmap;

	hMemDC2 = CreateCompatibleDC(hdc);
	hLifeBitmap = (HBITMAP)SelectObject(hMemDC2, hBit2);

	for (int i = 0; i < this->GetLifeStock(); i++)
		TransparentBlt(hdc, 10 + i * SPRITE_WIDTH, 25, SPRITE_WIDTH, SPRITE_HEIGHT,
			hMemDC2,
			26, 0, 25, 30, RGB(255, 0, 255));

	//���� ���� �̹����� �޸𸮿� �׷ȴ� DC�� �����Ѵ�.
	SelectObject(hMemDC2, hLifeBitmap);
	DeleteDC(hMemDC2);

}

void API2D::Draw(HDC hdc)
{
	HDC hMemDC;	
	HBITMAP hOldBitmap;
	int bx, by;
	bx = bit.bmWidth;
	by = bit.bmHeight;
	setWidthMax(bx);
	setHeightMax(by);

	hMemDC = CreateCompatibleDC(hdc);
	GetStockObject(NULL_BRUSH);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);	
	
	
	//��� �̹����� �׸���.
	TransparentBlt(hdc, 1, 1, bx, by, hMemDC, 0, 0, bx,by, RGB(255, 0, 255));
	//��� �̹����� �޸𸮿� �׷ȴ� DC�� �����Ѵ�.
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

	bx = SPRITE_WIDTH;
	by = SPRITE_HEIGHT;

	int StartX = CurFrame * bx;
	int StartY = (FacingDir-1) * SPRITE_HEIGHT;

	TransparentBlt(hdc, cur_posX- SPRITE_WIDTH /2, cur_posY- SPRITE_HEIGHT /2, bx, by, hMemDC,
		StartX, StartY, bx, by,
		RGB(255, 0, 255));

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

void API2D::SetDrawStart(POINT StartPos)
{
	this->DrawStart.x = StartPos.x;
	this->DrawStart.y = StartPos.y;
}

POINT API2D::GetDrawStart()
{	
	return this->DrawStart;
}


void API2D::DrawLine(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	HDC hMemDC = CreateCompatibleDC(hdc);
	if ((getPLAYER_STATUS() == DRAWING) && DrawingPosXY.size() > 0)	// �׸��� ���� & ��ǥ ����� ���� 1�� �̻��� ��
	{
		MoveToEx(hdc, GetDrawStart().x, GetDrawStart().y, NULL);
		LineTo(hdc, DrawingPosXY[0].x, DrawingPosXY[0].y);

		for (int i = 1; i < DrawingPosXY.size(); i++)
		{
			MoveToEx(hdc, DrawingPosXY[i-1].x, DrawingPosXY[i-1].y, NULL);
			LineTo(hdc, DrawingPosXY[i].x, DrawingPosXY[i].y);
		}
	}

	BitBlt(hdc, 0, 0, getWidthMax(), getHeightMax(), hMemDC, 0, 0, SRCPAINT);
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
	if (CurFrame + x > RUN_FRAME_MAX)
	{
		CurFrame = RUN_FRAME_MIN;
	}
	else
		CurFrame += x;
}

void API2D::setFacingDir(int FacingDir)
{
	this->FacingDir = FacingDir;
}

int API2D::getFacingDir()
{
	return this->FacingDir;
}
