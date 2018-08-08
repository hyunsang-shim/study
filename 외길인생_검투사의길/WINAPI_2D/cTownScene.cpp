#include "stdafx.h"
#include "cTownScene.h"


cTownScene::cTownScene()
{
	PC_pos.x = 500;
	PC_pos.y = 550;	
}

void cTownScene::LoadScene(HINSTANCE hInst, HDC hdc)
{
	// prepare image resources
	bg_town = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	character_PC = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void cTownScene::UnloadScene()
{
	DeleteObject(bg_town);
	DeleteObject(character_PC);
}

void cTownScene::ProcessKeyInput(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
		PC_pos.y += 1;

		break;
	}
}

void cTownScene::DrawScene(HDC hdc)
{
	// A BackBuffer DC which sotres picture just before draw onto front DC(hdc).
	HDC BackMemDC;
	HBITMAP hOldBitmap;

	// copy front DC's attributes intto BackMemDC
	BackMemDC = CreateCompatibleDC(hdc);
	//make BackMemDC's size properly and select source image onto BackMemDC
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_town);

	// Draw BG Image (contains no transparent part)
	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SRCCOPY);

	DeleteObject(hOldBitmap);
	static int framecounter= 0;

	framecounter++;

	if (framecounter > (CHARACTER_FRAME_MAX * 12))
		framecounter = 0;
	else
		CurPcFrame = (framecounter/4) % 4;

	DrawSpriteImage(hdc, PC_pos.x, PC_pos.y, character_PC, CurPcFrame);

}



cTownScene::~cTownScene()
{
}
