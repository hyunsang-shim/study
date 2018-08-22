#pragma once

#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::UnLoadResource()
{
	DeleteObject(resTitle_bg);
	DeleteObject(resTitle_txt1);
	DeleteObject(resTitle_txt1);
	DeleteObject(resTitle_txt2);
	DeleteObject(resTitle_btn1);
	DeleteObject(resTitle_btn2_on);
	DeleteObject(resTitle_btn2_off);
	DeleteObject(resTitle_btn3);
	
	DeleteObject(resTown_bg);
	
	DeleteObject(resBattle_bg);

	DeleteObject(resPC_walk);
	DeleteObject(resPC_shadow);

	DeleteObject(resPC_battle);
	DeleteObject(resPC_face);
	DeleteObject(resMob_face);
	DeleteObject(resBattle_btn_attack_on);
	DeleteObject(resBattle_btn_attack_off);
	DeleteObject(resBattle_btn_defense_on);
	DeleteObject(resBattle_btn_defense_off);

	DeleteObject(resWPN_shortsword);
	DeleteObject(resWPN_shortsword_fx);

	DeleteObject(resMob_rat);
	DeleteObject(resUI_numbers);
	DeleteObject(resUI_hpbar_big);
	DeleteObject(resUI_hpbar_small);


}

void SceneManager::LoadResource()
{
	resTitle_bg = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\BG\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_txt1 = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\title_text1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_txt2 = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\title_text2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_btn1 = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_new.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_btn2_on = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_load_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_btn2_off = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_load_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resTitle_btn3 = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_quit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resTown_bg = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\BG\\town.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resBattle_bg = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\BG\\battle.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resBattle_btn_attack_on = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_attack_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resBattle_btn_attack_off = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_attack_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resBattle_btn_defense_on = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_defense_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resBattle_btn_defense_off = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_defense_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);



	resPC_walk = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resPC_shadow = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\PC_shadow.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resPC_battle = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\PC_battle.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resPC_face = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\PC_face.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resWPN_shortsword = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\weapon\\wpn_shortsword.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resWPN_shortsword_fx = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\weapon\\wpn_shortsword_fx.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resMob_rat = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\Mob_rat.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resMob_face = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\Character\\PC_face.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resUI_numbers = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\ui_numbers.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resUI_hpbar_big = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\ui_hpbar_big.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resUI_hpbar_small = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\ui_hpbar_small.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}

void SceneManager::DrawScene(HDC hdc)
{
	//std::cout << GetCurMenu();

	switch (GetCurScene())
	{
	case TitleScene:
		DrawTitleScene(hdc);
		break;
	case TownScene:
		DrawTownScene(hdc);
		break;
	case BattleScene:
		DrawBattleScene(hdc);
		//DoBattle(hdc);
		break;
	}

}

void SceneManager::ChangeScene(int destSceneidx)
{
		
	switch (destSceneidx)
	{
	case TitleScene:
		SetCurScene(TitleScene);
		SetPC_Direction(FacingRight);
		SetCurMenu(menuNew);
		InvalidateRgn(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), NULL, TRUE);
		break;
	case TownScene:
		SetCurScene(TownScene);
		SetPC_COORD(11, 8);
		SetPC_POS(11, 8);
		SetPC_COORD_NEXT(11, 8);
		SetPC_Direction(FacingUp);
		SetPC_State(Idle);
		InvalidateRgn(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), NULL, TRUE);
		break;
	case BattleScene:
		SetCurScene(BattleScene);
		InitBattleScene();
		break;
	case GameOverScene:
		SetCurScene(GameOverScene);
		break;
	case ShopGym:
		SetCurScene(ShopGym);
		break;
	case ShopChurch:
		SetCurScene(ShopChurch);
		break;
	case ShopBlacksmith:
		SetCurScene(ShopBlacksmith);
		break;
	case ShopGuild:
		SetCurScene(ShopGuild);
		break;
	case House:
		SetCurScene(House);
		break;
	}
	 	
}

void SceneManager::DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP &src)
{
	RECT tmpRect;
	HWND myHwnd = FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길"));
	GetClientRect(myHwnd, &tmpRect);


	GetObject(src, sizeof(BITMAP), &bm);
	
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, startX, startY, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}
void SceneManager::DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP &src, int frameNumber)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
		
	TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, GetDirection_PC() * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);	

}
void SceneManager::DrawSpriteShadow(HDC destDC, int startX, int startY, HBITMAP &src)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, startX, startY + 2, CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, 0, 0, CHARACTER_SIZE, CHARACTER_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

}

void SceneManager::DrawUI_Font(HDC destDC, int startX, int startY, HBITMAP &src, int number)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, startX, startY, UI_FONT_SIZE, UI_FONT_SIZE, hMemDC, number * UI_FONT_SIZE, 0, UI_FONT_SIZE, UI_FONT_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawUI_Portrait(HDC destDC)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int shake_cnt = CHARACTER_FRAME_MAX;
	int shakerX;
	int shakerY;


	hMemDC = CreateCompatibleDC(destDC);

	//draw PC's portrait
	if (GetBattleState_PC() == Hit)
	{
		// PC's portrait w/ shaking effect

		shakerX = rand() % 2 * shake_mid;
		shakerY = rand() % 2 * shake_mid;

		if (!(shake_cnt % 4))
		{
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450 + shakerX, 60 + shakerY, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt--;

			// Mob's portrait w/o shaking effect
			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		}
		else
		{
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt = CHARACTER_FRAME_MAX;

			// Mob's portrait w/o shaking effect
			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		}		
		
	}
	else if (GetBattleState_PC() == Attacking)
	{
		if (!(shake_cnt % 4))
		{
			// PC's portrait w/o shaking effect
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

			// Mob's portrait w/o shaking effect
			shakerX = rand() % 2 * shake_mid;
			shakerY = rand() % 2 * shake_mid;

			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200 + shakerX, 60 + shakerY, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt--;
		}
		else
		{
			// PC's portrait w/o shaking effect
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

			// Mob's portrait w/o shaking effect
			shakerX = rand() % 2 * shake_mid;
			shakerY = rand() % 2 * shake_mid;

			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE-1, RGB(255, 0, 255));
			shake_cnt = CHARACTER_FRAME_MAX;
		}
	}
	else
	{
		shake_cnt = CHARACTER_FRAME_MAX;
		// PC's portrait w/o shaking effect

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
		TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

		// Mob's portrait w/o shaking effect
		SelectObject(hMemDC, resMob_face);
		TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
	}


	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawUI_HPbar(HDC destDC)
{
	double pixelperhp_PC = 0;
	double pixelperhp_MOB = 0;

	pixelperhp_PC = PORTRAIT_SIZE / (double)pc_stat.hp_max;
	pixelperhp_MOB = PORTRAIT_SIZE / (double)mob_stat.hp_max;

	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_hpbar_big);

	TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));	// hpbar bg for pc
	TransparentBlt(destDC, 200, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));// hpbar bg for mob

	//TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG-1, hMemDC, 0, UI_HPBAR_HEIGHT_BIG, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG-1, RGB(255, 0, 255));	// hpbar bg for pc
	
	// hpbar for pc
	TransparentBlt(destDC, 
		450, 60 + PORTRAIT_SIZE + 5, 
		(int)(pixelperhp_PC * pc_stat.hp), UI_HPBAR_HEIGHT_BIG,
		hMemDC, 0, UI_HPBAR_HEIGHT_BIG, 
		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, 
		RGB(255, 0, 255));	

	// hpbar for mob
	TransparentBlt(destDC, 
		200 + (int)(pixelperhp_MOB * abs(mob_stat.hp_max - mob_stat.hp)), 60 + PORTRAIT_SIZE + 5, 
		(int)(pixelperhp_MOB * mob_stat.hp), UI_HPBAR_HEIGHT_BIG, 
		hMemDC, 0, UI_HPBAR_HEIGHT_BIG,
		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG,
		RGB(255, 0, 255));


	// for actor's hpbar
	//SelectObject(hMemDC, resUI_hpbar_small);
	//TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));	// hpbar bg for pc
	//TransparentBlt(destDC, 200, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));// hpbar bg for mob

	//TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, (int)(pixelperhp_PC * pc_stat.hp), 10, hMemDC, 0, 10, UI_HPBAR_WIDTH_BIG, 20, RGB(255, 0, 255));	// hpbar for pc
	//TransparentBlt(destDC, 200 + (int)(pixelperhp_MOB * abs(mob_stat.hp_max - mob_stat.hp)), 60 + PORTRAIT_SIZE + 5, (int)(pixelperhp_MOB * mob_stat.hp), UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 10, PORTRAIT_SIZE, 20, RGB(255, 0, 255));// hpbar for mob

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawFX_PC(HDC destDC, int startX, int startY, HBITMAP &src, int frameNumber)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, startX - FX_WPN_MOD_LEFT, startY - FX_WPN_MOD_UP, FX_WPN_WIDTH, FX_WPN_HEIGHT,
		hMemDC, frameNumber * FX_WPN_WIDTH, 0, FX_WPN_WIDTH, FX_WPN_HEIGHT, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}
void SceneManager::DrawATK_VFX(HDC destDC, int startX, int startY, HBITMAP &src, int frameNumber)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	GetObject(src, sizeof(BITMAP), &bm);		

	TransparentBlt(destDC, startX, startY, FX_VFX_SIZE, FX_VFX_SIZE,
		hMemDC, frameNumber * FX_VFX_SIZE, 0, FX_VFX_SIZE, FX_VFX_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawBattler_PC(HDC destDC, int startX, int startY, HBITMAP &src, int frameNumber)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	if (GetBattleState_PC() == Hit)
	{
		TransparentBlt(destDC, startX, startY, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, hMemDC, frameNumber * CHARACTER_SIZE_BATTLE, GetBattleState_PC() % 4 * CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, RGB(255, 0, 255));
	}
	else
		TransparentBlt(destDC, startX, startY, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, hMemDC, frameNumber * CHARACTER_SIZE_BATTLE, GetBattleState_PC()%4 * CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawBattler_Mob(HDC destDC, int startX, int startY, HBITMAP &src)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;


	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	GetObject(src, sizeof(BITMAP), &bm);

	if (GetBattleState_PC() == Attacking)
	{
		TransparentBlt(destDC, startX, startY, bm.bmWidth, bm.bmHeight - 1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight - 1, RGB(255, 0, 255));
	}
	else
		TransparentBlt(destDC, startX, startY, bm.bmWidth, bm.bmHeight - 1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}


// not use. just for history
/*
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
*/

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
		GetObject(resTitle_bg, sizeof(BITMAP), &bm);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resTitle_bg);

		BitBlt(BackMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC2, 0, 0, SRCCOPY);
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hBit4);
		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);
	}

	DrawSpriteImage(BackMemDC, 210, 0, resTitle_txt1);	// Title
	DrawSpriteImage(BackMemDC, 210, 96, resTitle_txt2);	// sub Title
	DrawSpriteImage(BackMemDC, 600, 400, resTitle_btn1);	// menu - start

													// condition flagged as 'true' if there is a save file exists.
													// according the result, load different image
													// checker funtion sould be made later.
	if (0)
		DrawSpriteImage(BackMemDC, 600, 460, resTitle_btn2_on);	// menu - load (on)
	else
		DrawSpriteImage(BackMemDC, 600, 460, resTitle_btn2_off);	// menu - load (off)

	DrawSpriteImage(BackMemDC, 600, 520, resTitle_btn3);	// menu - quit

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;


	if (framecounter > (CHARACTER_FRAME_MAX * 60))
		framecounter = 0;
	else
		characterFrame = (framecounter / 10) % 4;


	DrawSpriteImage(BackMemDC, 550, 390 + GetCurMenu() * 60, resPC_walk, characterFrame);


	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
	// Draw backbuffer DC onto front DC

	SelectObject(BackMemDC, hOldBitmap); // << : 
	//DeleteObject(hOldBitmap);
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
		GetObject(resTown_bg, sizeof(BITMAP), &bm);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resTown_bg);

		BitBlt(BackMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC2, 0, 0, SRCCOPY);
		SelectObject(hMemDC2, hOldBitmap2);

		DeleteObject(hOldBitmap2);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC2, hBit4);
		DeleteObject(hBit4);
		DeleteDC(hMemDC2);

	}

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;


	if (framecounter > (CHARACTER_FRAME_MAX * 60))
		framecounter = 0;
	else
		characterFrame = (framecounter / 10) % 4;

	DrawSpriteShadow(BackMemDC, PC_POS.x, PC_POS.y, resPC_shadow);
	DrawSpriteImage(BackMemDC, PC_POS.x, PC_POS.y, resPC_walk, characterFrame);

	if (tmpflag ==1)
	{
		for (int row = 0; row < 14; row++)
			for (int col = 0; col < 17; col++)
				if (TownMap[row][col])
					Rectangle(BackMemDC, col * MAPCHIP_SIZE, row * MAPCHIP_SIZE, col * MAPCHIP_SIZE + MAPCHIP_SIZE, row * MAPCHIP_SIZE + MAPCHIP_SIZE - 1);
	}

	// Draw backbuffer DC onto front DC
	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

	SelectObject(BackMemDC, hOldBitmap); // << : 
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);


}

void SceneManager::DrawBattleScene(HDC hdc)
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
		GetObject(resTown_bg, sizeof(BITMAP), &bm);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resBattle_bg);

		BitBlt(BackMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hOldBitmap2);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC2, hBit4);
		DeleteObject(hBit4);
		DeleteDC(hMemDC2);

	}
	
	//for Testing purpose
	if (tmpflag == 1)
	{
		for (int row = 0; row < 14; row++)
			for (int col = 0; col < 17; col++)
				if (BattleMap[row][col])
					Rectangle(BackMemDC, col * MAPCHIP_SIZE, row * MAPCHIP_SIZE, col * MAPCHIP_SIZE + MAPCHIP_SIZE, row * MAPCHIP_SIZE + MAPCHIP_SIZE - 1);
	}

	DoBattle(BackMemDC);
		// Draw backbuffer DC onto front DC
	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
	
	//std::cout << GetPC_COORD().y << " " << GetPC_COORD().x << " " << BattleMap[GetPC_COORD().y][GetPC_COORD().x] << " \n";
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

			InvalidateRgn(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), NULL, FALSE);

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

			InvalidateRgn(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), NULL, FALSE);
			break;
		case VK_RETURN:
			switch (GetCurMenu())
			{
			case menuQuit:
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
				SetPC_Direction(FacingUp);
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
				SetPC_Direction(FacingDown);
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
				SetPC_Direction(FacingLeft);
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
				SetPC_Direction(FacingRight);
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
			ChangeScene(BattleScene);
			break;
		}
		SetEventID(TownMap[PC_COORD.y][PC_COORD.x]);
		//std::cout << "PC Coord (current, next) : (" << PC_COORD.y << "," << PC_COORD.x << "), (" << PC_COORD_NEXT.y << "," << PC_COORD_NEXT.y << "  EventID : " << EventId << "\n";
		break;
	case BattleScene:
		if (GetBattleState_PC() == Ready)
		{
			switch (wParam)
			{
			case VK_LEFT:
				SetCurMenu(menuAttack);
				mob_stat.atk = 1;
				break;
			case VK_RIGHT:
				SetCurMenu(menuDefense);
				mob_stat.atk = 20;
				break;
			case VK_UP:
				pc_stat.hp = pc_stat.hp_max;
				break;
			case VK_SPACE:
				tmpflag *= -1;
				break;
			case VK_ESCAPE:
				ChangeScene(TownScene);
				SetEventID(1);
				break;
			case VK_RETURN:
				SetBattleState_PC(AttackStart);
				break;
			}
			break;
		}
		else if (GetBattleState_PC() == Win)
		{
			switch (wParam)
			{
			case VK_RETURN:
				ChangeScene(TownScene);
				SetEventID(1);
				break;
			case VK_SPACE:
				tmpflag *= -1;
				break;
			}
			break;
		}
		else if ((GetBattleState_PC() == Dead) && (wParam == VK_RETURN))			
				ChangeScene(TitleScene);		
		break;
	}
}

bool SceneManager::PeekNextCoord(POINT CurPos)
{
	// 사각형 충돌 확인 함수(IntersectRect()) 참고 : https://m.blog.naver.com/PostView.nhn?blogId=pok_jadan&logNo=186535496&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
	
	// 다음 row/col 값을 확인하고, 1이면 이동 아니면 제자리	
	switch(GetCurScene())
	{
	case TownScene:
		switch (GetDirection_PC())
		{
		case FacingLeft:
			if (CurPos.x - 1 < 0)
				return false;
			else
				return TownMap[CurPos.y][CurPos.x - 1];
		case FacingRight:
			if (CurPos.x + 1 >= MAP_COL)
				return false;
			else
				return TownMap[CurPos.y][CurPos.x + 1];
		case FacingUp:
			if (CurPos.y - 1 < 0)
				return false;
			else 
				return TownMap[CurPos.y - 1][CurPos.x];
		case FacingDown:
			if (CurPos.y + 1 >= MAP_ROW)
				return false;
			else
				return TownMap[CurPos.y + 1][CurPos.x];
		}
	break;
	case BattleScene:
		switch (GetDirection_PC())
		{
		case FacingLeft:
			if (CurPos.x - 1 < 0)
				return false;
			else
				return BattleMap[CurPos.y][CurPos.x - 1];
		case FacingRight:
			if (CurPos.x + 1 >= MAP_COL)
				return false;
			else
				return BattleMap[CurPos.y][CurPos.x + 1];
		case FacingUp:
			if (CurPos.y - 1 < 0)
				return false;
			else
				return BattleMap[CurPos.y - 1][CurPos.x];
		case FacingDown:
			if (CurPos.y + 1 >= MAP_ROW)
				return false;
			else
				return BattleMap[CurPos.y + 1][CurPos.x];
		}
	break;
	}

	return false;
}

void SceneManager::MoveCharacter(POINT nextPos)
{
	// Move Character from currend coordinate to next coordinate.
	// should ignore input while moving


	int DestX = nextPos.x * 48;
	int DestY = nextPos.y * 48;

	// Set x position
	if (DestX - PC_POS.x > 0)
		PC_POS.x += GetSpeed_PC();
	else if (DestX - PC_POS.x < 0)
		PC_POS.x -= GetSpeed_PC();
	
	// Set y position
	if (DestY - PC_POS.y > 0)
		PC_POS.y += GetSpeed_PC();
	else if (DestY - PC_POS.y < 0)
		PC_POS.y -= GetSpeed_PC();


	// change character status to Idle whel reaches target position.
	if ((PC_POS.x == DestX) && (PC_POS.y == DestY))
	{
		if (GetPC_State() == Moving)
		{
			SetPC_State(Idle);
			SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x);
		}
		else if (GetBattleState_PC() == PrepareAttack)
		{
			SetPC_Direction(FacingLeft);
			SetBattleState_PC(Attacking);
			SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x);
		}
		else if (GetBattleState_PC() == FinishAttack)
		{
			SetBattleState_PC(AttackEnd);
			SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x);
			SetPC_Direction(FacingLeft);
		}
	}


	// TODO : check for event
	//if ((GetPC_COORD().y == 12) && (GetPC_COORD().x == 8))
	if (GetEventID() > 1)
		ChangeScene(EventId);
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

void SceneManager::SetEventID(int eventID)
{
	this->EventId = eventID;
}

int SceneManager::GetEventID()
{
	return EventId;
}

void SceneManager::ShowEvent(int EventId)
{
	switch (EventId)
	{
	case 100://교회
	case 200://대장간
	case 300://길드
	case 400://체육관
	case 500://숙소
		//std::cout << "이벤트 발생!" << std::endl;
		SetEventID(1);
		break;
	case 600://출구
		ChangeScene(BattleScene);
		SetEventID(1);
		break;
	}
}

void SceneManager::drawDamage(HDC destDC, POINT pos, int dmg)
{
	char dmg_to_string[64] = { '\0' };

	_itoa_s(dmg, dmg_to_string, sizeof(dmg_to_string), 10);

	if (damage_font.CurPos.x == damage_font.EndPos.x)
	{
		if (damage_font.CurPos.y == damage_font.EndPos.y)
		{
			dmg_to_string[0] = { '\0' };
			if (GetBattleState_PC() == Hit)
				SetBattleState_PC(Ready);			
		}
	}
	else
	{
		damage_font.CurPos.x++;
		damage_font.CurPos.y--;

		/*printf("start X : %d start y : %d, cur X : %d, cur Y : %d, end X : %d, end Y : %d\n", 
			damage_font.StartPos.x, damage_font.StartPos.y,
			damage_font.CurPos.x, damage_font.CurPos.y,
			damage_font.EndPos.x, damage_font.EndPos.y);
*/

		for (int i = 0; i < sizeof(dmg_to_string); i++)
		{
			//printf("%d : int - [ %d ],string - [ %s ]\n", i, 123, dmg_to_string);
			DrawUI_Font(destDC, damage_font.CurPos.x +i* UI_FONT_SIZE, damage_font.CurPos.y, resUI_numbers, dmg_to_string[i] - 48);
		}

	}

}

void SceneManager::DrawUI(HDC hdc)
{
	switch (GetCurScene())
	{
	case TownScene:
		break;
	case BattleScene:
		if (GetBattleState_PC() == Ready)
			ShowBattleMenu(hdc);

		//draw portraits;
		DrawUI_Portrait(hdc);
		DrawUI_HPbar(hdc);

		break;
	}
}


void SceneManager::DoBattle(HDC BackMemDC)
{

	//std::cout << "GetBattleState_PC : " << GetBattleState_PC() << " curMenu : " << GetCurMenu() << "\n";

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;

	// Sync PC sprite frame to current action.	
	// if action ends -> change state.
	if (framecounter > ((CHARACTER_FRAME_MAX - 1) * 10))
	{
		framecounter = 0;

		if (GetBattleState_PC() == FinishAttack)
			SetBattleState_PC(AttackEnd); 
		else if (GetBattleState_PC() == Attacking)
		{
			SetPC_COORD_NEXT(7, 13);
			SetPC_COORD(7, 13);
			SetBattleState_PC(FinishAttack);
		}
		else if (GetBattleState_PC() == Hit)
		{
			SetBattleState_PC(Ready);
		}
	}
	else
		characterFrame = (framecounter / 10) % 4;


	// variables for damage calculation
	static int damage_to_monster = 0;
	static int damage_to_pc = 0;

	// Draw Player Character's shadow
	DrawSpriteShadow(BackMemDC, PC_POS.x + 8, PC_POS.y + 18, resPC_shadow);
	
	//printf("mob_stat.hp : %d \n", mob_stat.hp);
	DAMAGE_FONT tmp;
	POINT tmp_next;
	
	switch (GetBattleState_PC())
	{
	case Ready:
		// show battle Menu
		if (pc_stat.hp >=0)
			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		else
		{
			SetBattleState_PC(Dead);
			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		}

		// Draw Mob action
		if (mob_stat.hp >= 0)
			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
		break;
	case AttackStart:		
		framecounter = 0;
		// Draw Damage
		// add damage to ui list
		
		tmp_next.x = MOB_POS.x + 30;
		tmp_next.y = MOB_POS.y - 30;

		tmp.EndPos = tmp_next;
		tmp.StartPos = MOB_POS;
		tmp.CurPos = MOB_POS;
		damage_font = tmp;

		// calculate Damage in this turn.
		damage_to_monster = calcDamage(&pc_stat, &mob_stat);
		damage_to_pc = calcDamage(&mob_stat, &pc_stat);

		// for testing
		//printf("start X : %d start y : %d, cur X : %d, cur Y : %d, end X : %d, end Y : %d\n", tmp.StartPos.x, tmp.StartPos.y, tmp.CurPos.x, tmp.CurPos.y, tmp.EndPos.x, tmp.EndPos.y);
		
		if (mob_stat.hp >= 0)
			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);

		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);

		SetBattleState_PC(PrepareAttack);
		SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x - 2);
		SetPC_COORD(GetPC_COORD_NEXT().y, GetPC_COORD_NEXT().x);
		break;
	case PrepareAttack:
		DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
		DrawSpriteShadow(BackMemDC, PC_POS.x, PC_POS.y, resPC_shadow);
		MoveCharacter(GetPC_COORD_NEXT());
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		break;
	case Attacking:
		DrawBattler_Mob(BackMemDC, MOB_POS.x + (-1 * (framecounter % shake_mid)), MOB_POS.y, resMob_rat);
		DrawATK_VFX(BackMemDC, MOB_POS.x, MOB_POS.y, resWPN_shortsword_fx, characterFrame);
		DrawFX_PC(BackMemDC, PC_POS.x, PC_POS.y, resWPN_shortsword, characterFrame);
		drawDamage(BackMemDC, damage_font.StartPos, damage_to_monster);		
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		break;
	case FinishAttack:
		SetPC_Direction(FacingRight);
		DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
		DrawSpriteShadow(BackMemDC, PC_POS.x, PC_POS.y, resPC_shadow);
		MoveCharacter(GetPC_COORD_NEXT());
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);				
		break; 
	case AttackEnd:
		if (mob_stat.hp >= 0)
			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat); 
		DrawFX_PC(BackMemDC, PC_POS.x, PC_POS.y, resWPN_shortsword, characterFrame);
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);

		// set damage font location for PC
		tmp_next.x = PC_POS.x + 30;
		tmp_next.y = PC_POS.y - 30;

		tmp.EndPos = tmp_next;
		tmp.StartPos = PC_POS;
		tmp.CurPos = PC_POS;

		damage_font = tmp; 
		
		if (mob_stat.hp <= 0)
			SetBattleState_PC(Win);
		else if (mob_stat.hp > 0)		
			SetBattleState_PC(Hit);
		break;
	case Hit:
		DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
		DrawBattler_PC(BackMemDC, PC_POS.x + (-1 * (framecounter % shake_mid)), PC_POS.y, resPC_battle, characterFrame);
		// temporal VFX. should be changed later.
		DrawATK_VFX(BackMemDC, PC_POS.x-32, PC_POS.y-32, resWPN_shortsword_fx, characterFrame);		
		drawDamage(BackMemDC, damage_font.StartPos, damage_to_pc);
		break;
	case Win:
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		// temporal VFX. should be changed later.
		TextOut(BackMemDC, 330, 230, _T("전투에서 승리 하였습니다!"), lstrlen(_T("전투에서 승리 하였습니다!")));
		TextOut(BackMemDC, 290, 250, _T("Enter키를 누르면 마을로 돌아갑니다."), lstrlen(_T("Enter키를 누르면 마을로 돌아갑니다.")));
		break;
	case Dead:
		DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
		DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
		TextOut(BackMemDC, 330, 230, _T("전투에서 패배 하였습니다..."), lstrlen(_T("전투에서 패배 하였습니다...")));
		TextOut(BackMemDC, 265, 250, _T("Enter키를 누르면 타이틀 화면으로 돌아갑니다."), lstrlen(_T("Enter키를 누르면 타이틀 화면으로 돌아갑니다.")));
		break;
	}

	DrawUI(BackMemDC);
	
}

void SceneManager::ShowBattleMenu(HDC BackMemDC)
{

	// PC position : 624, 336
	if (GetCurMenu() == menuAttack)
	{
		DrawSpriteImage(BackMemDC, GetPC_POS().x - BATTLE_MENU_SIZE/2 , GetPC_POS().y - BATTLE_MENU_SIZE, resBattle_btn_attack_on);	// attack Menu : on
		DrawSpriteImage(BackMemDC, GetPC_POS().x + BATTLE_MENU_SIZE/2, GetPC_POS().y - BATTLE_MENU_SIZE, resBattle_btn_defense_off);	// Defense Menu : off
	}
	else if (GetCurMenu() == menuDefense)
	{
		DrawSpriteImage(BackMemDC, GetPC_POS().x - BATTLE_MENU_SIZE/2, GetPC_POS().y - BATTLE_MENU_SIZE, resBattle_btn_attack_off);	// attack Menu : on
		DrawSpriteImage(BackMemDC, GetPC_POS().x + BATTLE_MENU_SIZE/2, GetPC_POS().y - BATTLE_MENU_SIZE, resBattle_btn_defense_on);	// Defense Menu : off
	}

}

void SceneManager::InitBattleScene()
{
	SetPC_COORD(7, 13);
	SetPC_POS(7, 13);
	SetPC_COORD_NEXT(7, 13);
	SetPC_Direction(FacingLeft);
	SetPC_State(Idle);
	SetCurMenu(menuAttack);
	SetBattleState_PC(Ready);
	pc_stat = { 10,0,10,20 };
	//mob_stat = { 1,100,0,25, 25 };
	mob_stat = { 1,1,0,25, 25 };
}
