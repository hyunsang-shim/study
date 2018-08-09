#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::UnloadScene()
{
	for (int i = 0; i < resources.size(); i++)
	{
		SelectObject(GetDC((HWND)GetModuleHandle(NULL)), resources[i]);
		DeleteObject(resources[i]);		
	}

	resources.clear();
}

void SceneManager::LoadScene(int destSceneidx)
{
	resources.clear();

	switch (destSceneidx)
	{
	case TitleScene:
		this->SetCurScene(TitleScene);
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\BG\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\title_text1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\title_text2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\btn_new.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\btn_load_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\btn_load_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\UI\\btn_quit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		break;
	case TownScene:
		this->SetCurScene(TownScene);
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\BG\\town.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		resources.push_back((HBITMAP)LoadImage(GetModuleHandle(NULL), _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		SetDirection_PC(FacingUp);
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

void SceneManager::DrawScene(HDC hdc)
{
	switch (GetCurScene())
	{
	case TitleScene:
		DrawTitleScene(hdc);
		break;
	case TownScene:
		DrawTownScene(hdc);
		break;
	}

}

void SceneManager::ChangeScene(int destSceneidx)
{
	UnloadScene();	
	
	
	switch (destSceneidx)
	{
	case TitleScene:
		this->SetCurScene(TitleScene);
		LoadScene(destSceneidx);
		SetDirection_PC(FacingRight);
		InvalidateRgn(GetMyHWND(), NULL, TRUE);
		break;
	case TownScene:
		this->SetCurScene(TownScene);
		PC_POS.x = 386;
		PC_POS.y = 560;
		LoadScene(destSceneidx);
		SetDirection_PC(FacingUp);
		InvalidateRgn(GetMyHWND(), NULL, TRUE);
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
		frameNumber * 50, GetDirection_PC() * 48, CHARACTER_SIZE, CHARACTER_SIZE-1,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawToFront(HDC destDC, HDC srcDC)
{
	//for town map movement test
	if ((GetCurScene() == TownScene) && tmpflag > 0)
	{
		for (int i = 1; i < 15; i++)
		{
			for (int j = 1; j < 18; j++)
			{
				RECT tmp;

				if (TownMap[i][j])
					SelectObject(srcDC, GetStockObject(HOLLOW_BRUSH));
				else
					SelectObject(srcDC, GetStockObject(WHITE_BRUSH));
				tmp.top = (i-1) * 48;
				tmp.left = (j-1) * 48;
				tmp.bottom = tmp.top + 48;
				tmp.right = tmp.left + 48;
				Rectangle(srcDC, tmp.left, tmp.top, tmp.right, tmp.bottom);
			}
		}
	}


	// Draw image on buffer DC onto front DC
	TransparentBlt(destDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, srcDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
}

void SceneManager::DrawTitleScene(HDC hdc)
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
		GetObject(resources[0], sizeof(BITMAP), &bit);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resources[0]);

		BitBlt(BackMemDC, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC2, 0, 0, SRCCOPY);
		SelectObject(hMemDC2, hOldBitmap2);

		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);


	}

	DrawSpriteImage(BackMemDC, 245, 0, resources[1]);	// Title
	DrawSpriteImage(BackMemDC, 245, 96, resources[2]);	// sub Title
	DrawSpriteImage(BackMemDC, 600, 390, resources[3]);	// menu - start

													// condition flagged as 'true' if there is a save file exists.
													// according the result, load different image
													// checker funtion sould be made later.
	if (0)
		DrawSpriteImage(BackMemDC, 600, 450, resources[4]);	// menu - load (on)
	else
		DrawSpriteImage(BackMemDC, 600, 450, resources[5]);	// menu - load (off)

	DrawSpriteImage(BackMemDC, 600, 510, resources[6]);	// menu - quit

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;


	if (framecounter > (CHARACTER_FRAME_MAX * 12))
		framecounter = 0;
	else
		characterFrame = (framecounter / 4) % 4;


	DrawSpriteImage(BackMemDC, 550, 390 + this->GetCurMenu() * 60, resources[7], characterFrame);

	DrawToFront(hdc, BackMemDC);	// Draw backbuffer DC onto front DC

	SelectObject(BackMemDC, hOldBitmap); // << : 
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);
}

void SceneManager::DrawTownScene(HDC hdc)
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
		GetObject(resources[0], sizeof(BITMAP), &bit);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resources[0]);

		BitBlt(BackMemDC, 0, 0, bit.bmWidth, bit.bmHeight, hMemDC2, 0, 0, SRCCOPY);
		SelectObject(hMemDC2, hOldBitmap2);
		
		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);

	}

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;

	// for testing
	if (framecounter%4 ==3)
		std::cout << "Cur x : " << PC_POS.x << "Y : " << PC_POS.y << "          " << PC_POS.y / 48 << "   " << PC_POS.x/48 << "\n";

	if (framecounter > (CHARACTER_FRAME_MAX * 12))
		framecounter = 0;
	else
		characterFrame = (framecounter / 4) % 4;

	DrawSpriteImage(BackMemDC, PC_POS.x, PC_POS.y, resources[1], characterFrame);

	DrawToFront(hdc, BackMemDC);	// Draw backbuffer DC onto front DC

	SelectObject(BackMemDC, hOldBitmap); // << : 
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);


}

void SceneManager::KeyInput(WPARAM wParam)
{
	switch (GetCurScene())
	{
	case TitleScene:
		switch (wParam)
		{
		case VK_UP:
			if (GetCurMenu() == menuNew)
				SetCurMenu(menuQuit);
			else if (GetCurMenu() == menuQuit)
				if (HaveSaveFile())
					SetCurMenu(menuLoad);
				else
					SetCurMenu(menuNew);
			else
				SetCurMenu(menuNew);

			InvalidateRgn(GetMyHWND(), NULL, FALSE);

			break;
		case VK_DOWN:
			if (GetCurMenu() == menuNew)
				if (HaveSaveFile())
					SetCurMenu(menuLoad);
				else
					SetCurMenu(menuQuit);
			else if (GetCurMenu() == menuLoad)
				SetCurMenu(menuQuit);
			else
				SetCurMenu(menuNew);

			InvalidateRgn(GetMyHWND(), NULL, FALSE);
			break;
		case VK_RETURN:
			switch (GetCurMenu())
			{
			case menuQuit:
				UnloadScene();
				PostQuitMessage(0);
				break;
			case menuNew:
				ChangeScene(TownScene);
			}
			break;
		}
		break;
	case TownScene:
		switch (wParam)
		{
		case VK_ESCAPE:
			ChangeScene(TitleScene);			
			break;
		case VK_UP:
			SetDirection_PC(FacingUp);
		case VK_DOWN:			
			SetDirection_PC(FacingDown);			
			break;
		case VK_LEFT:			
			SetDirection_PC(FacingLeft);
			break;
		case VK_RIGHT:			
			SetDirection_PC(FacingRight);
			break;
		case VK_SPACE:
			tmpflag *= -1;
		}
		
		break;
	}
}

bool SceneManager::PeekNextPlace(POINT nextPos)
{
	POINT tmp = nextPos;
	/*
	다음 좌표값 -> 맵칩 사이즈로 나눈걸로 배열 찾아서
	값을 리턴시킨다.	
	*/

	switch (GetDirection_PC())
	{
	case FacingRight:
		tmp.x += CHARACTER_SIZE;
		break;
	case FacingDown:
		tmp.y += CHARACTER_SIZE;
		break;
	}
	
	switch (GetCurScene())
	{
	case TownScene:
		return TownMap[(tmp.y) / 48][(tmp.x) / 48];
		break;
	}
}

