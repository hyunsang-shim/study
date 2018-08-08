#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::UnLoadScene()
{
	for (int i = 0; i < resources.size(); i++)
		DeleteObject(resources[i]);

	resources.clear();
}

/*
void SceneManager::DrawScene(HDC hdc)
{
	switch (GetCurScene())
	{
	case TitleScene:
	{
		HDC BackMemDC;
			HBITMAP hOldBitmap;

			// copy front DC's attributes intto BackMemDC
			BackMemDC = CreateCompatibleDC(hdc);
			//make BackMemDC's size properly and select source image onto BackMemDC
			//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);

			{
				HBITMAP hBit4 = CreateCompatibleBitmap(GetDC(NULL), SCREEN_WIDTH, SCREEN_HEIGHT);
				hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

				HDC hMemDC2;
				hMemDC2 = CreateCompatibleDC(BackMemDC);
				HBITMAP hOldBitmap2;
				BITMAP bit;
				GetObject(bg_title, sizeof(BITMAP), &bit);

				hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, bg_title);

				BitBlt(BackMemDC, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC2, 0, 0, SRCCOPY);
				SelectObject(hMemDC2, hOldBitmap2);
			}

			DrawSpriteImage(BackMemDC, 245, 0, txt1);	// Title
			DrawSpriteImage(BackMemDC, 245, 96, txt2);	// sub Title
			DrawSpriteImage(BackMemDC, 600, 390, menu1);	// menu - start

															// condition flagged as 'true' if there is a save file exists.
															// according the result, load different image
															// checker funtion sould be made later.
			if (0)
				DrawSpriteImage(BackMemDC, 600, 450, menu2_on);	// menu - load (on)
			else
				DrawSpriteImage(BackMemDC, 600, 450, menu2_off);	// menu - load (off)

			DrawSpriteImage(BackMemDC, 600, 510, menu3);	// menu - quit

			static int frameCounter = (TARGET_FPS / selectorFrameMax) / 2;

			if (frameCounter < 0)
			{
				this->curSelectorFrame += 1;
				frameCounter = (TARGET_FPS / selectorFrameMax) / 2;
			}
			else
				frameCounter--;

			if (this->curSelectorFrame >(selectorFrameMax - 1))
				this->curSelectorFrame = 0;

			DrawSpriteImage(BackMemDC, 550, 390 + this->GetCurMenu() * 60, selector, curSelectorFrame);

			DrawToFront(hdc, BackMemDC);	// Draw backbuffer DC onto front DC

			SelectObject(BackMemDC, hOldBitmap); // << : 
			DeleteObject(hOldBitmap);
			DeleteDC(BackMemDC);
		}
	break;

	}

}
*/
void SceneManager::LoadScene(int destSceneidx)
{
	resources.clear();

	switch (destSceneidx)
	{
	case TitleScene:
		this->SetCurScene(TitleScene);
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\title_text1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\title_text2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\btn_new.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\btn_load_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\btn_load_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\btn_quit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		break;
	case TownScene:
		this->SetCurScene(TownScene);
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));	
		break;
	case BattleScene:
		this->SetCurScene(BattleScene);
		break;
	case GameOverScene:
		this->SetCurScene(GameOverScene);
		break;
	case ShopGym:
		this->SetCurScene(ShopGym);
		break;
	case ShopChurch:
		this->SetCurScene(ShopChurch);
		break;
	case ShopBlacksmith:
		this->SetCurScene(ShopBlacksmith);
		break;
	case ShopGuild:
		this->SetCurScene(ShopGuild);
		break;
	case House:
		this->SetCurScene(House);
		break;
	}

	
}
void SceneManager::ChangeScene(int destSceneidx)
{
	UnLoadScene();
	if (this->GetCurScene() == destSceneidx)
		return;
	else
	{
		switch (destSceneidx)
		{
		case TitleScene:
			this->SetCurScene(TitleScene);
			LoadScene(destSceneidx);
			//DrawScene(hdc);
			break;
		case TownScene:
			this->SetCurScene(TownScene);
			break;
		case BattleScene:
			this->SetCurScene(BattleScene);
			break;
		case GameOverScene:
			this->SetCurScene(GameOverScene);
			break;
		case ShopGym:
			this->SetCurScene(ShopGym);
			break;
		case ShopChurch:
			this->SetCurScene(ShopChurch);
			break;
		case ShopBlacksmith:
			this->SetCurScene(ShopBlacksmith);
			break;
		case ShopGuild:
			this->SetCurScene(ShopGuild);
			break;
		case House:
			this->SetCurScene(House);
			break;
		}

	}

	
}


void  SceneManager::DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src)
{
	HDC BackMemDC;
	HBITMAP hOldBitmap;

	// copy front DC's attributes intto BackMemDC
	BackMemDC = CreateCompatibleDC(destDC);
	//make BackMemDC's size properly and select source image onto BackMemDC
	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);


	HBITMAP hBit4 = CreateCompatibleBitmap(GetDC(NULL), SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

	HDC hMemDC2;
	hMemDC2 = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap2;
	BITMAP bit;
	GetObject(src, sizeof(BITMAP), &bit);

	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, src);

	BitBlt(BackMemDC, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC2, 0, 0, SRCCOPY);
	SelectObject(hMemDC2, hOldBitmap2);

	TransparentBlt(destDC, startX, startY, bit.bmWidth, bit.bmHeight, BackMemDC, 0,0, bit.bmWidth, bit.bmHeight, RGB(255, 0, 255));


	SelectObject(hMemDC2, hOldBitmap2);
	DeleteObject(hOldBitmap2);

	SelectObject(hMemDC2, hBit4);
	DeleteObject(hBit4);


	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);

	DeleteDC(BackMemDC);
	DeleteDC(hMemDC2);
}


void SceneManager::DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber)
{

	HDC hMemDC;
	HBITMAP hOldBitmap;
	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	
	TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE, hMemDC,
		frameNumber * 50, 96, CHARACTER_SIZE, CHARACTER_SIZE,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawToFront(HDC destDC, HDC srcDC)
{
	// Draw image on buffer DC onto front DC
	TransparentBlt(destDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, srcDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
}
