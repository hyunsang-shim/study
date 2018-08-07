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
	
	if (selector == NULL)
		std::cout << "캐릭터가 없어?\n";
}

void cTitleScene::DrawTitleScene(HDC hdc)
{
	// A BackBuffer DC which sotres picture just before draw onto front DC(hdc).
	HDC BackMemDC;
	HBITMAP hOldBitmap;

	// copy front DC's attributes intto BackMemDC
	BackMemDC = CreateCompatibleDC(hdc);
	//make BackMemDC's size properly and select source image onto BackMemDC
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);

	// Draw BG Image (contains no transparent part)
	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SRCCOPY);	

	DeleteObject(hOldBitmap);

	// Draw Menu and title sprite images onto BackBuffer DC
	DrawSpriteImage(BackMemDC, 245, 0, txt1);	// Title
	DrawSpriteImage(BackMemDC, 245, 96, txt2);	// sub Title
	DrawSpriteImage(BackMemDC, 600, 390, menu1);	// menu - start

	// condition flagged as 'true' if there is a save file exists.
	// according the result, load different image
	// checker funtion sould be made later.
	if (1)
		DrawSpriteImage(BackMemDC, 600, 450, menu2_on);	// menu - load (on)
	else
		DrawSpriteImage(BackMemDC, 600, 450, menu2_off);	// menu - load (off)


	DrawSpriteImage(BackMemDC, 600, 510, menu3);	// menu - quit
	
	DrawSpriteAnimation(BackMemDC, 550, 390 + this->GetCurMenu() * 50, selector);

	DrawToFront(hdc, BackMemDC);	// Draw backbuffer DC onto front DC

	DeleteDC(BackMemDC);

}

void  cTitleScene::DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src)
{
	// temporal (to get the size(width and height) of HBITMAP)
	BITMAP bmp;
	HBITMAP hOldBitmap;

	// load on bmp the src(HBITMAP)
	int res = ::GetObject(src, sizeof(BITMAP), (LPVOID)&bmp);
	int sWidth, sHeight;
	sWidth = (int)bmp.bmWidth;  // width of src bitmap
	sHeight = (int)bmp.bmHeight; // height of src bitmap

	// create temporal DC(Device Context)
	HDC tmpDC;
	tmpDC = CreateCompatibleDC(destDC);

	// make temporal DC properly sized.
	hOldBitmap = (HBITMAP)SelectObject(tmpDC, src);

	// draw src onto destDC with it's own size calculated above
	TransparentBlt(destDC, startX, startY, sWidth, sHeight, tmpDC, 0, 0, sWidth, sHeight, RGB(255, 0, 255));

	// delete all temporaly made
	DeleteObject(hOldBitmap);
	DeleteDC(tmpDC);
}

void cTitleScene::DrawSpriteAnimation(HDC destDC, int startX, int startY, HBITMAP src)
{
	static int frameCounter = (TARGET_FPS / selectorFrameMax)/2;
	// create temporal DC(Device Context)
	HDC tmpDC;
	HBITMAP hOldBitmap;
	tmpDC = CreateCompatibleDC(destDC);

	// make temporal DC properly sized.
	hOldBitmap = (HBITMAP)SelectObject(tmpDC, src);


	if (frameCounter < 0)
	{
		curSelectorFrame++;
		frameCounter = (TARGET_FPS / selectorFrameMax) / 2;
	}
	else 
		frameCounter--;


	if (curSelectorFrame > (selectorFrameMax-1))
		curSelectorFrame = 0;


	// draw src onto destDC with it's own size calculated above
	TransparentBlt(destDC, startX, startY, 50, 50, tmpDC, curSelectorFrame *50, 100, 50, 45, RGB(255, 0, 255));

	// delete all temporaly made
	DeleteObject(hOldBitmap);

	DeleteDC(tmpDC);
}

void cTitleScene::DrawToFront(HDC destDC, HDC srcDC)
{
	// Draw image on buffer DC onto front DC
	TransparentBlt(destDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, srcDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

}

cTitleScene::~cTitleScene()
{
}
