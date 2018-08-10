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
		SetCurScene(TitleScene);
		LoadScene(destSceneidx);
		SetDirection_PC(FacingRight);
		InvalidateRgn(GetMyHWND(), NULL, TRUE);
		break;
	case TownScene:
		SetCurScene(TownScene);
		SetPC_COORD(11, 9);
		SetPC_COORD_NEXT(11, 9);
		SetPC_POS(11, 9);
		LoadScene(destSceneidx);
		SetDirection_PC(FacingUp);
		SetPC_State(Idle);
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

	//>>
	// for testing purpose
	if (GetCurScene() == TownScene && tmpflag >0)
	for (int row = 0; row < 14; row++)
		for (int col = 0; col < 18; col++)
			if (!TownMap[row][col])
			{
				Rectangle(srcDC, col * 48, row * 48, (col + 1) * 48 - 1, (row + 1) * 48 - 1);
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
	
	// 이동 명령이 들어오면
	// if 이동중이면
	//	무시
	// else
	//	해당 방향으로 방향 전환
	//	다음 타일로 이동 진행
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
			if (GetPC_State() == Moving)
			{
				MoveCharacter(GetPC_COORD_NEXT());
				break;
			}
			else
			{
				SetDirection_PC(FacingUp);
				if (PeekNextCoord(PC_COORD))
				{
					SetPC_State(Moving);
					SetPC_COORD_NEXT(PC_COORD.y - 1, PC_COORD.x);
					SetPC_COORD(PC_COORD.y - 1, PC_COORD.x);
					MoveCharacter(GetPC_COORD_NEXT());
				}
				break;
			}
		case VK_DOWN:			
			if (GetPC_State() == Moving)
			{
				MoveCharacter(GetPC_COORD_NEXT());
				break;
			}
			else
			{
				SetDirection_PC(FacingDown);
				if (PeekNextCoord(PC_COORD))
				{
					SetPC_State(Moving);
					SetPC_COORD_NEXT(PC_COORD.y + 1, PC_COORD.x);
					SetPC_COORD(PC_COORD.y + 1, PC_COORD.x);
					MoveCharacter(GetPC_COORD_NEXT());
				}
				break;
			}
		case VK_LEFT:			
			if (GetPC_State() == Moving)
			{
				MoveCharacter(GetPC_COORD_NEXT());
				break;
			}
			else
			{
				SetDirection_PC(FacingLeft);
				if (PeekNextCoord(PC_COORD))
				{
					SetPC_State(Moving);
					SetPC_COORD_NEXT(PC_COORD.y, PC_COORD.x - 1);
					SetPC_COORD(PC_COORD.y, PC_COORD.x - 1);
					MoveCharacter(GetPC_COORD_NEXT());
				}
				break;
			}
		case VK_RIGHT:			
			if (GetPC_State() == Moving)
			{
				MoveCharacter(GetPC_COORD_NEXT());
				break;
			}
			else
			{
				SetDirection_PC(FacingRight);
				if (PeekNextCoord(PC_COORD))
				{
					SetPC_State(Moving);
					SetPC_COORD_NEXT(PC_COORD.y, PC_COORD.x + 1);
					SetPC_COORD(PC_COORD.y, PC_COORD.x + 1);
					MoveCharacter(GetPC_COORD_NEXT());
				}
				break;
			}
		case VK_SPACE:	// for testing purpose
			tmpflag *= -1;
			break;
		}
		break;
	}
}

bool SceneManager::PeekNextCoord(POINT CurPos)
{
	// 사각형 충돌 확인 함수(IntersectRect()) 참고 : https://m.blog.naver.com/PostView.nhn?blogId=pok_jadan&logNo=186535496&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
	
	// 다음 row/col 값을 확인하고, 1이면 이동 아니면 제자리	

	switch (GetDirection_PC())
	{
	case FacingLeft:
		if (CurPos.x - 1 < 0)
			return false;
		else
			return TownMap[CurPos.y][CurPos.x - 1];
	case FacingRight:
		if (CurPos.x + 1 >= TOWN_COL)
			return FALSE;
		else
			return TownMap[CurPos.y][CurPos.x + 1];
	case FacingUp:
		if (CurPos.y - 1 < 0)
			return false;
		else 
			return TownMap[CurPos.y - 1][CurPos.x];
	case FacingDown:
		if (CurPos.y + 1 >= TOWN_ROW)
			return false;
		else
			return TownMap[CurPos.y + 1][CurPos.x];
	}
	
}

void SceneManager::MoveCharacter(POINT nextPos)
{
	//현재 coord에서 다음 coord까지 캐릭터를 이동시킨다.
	//이동 중 입력이 들어오면 무시 되어야 한다.

	// 이동중인 상태일 때만
	int DestX = nextPos.x * 48;
	int DestY = nextPos.y * 48;

	//x좌표값 조정
	if (DestX - PC_POS.x > 0)
		PC_POS.x += GetSpeed_PC();
	else if (DestX - PC_POS.x < 0)
		PC_POS.x -= GetSpeed_PC();
	
	// y좌표값 조정
	if (DestY - PC_POS.y > 0)
		PC_POS.y += GetSpeed_PC();
	else if (DestY - PC_POS.y < 0)
		PC_POS.y -= GetSpeed_PC();


	// 목표 좌표까지 이동 되었으면 상태를 Idle로 전환한다
	if ((PC_POS.x == DestX) && (PC_POS.y == DestY))
	{
		SetPC_State(Idle);
		SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x);
	}


}


void SceneManager::SetPC_POS(int row, int col)
{
	PC_POS.x = col * 48;
	PC_POS.y = row * 48;
}

POINT SceneManager::GetPC_POS()
{
	return PC_POS;
}

void SceneManager::SetPC_COORD(int row, int col)
{
	
	PC_COORD.x = col;
	PC_COORD.y = row;
}

POINT SceneManager::GetPC_COORD()
{
	return PC_COORD;
}

void SceneManager::SetPC_COORD_NEXT(int row, int col)
{
	PC_COORD_NEXT.x = col;
	PC_COORD_NEXT.y = row;
}

POINT SceneManager::GetPC_COORD_NEXT()
{
	return PC_COORD_NEXT;
}
