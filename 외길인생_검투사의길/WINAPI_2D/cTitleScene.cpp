#include "stdafx.h"
#include "cTitleScene.h"
#include "WINAPI_2D.h"


cTitleScene::cTitleScene()
{
}


void cTitleScene::LoadScene(HINSTANCE hInst, HDC hdc)
{
	// prepare image resources
	bg_title = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	txt1 = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title_text1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	txt2 = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title_text2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	menu1 = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_new.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	menu2_on = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_load_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	menu2_off = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_load_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	menu3 = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_quit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	selector = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


}

//void cTitleScene::UnLoadScene()
//{
//	DeleteObject(bg_title);
//	DeleteObject(txt1);
//	DeleteObject(txt2);
//	DeleteObject(menu1);
//	DeleteObject(menu2_on);
//	DeleteObject(menu2_off);
//	DeleteObject(menu3);
//	DeleteObject(selector);
//	DeleteObject(hbrush);
//}

//
//void cTitleScene::DrawScene(HDC hdc)
//{
//	HDC BackMemDC;
//	HBITMAP hOldBitmap;
//
//	// copy front DC's attributes intto BackMemDC
//	BackMemDC = CreateCompatibleDC(hdc);
//	//make BackMemDC's size properly and select source image onto BackMemDC
//	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);
//
//	{
//		HBITMAP hBit4 = CreateCompatibleBitmap(GetDC(NULL), SCREEN_WIDTH, SCREEN_HEIGHT);
//		hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);
//
//		HDC hMemDC2;
//		hMemDC2 = CreateCompatibleDC(BackMemDC);
//		HBITMAP hOldBitmap2;
//		BITMAP bit;
//		GetObject(bg_title, sizeof(BITMAP), &bit);
//
//		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, bg_title);
//
//		BitBlt(BackMemDC, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC2, 0, 0, SRCCOPY);
//		SelectObject(hMemDC2, hOldBitmap2);
//	}
//
//	DrawSpriteImage(&BackMemDC, 245, 0, &txt1);	// Title
//	DrawSpriteImage(&BackMemDC, 245, 96, &txt2);	// sub Title
//	DrawSpriteImage(&BackMemDC, 600, 390, &menu1);	// menu - start
//
//													// condition flagged as 'true' if there is a save file exists.
//													// according the result, load different image
//													// checker funtion sould be made later.
//	if (0)
//		DrawSpriteImage(&BackMemDC, 600, 450, &menu2_on);	// menu - load (on)
//	else
//		DrawSpriteImage(&BackMemDC, 600, 450, &menu2_off);	// menu - load (off)
//
//	DrawSpriteImage(&BackMemDC, 600, 510, &menu3);	// menu - quit
//
//	static int frameCounter = (TARGET_FPS / CHARACTER_FRAME_MAX) / 2;
//
//	if (frameCounter < 0)
//	{
//		this->curSelectorFrame += 1;
//		frameCounter = (TARGET_FPS / CHARACTER_FRAME_MAX) / 2;
//	}
//	else
//		frameCounter--;
//
//	if (this->curSelectorFrame >(CHARACTER_FRAME_MAX - 1))
//		this->curSelectorFrame = 0;
//
//	DrawSpriteImage(&BackMemDC, 550, 390 + this->GetCurMenu() * 60, &selector, curSelectorFrame);
//
//	DrawToFront(&hdc, &BackMemDC);	// Draw backbuffer DC onto front DC
//
//	SelectObject(BackMemDC, hOldBitmap); // << : 
//	DeleteObject(hOldBitmap);
//	DeleteDC(BackMemDC);
//}
//
//void cTitleScene::ProcessKeyInput(HWND hWnd, WPARAM wParam)
//{
//	switch (wParam)
//	{
//	case VK_UP:
//		if (GetCurMenu() == menuNew)
//			SetCurMenu(menuQuit);
//		else if (GetCurMenu() == menuQuit)
//			if (HaveSaveFile())
//				SetCurMenu(menuLoad);
//			else
//				SetCurMenu(menuNew);
//		else
//			SetCurMenu(menuNew);
//
//		InvalidateRgn(hWnd, NULL, FALSE);
//
//		break;
//	case VK_DOWN:
//		if (GetCurMenu() == menuNew)
//			if (HaveSaveFile())
//				SetCurMenu(menuLoad);
//			else
//				SetCurMenu(menuQuit);
//		else if (GetCurMenu() == menuLoad)
//			SetCurMenu(menuQuit);
//		else
//			SetCurMenu(menuNew);
//
//		InvalidateRgn(hWnd, NULL, FALSE);
//		break;
//	case VK_RETURN:
//		switch (GetCurMenu())
//		{
//		case menuQuit:
//			PostQuitMessage(0);
//			break;
//		case menuNew:
//			UnloadScene();
//			SetCurScene(TownScene);
//		}
//		break;
//	}
//}
//

cTitleScene::~cTitleScene()
{
}
