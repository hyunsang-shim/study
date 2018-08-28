#pragma once

class cManager;
#include "stdafx.h"
#include "SceneManager.h"
#include "cManager.h"


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
	DeleteObject(resUI_Battlemsg);


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
	resUI_Battlemsg = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\ui_msgbox.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}

void SceneManager::DrawBG(HDC destDC, HBITMAP &src)
{
	RECT tmpRect;

	GetClientRect(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), &tmpRect);
	//GetClientRect(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), &tmpRect);

	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	BitBlt(destDC, 0, 0, tmpRect.right, tmpRect.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawUI_Image(HDC destDC, POINT &point, HBITMAP &src)
{
	RECT tmpRect;
	GetClientRect(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), &tmpRect);
	
	GetObject(src, sizeof(BITMAP), &bm);
	
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, point.x, point.y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}
void SceneManager::DrawUI_SpriteImage(HDC destDC, POINT &point, HBITMAP &src, int width, int height, int frameNumber, bool isVertical)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	GetObject(resUI_Battlemsg, sizeof(BITMAP), &bm);

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	if (isVertical)
		TransparentBlt(destDC, point.x, point.y, width, height - 1, hMemDC, 0, frameNumber * height, width, height - 1, RGB(255, 0, 255));	
	else
		TransparentBlt(destDC, point.x, point.y, width, height - 1, hMemDC, frameNumber * width, 0, width, height - 1, RGB(255, 0, 255));
	//TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, 1 * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawUI_Selector(HDC destDC, POINT &point, HBITMAP &src, int &frameNumber, int &direction)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
		
	TransparentBlt(destDC, point.x, point.y, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, direction * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));
	//TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, 1 * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);	

}
void SceneManager::DrawActor_PC_Shadow(HDC destDC, int &start_x, int &start_y, HBITMAP src)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, start_x, start_y + 2, CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, 0, 0, CHARACTER_SIZE, CHARACTER_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

}

void SceneManager::DrawUI_Font(HDC destDC, int startX, int startY, HBITMAP src, int number)
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
void SceneManager::DrawUI_Portrait(HDC destDC, int &player_battlestate, int &monster_battlestate)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int shake_cnt = CHARACTER_FRAME_MAX;
	int shakerX;
	int shakerY;


	hMemDC = CreateCompatibleDC(destDC);

	//draw PC's portrait
	//if (GetBattleState_PC() == Hit)
	switch (player_battlestate)
	{
	case Player_Hit:
		// PC's portrait w/ shaking effect

		shakerX = rand() % 2 * shake_mid;
		shakerY = rand() % 2 * shake_mid;

		if (!(shake_cnt % 4))
		{
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450 + shakerX, 60 + shakerY, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, player_battlestate * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt--;

			// Mob's portrait w/o shaking effect
			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 1 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		}
		else
		{
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, player_battlestate * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt = CHARACTER_FRAME_MAX;

			// Mob's portrait w/o shaking effect
			SelectObject(hMemDC, resMob_face);
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 1 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		}
		break;
	case Player_Attacking:
		if (!(shake_cnt % 4))
		{
			// PC's portrait w/o shaking effect
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			//TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, player_battlestate * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

			// Mob's portrait w/o shaking effect
			shakerX = rand() % 2 * shake_mid;
			shakerY = rand() % 2 * shake_mid;

			SelectObject(hMemDC, resMob_face);
			//TransparentBlt(destDC, 200 + shakerX, 60 + shakerY, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			TransparentBlt(destDC, 200 + shakerX, 60 + shakerY, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 2 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt--;
		}
		else
		{
			// PC's portrait w/o shaking effect
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
			//TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 1 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

			// Mob's portrait w/o shaking effect
			shakerX = rand() % 2 * shake_mid;
			shakerY = rand() % 2 * shake_mid;

			SelectObject(hMemDC, resMob_face);
			//TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE-1, RGB(255, 0, 255));
			TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 1 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
			shake_cnt = CHARACTER_FRAME_MAX;
		}
		break;
	default:
		shake_cnt = CHARACTER_FRAME_MAX;
		// PC's portrait w/o shaking effect

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_face);
		//TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, (GetBattleState_PC() % 5) * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		TransparentBlt(destDC, 450, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, player_battlestate * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));

		// Mob's portrait w/o shaking effect
		SelectObject(hMemDC, resMob_face);
		//TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, GetBattleState_Mob() * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		TransparentBlt(destDC, 200, 60, PORTRAIT_SIZE, PORTRAIT_SIZE, hMemDC, 1 * PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE - 1, RGB(255, 0, 255));
		break;
	}


	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawUI_HPbar(HDC destDC, STATUS_PC *PC, STATUS_MOB *MOB)
{
	double pixelperhp_PC = 0;
	double pixelperhp_MOB = 0;

	//pixelperhp_PC = PORTRAIT_SIZE / (double)pc_stat.hp_max);
	//pixelperhp_MOB = PORTRAIT_SIZE / (double)mob_stat.hp_max;
	pixelperhp_PC = PORTRAIT_SIZE / (double)PC->hp_max;
	pixelperhp_MOB = PORTRAIT_SIZE / (double)MOB->hp_max;

	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_hpbar_big);

	TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));	// hpbar bg for pc
	TransparentBlt(destDC, 200, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, hMemDC, 0, 0, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, RGB(255, 0, 255));// hpbar bg for mob

	//TransparentBlt(destDC, 450, 60 + PORTRAIT_SIZE + 5, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG-1, hMemDC, 0, UI_HPBAR_HEIGHT_BIG, UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG-1, RGB(255, 0, 255));	// hpbar bg for pc
	
	// hpbar for pc
	//TransparentBlt(destDC, 		450, 60 + PORTRAIT_SIZE + 5, 		(int)(pixelperhp_PC * pc_stat.hp), UI_HPBAR_HEIGHT_BIG,		hMemDC, 0, UI_HPBAR_HEIGHT_BIG, 		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG, 		RGB(255, 0, 255));	
	TransparentBlt(destDC,
		450, 60 + PORTRAIT_SIZE + 5,
		(int)(pixelperhp_PC * PC->hp_max), UI_HPBAR_HEIGHT_BIG,
		hMemDC, 
		0, UI_HPBAR_HEIGHT_BIG,
		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG,
		RGB(255, 0, 255));	

	TCHAR tmp[64] = { '\0' };

	wsprintf(tmp, _T("HP : %d / %d"), PC->hp, PC->hp_max );

	TextOut(destDC, 450, 60 + PORTRAIT_SIZE + UI_HPBAR_HEIGHT_BIG + 10, tmp, lstrlen(tmp));


	// hpbar for mob
	//TransparentBlt(destDC, 		200 + (int)(pixelperhp_MOB * abs(mob_stat.hp_max - mob_stat.hp)), 60 + PORTRAIT_SIZE + 5, 		(int)(pixelperhp_MOB * mob_stat.hp), UI_HPBAR_HEIGHT_BIG, 		hMemDC, 0, UI_HPBAR_HEIGHT_BIG,		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG,		RGB(255, 0, 255));
	TransparentBlt(destDC,
		200 + PORTRAIT_SIZE - (int)(pixelperhp_MOB * MOB->hp),	60 + PORTRAIT_SIZE + 5, 
		(int)(pixelperhp_MOB * MOB->hp), UI_HPBAR_HEIGHT_BIG,
		hMemDC,
		0, UI_HPBAR_HEIGHT_BIG,		
		UI_HPBAR_WIDTH_BIG, UI_HPBAR_HEIGHT_BIG,
		RGB(255, 0, 255));

	wsprintf(tmp, _T("HP : %d / %d"), MOB->hp, MOB->hp_max);

	TextOut(destDC, 200, 60 + PORTRAIT_SIZE + UI_HPBAR_HEIGHT_BIG + 10, tmp, lstrlen(tmp));

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

void SceneManager::DrawFX_PC(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber)
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
void SceneManager::DrawATK_VFX(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber)
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
void SceneManager::DrawBattler_PC(HDC destDC, STATUS_PC *status_pc, HBITMAP src, int frameNumber)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	//if (GetBattleState_PC() == Hit)
	if (status_pc->battlestate == Player_Hit)
	{
		TransparentBlt(destDC, status_pc->pos_x, status_pc->pos_y, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, hMemDC, frameNumber * CHARACTER_SIZE_BATTLE, status_pc->battlestate%4 * CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, RGB(255, 0, 255));
	}
	else
		TransparentBlt(destDC, status_pc->pos_x, status_pc->pos_y, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, hMemDC, frameNumber * CHARACTER_SIZE_BATTLE, status_pc->battlestate % 4 * CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawActor_PC(HDC destDC, int &start_x, int &start_y, HBITMAP &src, int &frameNumber, int &facing)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	TransparentBlt(destDC, start_x, start_y, CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, frameNumber * CHARACTER_SIZE, facing * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));
	//TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, 1 * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}
void SceneManager::DrawBattler_Mob(HDC destDC, int startX, int startY, HBITMAP src)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;


	hMemDC = CreateCompatibleDC(destDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);

	GetObject(src, sizeof(BITMAP), &bm);

	//if (GetBattleState_PC() == Attacking)
	if (GAME_MANAGER->GetStatus_MOB().battlestate == Monster_Attack_Move)
	{
		TransparentBlt(destDC, startX, startY, bm.bmWidth, bm.bmHeight - 1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight - 1, RGB(255, 0, 255));
	}
	else
		TransparentBlt(destDC, startX, startY, bm.bmWidth, bm.bmHeight - 1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}

void SceneManager::DrawTitleScene(HDC hdc, int &CurMenu, int &PC_Direction)
{
	HDC BackMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);
	
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));

	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);	

	DeleteObject(hBit4);
	
	DrawBG(BackMemDC, resTitle_bg);
/*
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));

	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);

	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);

	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

		DeleteObject(hBit4);

		HDC hMemDC2;
		hMemDC2 = CreateCompatibleDC(BackMemDC);
		HBITMAP hOldBitmap2;
		GetObject(resTitle_bg, sizeof(BITMAP), &bm);

		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resTitle_bg);

		BitBlt(BackMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteObject(hOldBitmap2);
		DeleteDC(hMemDC2);
		*/

		DrawUI_Image(BackMemDC, title1, resTitle_txt1);	// Title
		DrawUI_Image(BackMemDC, title2, resTitle_txt2);	// sub Title
		DrawUI_Image(BackMemDC, btn1, resTitle_btn1);	// menu - start

													// condition flagged as 'true' if there is a save file exists.
													// according the result, load different image
													// checker funtion sould be made later.
	if (0)
		DrawUI_Image(BackMemDC, btn2, resTitle_btn2_on);	// menu - load (on)
	else
		DrawUI_Image(BackMemDC, btn2, resTitle_btn2_off);	// menu - load (off)

	DrawUI_Image(BackMemDC, btn3, resTitle_btn3);	// menu - quit

	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;
	
	if (framecounter > (CHARACTER_FRAME_MAX * 60))
		framecounter = 0;
	else
		characterFrame = (framecounter / 10) % 4;

	selector.y = 390 + CurMenu * 60;
	DrawUI_Selector(BackMemDC, selector, resPC_walk, characterFrame, PC_Direction);

	// Draw backbuffer DC onto front DC
	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
	//SelectObject(BackMemDC, hOldBitmap); // << : 
	//DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);


}

void SceneManager::DrawTownScene(HDC hdc, STATUS_PC *status_pc)
{
	HDC BackMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);

	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));

	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);

	DeleteObject(hBit4);

	DrawBG(BackMemDC, resTown_bg);


	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;


	if (framecounter > (CHARACTER_FRAME_MAX * 60))
		framecounter = 0;
	else
		characterFrame = (framecounter / 10) % 4;

	DrawActor_PC_Shadow(BackMemDC, status_pc->pos_x, status_pc->pos_y, resPC_shadow);
	DrawActor_PC(BackMemDC, status_pc->pos_x, status_pc->pos_y, resPC_walk, characterFrame, status_pc->facing);

	if (tmpflag ==1)
	{
		//for (int row = 0; row < 14; row++)
			//for (int col = 0; col < 17; col++)
				//if (TownMap[row][col])
				//	Rectangle(BackMemDC, col * MAPCHIP_SIZE, row * MAPCHIP_SIZE, col * MAPCHIP_SIZE + MAPCHIP_SIZE, row * MAPCHIP_SIZE + MAPCHIP_SIZE - 1);

	}

	// Draw backbuffer DC onto front DC
	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

	SelectObject(BackMemDC, hOldBitmap); // << : 
	DeleteDC(BackMemDC);

}

void SceneManager::DrawBattleScene(HDC hdc, int &battleState, STATUS_PC *status_pc, STATUS_MOB *status_mob)
{
	HDC BackMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);

	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));

	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);

	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);

	DeleteObject(hBit4);

	// Draw Background Image
	DrawBG(BackMemDC, resBattle_bg);


	// for resource's frame
	static int framecounter = 0;
	static int characterFrame = 0;
	framecounter++;


	// Sync PC sprite frame to current action.	
	// if action ends -> change state.
	if (framecounter > ((CHARACTER_FRAME_MAX - 1) * 10))
	{
		framecounter = 0;
	
		if (status_pc->battlestate == Player_Return_Move)
			status_pc->battlestate = Player_Wait;
		else if (status_pc->battlestate == Player_Attacking)
		{
			GAME_MANAGER->SetBattleState(Battle_Wait);
			GAME_MANAGER->ApplyDamage(status_mob, GAME_MANAGER->GetBattleMessage().damage);
			status_pc->battlestate = Player_WaitAttackMessage;
		}
		else if (status_pc->battlestate == Player_Hit)
		{
			status_pc->battlestate = Player_Ready;
		}
		else if (status_pc->battlestate == Player_Attack_Move)
			status_pc->battlestate = Player_Attacking;
	}
	else
		characterFrame = (framecounter / 10) % 4;


	// Draw Player Character
	DrawBattler_PC(BackMemDC, status_pc, resPC_battle, characterFrame);

	// Draw Portraits
	DrawUI_Portrait(BackMemDC, status_pc->battlestate, status_mob->battlestate);

	// Draw HP_Bars
	DrawUI_HPbar(BackMemDC, status_pc, status_mob);


	// Draw Battle Message Box
	if (GAME_MANAGER->GetBattleState() == Battle_PlayerAttackResult)
	{
		

		POINT MSGBOX_startpos = { 42,460 };

		static int frame = 0;
		// Sync PC sprite frame to current action.	
		// if action ends -> change state.
		if (frame/2 < 4)
		{			
			DrawUI_SpriteImage(BackMemDC, MSGBOX_startpos, resUI_Battlemsg, MSG_BOX_WIDTH, MSG_BOX_HEIGHT, frame/2, true);
			frame++;
		}
		else
		{
			DrawUI_SpriteImage(BackMemDC, MSGBOX_startpos, resUI_Battlemsg, MSG_BOX_WIDTH, MSG_BOX_HEIGHT, frame/2, true);
			GAME_MANAGER->SetUI_state_MSGW(TRUE);			
		}

		if (GAME_MANAGER->GetUI_state_MSGW())
			ShowMessage(BackMemDC);

	}

	if (GAME_MANAGER->GetBattleMessage().damage != 0)
	{
		int damage = GAME_MANAGER->GetBattleMessage().damage;
		drawDamage(BackMemDC, damage_font, damage);
	}
	// Draw backbuffer DC onto front DC
	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

	SelectObject(BackMemDC, hOldBitmap); // << : 
	DeleteDC(BackMemDC);

}

//
//void SceneManager::DrawBattleScene(HDC hdc, int &BattleState_PC)
//{
//	HDC BackMemDC;
//	HBITMAP hOldBitmap;
//
//	// copy front DC's attributes intto BackMemDC
//	BackMemDC = CreateCompatibleDC(hdc);
//	//make BackMemDC's size properly and select source image onto BackMemDC
//	//hOldBitmap = (HBITMAP)SelectObject(BackMemDC, bg_title);
//
//	
//		HBITMAP hBit4 = CreateCompatibleBitmap(GetDC(NULL), SCREEN_WIDTH, SCREEN_HEIGHT);
//		hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit4);
//
//		HDC hMemDC2;
//		hMemDC2 = CreateCompatibleDC(BackMemDC);
//		HBITMAP hOldBitmap2;
//		GetObject(resTown_bg, sizeof(BITMAP), &bm);
//
//		DeleteObject(hBit4);
//		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, resBattle_bg);
//
//		BitBlt(BackMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC2, 0, 0, SRCCOPY);
//
//		SelectObject(hMemDC2, hOldBitmap2);		
//		DeleteDC(hMemDC2);
//	
//	
//	//for Testing purpose
//	/*if (tmpflag == 1)
//	{
//		for (int row = 0; row < 14; row++)
//			for (int col = 0; col < 17; col++)
//				if (BattleMap[row][col])
//					Rectangle(BackMemDC, col * MAPCHIP_SIZE, row * MAPCHIP_SIZE, col * MAPCHIP_SIZE + MAPCHIP_SIZE, row * MAPCHIP_SIZE + MAPCHIP_SIZE - 1);
//	}*/
//
//	//DoBattle(BackMemDC);
//
//	//std::cout << "GetBattleState_PC : " << GetBattleState_PC() << " curMenu : " << CurMenu << "\n";
//
//		static int framecounter = 0;
//		static int characterFrame = 0;
//		framecounter++;
//
//		// Sync PC sprite frame to current action.	
//		// if action ends -> change state.
//		if (framecounter > ((CHARACTER_FRAME_MAX - 1) * 10))
//		{
//			framecounter = 0;
//
//			if (BattleState_PC == FinishAttack)
//				BattleState_PC = AttackEnd;
//			else if (BattleState_PC == Attacking)
//			{
//
//				PC_COORD = PC_COORD_NEXT = { 13, 7 };
//				BattleState_PC = FinishAttack;
//				//SetBattleState_PC(WaitForMessage);
//			}
//			else if (BattleState_PC == Hit)
//			{
//				BattleState_PC = Ready;
//			}
//		}
//		else
//			characterFrame = (framecounter / 10) % 4;
//
//
//	// Draw Player Character's shadow
//		DrawActor_PC_Shadow(BackMemDC, PC_XY_SHADOW, resPC_shadow);
//
//		//printf("mob_stat.hp : %d \n", mob_stat.hp);
//		DAMAGE_FONT tmp;
//		POINT tmp_next;
//
//		// Main process
//		//do something about pc's current action state
//		switch (GetBattleState_PC())
//		{
//		case Ready:
//			// show battle Menu
//			if (pc_stat.hp >= 0)
//				DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//			else
//			{
//				SetBattleState_PC(Dead);
//				DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//			}
//
//			// Draw Mob action
//			if (mob_stat.hp >= 0)
//				DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			break;
//		case AttackStart:
//			framecounter = 0;
//			// Draw Damage
//			// add damage to ui list
//
//			tmp_next.x = MOB_POS.x + 30;
//			tmp_next.y = MOB_POS.y - 30;
//
//			tmp.EndPos = tmp_next;
//			tmp.StartPos = MOB_POS;
//			tmp.CurPos = MOB_POS;
//			damage_font = tmp;
//
//			// calculate Damage in this turn.
//			damage_to_monster = calcDamage(&pc_stat, &mob_stat);
//			damage_to_pc = calcDamage(&mob_stat, &pc_stat);
//
//			// for testing
//			//printf("start X : %d start y : %d, cur X : %d, cur Y : %d, end X : %d, end Y : %d\n", tmp.StartPos.x, tmp.StartPos.y, tmp.CurPos.x, tmp.CurPos.y, tmp.EndPos.x, tmp.EndPos.y);
//
//			if (mob_stat.hp >= 0)
//				DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//
//			SetBattleState_PC(PrepareAttack);
//			SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x - 2);
//			SetPC_COORD(GetPC_COORD_NEXT().y, GetPC_COORD_NEXT().x);
//			break;
//		case PrepareAttack:
//			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			DrawSpriteShadow(BackMemDC, PC_POS.x, PC_POS.y, resPC_shadow);
//			MoveCharacter(GetPC_COORD_NEXT());
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//
//			// PC arrived. go to next step
//			if ((PC_POS.x == (GetPC_COORD_NEXT().x) * 48) && (PC_POS.y == (GetPC_COORD_NEXT().y) * 48))
//				SetBattleState_PC(Attacking);
//			break;
//		case Attacking:
//			DrawBattler_Mob(BackMemDC, MOB_POS.x + (-1 * (framecounter % shake_mid)), MOB_POS.y, resMob_rat);
//			DrawATK_VFX(BackMemDC, MOB_POS.x, MOB_POS.y, resWPN_shortsword_fx, characterFrame);
//			DrawFX_PC(BackMemDC, PC_POS.x, PC_POS.y, resWPN_shortsword, characterFrame);
//			drawDamage(BackMemDC, damage_font.StartPos, damage_to_monster);
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//			break;
//		case FinishAttack:
//			SetPC_Direction(FacingRight);
//			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			DrawSpriteShadow(BackMemDC, PC_POS.x, PC_POS.y, resPC_shadow);
//			MoveCharacter(GetPC_COORD_NEXT());
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//
//			if ((PC_POS.x == (GetPC_COORD_NEXT().x) * 48) && (PC_POS.y == (GetPC_COORD_NEXT().y) * 48))
//				SetBattleState_PC(AttackEnd);
//			break;
//		case AttackEnd:
//			if (mob_stat.hp >= 0)
//				DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			DrawFX_PC(BackMemDC, PC_POS.x, PC_POS.y, resWPN_shortsword, characterFrame);
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//
//			// set damage font location for PC
//			tmp_next.x = PC_POS.x + 30;
//			tmp_next.y = PC_POS.y - 30;
//
//			tmp.EndPos = tmp_next;
//			tmp.StartPos = PC_POS;
//			tmp.CurPos = PC_POS;
//
//			damage_font = tmp;
//
//			if (mob_stat.hp <= 0)
//				SetBattleState_PC(Win);
//			else if (mob_stat.hp > 0)
//				SetBattleState_PC(Hit);
//			break;
//		case Hit:
//			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			DrawBattler_PC(BackMemDC, PC_POS.x + (-1 * (framecounter % shake_mid)), PC_POS.y, resPC_battle, characterFrame);
//			// temporal VFX. should be changed later.
//			DrawATK_VFX(BackMemDC, PC_POS.x - 32, PC_POS.y - 32, resWPN_shortsword_fx, characterFrame);
//			drawDamage(BackMemDC, damage_font.StartPos, damage_to_pc);
//			break;
//		case Win:
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//			// temporal VFX. should be changed later.
//			TextOut(BackMemDC, 330, 230, _T("전투에서 승리 하였습니다!"), lstrlen(_T("전투에서 승리 하였습니다!")));
//			TextOut(BackMemDC, 290, 250, _T("Enter키를 누르면 마을로 돌아갑니다."), lstrlen(_T("Enter키를 누르면 마을로 돌아갑니다.")));
//			break;
//		case Dead:
//			DrawBattler_Mob(BackMemDC, MOB_POS.x, MOB_POS.y, resMob_rat);
//			DrawBattler_PC(BackMemDC, PC_POS.x, PC_POS.y, resPC_battle, characterFrame);
//			TextOut(BackMemDC, 330, 230, _T("전투에서 패배 하였습니다..."), lstrlen(_T("전투에서 패배 하였습니다...")));
//			TextOut(BackMemDC, 265, 250, _T("Enter키를 누르면 타이틀 화면으로 돌아갑니다."), lstrlen(_T("Enter키를 누르면 타이틀 화면으로 돌아갑니다.")));
//			break;
//		}
//
//		DrawUI(BackMemDC);
//
//		// Draw backbuffer DC onto front DC
//	TransparentBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));
//	
//	//std::cout << GetPC_COORD().y << " " << GetPC_COORD().x << " " << BattleMap[GetPC_COORD().y][GetPC_COORD().x] << " \n";
//	SelectObject(BackMemDC, hOldBitmap); // << : 
//	DeleteObject(hOldBitmap);
//	DeleteDC(BackMemDC);
//
//}


void SceneManager::MoveCharacter(POINT nextPos)
{
	// Move Character from currend coordinate to next coordinate.
	// should ignore input while moving


	//int DestX = nextPos.x * 48;
	//int DestY = nextPos.y * 48;

	//// Set x position
	//if (DestX - PC_POS.x > 0)
	//	PC_POS.x += GetSpeed_PC();
	//else if (DestX - PC_POS.x < 0)
	//	PC_POS.x -= GetSpeed_PC();
	//
	//// Set y position
	//if (DestY - PC_POS.y > 0)
	//	PC_POS.y += GetSpeed_PC();
	//else if (DestY - PC_POS.y < 0)
	//	PC_POS.y -= GetSpeed_PC();


	//// change character status to Idle whel reaches target position.
	//if ((PC_POS.x == DestX) && (PC_POS.y == DestY))
	//{
	//	if (GetPC_State() == Moving)
	//	{
	//		SetPC_State(Idle);
	//		SetPC_COORD_NEXT(GetPC_COORD().y, GetPC_COORD().x);
	//	}
	//	else if (GetBattleState_PC() == PrepareAttack)
	//	{
	//		SetPC_Direction(FacingLeft);
	//		SetBattleState_PC(Attacking);
	//	}
	//	else if (GetBattleState_PC() == FinishAttack)
	//	{
	//		SetBattleState_PC(AttackEnd);
	//		//SetBattleState_PC(WaitForMessage);
	//		SetPC_Direction(FacingLeft);
	//	}
	//}


	//// TODO : check for event
	////if ((GetPC_COORD().y == 12) && (GetPC_COORD().x == 8))
	//if (GetEventID() > 1)
	//	ChangeScene(GetEventID());
}

void SceneManager::ShowEvent(int EventId)
{
	//switch (EventId)
	//{
	//case 100://교회
	//case 200://대장간
	//case 300://길드
	//case 400://체육관
	//case 500://숙소
	//	//std::cout << "이벤트 발생!" << std::endl;
	//	SetEventID(1);
	//	break;
	//case 600://출구
	//	ChangeScene(BattleScene);
	//	SetEventID(1);
	//	break;
	//}
}

void SceneManager::ShowMessage(HDC BackMemDC)
{

	static int nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
	static int nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);
	static int nLen_BattleResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage);


	if (nLen_AttackMessage-- >= 0)
		TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage) - nLen_AttackMessage);
	else if (nLen_AttackResultMessage-- >= 0)
	{
		TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
		TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage) - nLen_AttackResultMessage);
	}
	else if (nLen_BattleResultMessage-- >= 0 && GAME_MANAGER->GetStatus_MOB().hp <= 0)
	{
		TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
		TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));
		TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage) - nLen_BattleResultMessage);
	}
	else
	{
		TextOut(BackMemDC, 58, 472,_T("잇힝?"), lstrlen(_T("잇힝?")));

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

void SceneManager::DrawUI(HDC destDc)
{

	if (GAME_MANAGER->GetStatus_PC().battlestate == Player_Wait)
	{


		static int framecounter = 0;
		static int frame = 0;

		POINT MSGBOX_startpos = { 42,483 };

		frame = framecounter % 3;
		// Sync PC sprite frame to current action.	
		// if action ends -> change state.
		if (frame == 0)
		{
			framecounter++;
			DrawUI_SpriteImage(destDc, MSGBOX_startpos, resUI_Battlemsg, MSG_BOX_WIDTH, MSG_BOX_HEIGHT, frame, true);
		}
	}
	//switch (GetCurScene())
	//{
	//case TownScene:
	//	break;
	//case BattleScene:
	//	if (GetBattleState_PC() == Ready)
	//		ShowBattleMenu(hdc);

	//	//draw portraits;
	//	DrawUI_Portrait(hdc);
	//	DrawUI_HPbar(hdc);

	//	break;
	//}
}


void SceneManager::ShowBattleMenu(HDC BackMemDC, STATUS_PC *status_pc)
{
	POINT menu1, menu2;
	menu1.x = status_pc->pos_x - BATTLE_MENU_SIZE/2;
	menu1.y = status_pc->pos_y - BATTLE_MENU_SIZE;

	menu2.x = status_pc->pos_x + BATTLE_MENU_SIZE / 2;
	menu2.y = status_pc->pos_y - BATTLE_MENU_SIZE;


	////// PC position : 624, 336
	switch (GAME_MANAGER->GetCurMenu())
	{
	case menuAttack:		
		DrawUI_Image(BackMemDC, menu1, resBattle_btn_attack_on);	// attack Menu : on
			DrawUI_Image(BackMemDC, menu2, resBattle_btn_defense_off);	// Defense Menu : off
			break;
	case menuDefense:
		DrawUI_Image(BackMemDC, menu1, resBattle_btn_attack_off);	// attack Menu : on
		DrawUI_Image(BackMemDC, menu2, resBattle_btn_defense_on);	// Defense Menu : off
	}
}

