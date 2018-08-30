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
	DeleteObject(resUI_btnAttack_on);
	DeleteObject(resUI_btnAttack_off);
	DeleteObject(resUI_btnDefense_on);
	DeleteObject(resUI_btnDefense_off);

	DeleteObject(resWPN_shortsword);
	DeleteObject(resWPN_shortsword_fx);

	DeleteObject(resMob_rat);
	DeleteObject(resUI_numbers);
	DeleteObject(resUI_hpbar_big);
	DeleteObject(resUI_hpbar_small);
	DeleteObject(resUI_Battlemsg);
	DeleteObject(resUI_Battlemsg_marker);


	DeleteObject(resUItrans_horizontal_lones);


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
	resUI_btnAttack_on = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_attack_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resUI_btnAttack_off = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_attack_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resUI_btnDefense_on = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_defense_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resUI_btnDefense_off = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\btn_defense_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);



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
	resUI_Battlemsg_marker = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\ui_msgbox_marker.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	resUItrans_horizontal_lones = (HBITMAP)LoadImage(GetModuleHandle(_T("OneWay_Life")), _T(".\\Resources\\UI\\transition_horizontal_lines.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}


void SceneManager::ShowDebugMessageOnScreen(HDC BackMemDC)
{
	switch (GAME_MANAGER->GetCurScene())
	{
	case BattleScene:
	{
		TCHAR a[128];
		wsprintf(a, _T("Current Battle Message Line : %d"), GAME_MANAGER->GetCurMsgLine());
		TextOut(BackMemDC, 10, 10, a, lstrlen(a));

		TCHAR b[128];
		wsprintf(b, _T("Exp : %d / Gold : %d / Fame : %d"),
			GAME_MANAGER->GetStatus_PC().Exp, GAME_MANAGER->GetStatus_PC().Gold, GAME_MANAGER->GetStatus_PC().Fame);
		TextOut(BackMemDC, 10, 25, b, lstrlen(b));

		TCHAR c[128];
		wsprintf(c, _T("Cur Battle Step : %d"),
			GAME_MANAGER->GetBattleStep());
		TextOut(BackMemDC, 10, 40, c, lstrlen(c));


		TCHAR d[128];
		wsprintf(d, _T("Cur damage Numbers : %d"), GAME_MANAGER->GetBattleMessage().damage);			
		TextOut(BackMemDC, 10, 55, d, lstrlen(d));

		TCHAR e[128];
		wsprintf(e, _T("Line1 - %d Line2 - %d, Line3 - %d"), 
			GAME_MANAGER->GetCurMsgLine_state(1), GAME_MANAGER->GetCurMsgLine_state(2), GAME_MANAGER->GetCurMsgLine_state(3));
		TextOut(BackMemDC, 10, 70, e, lstrlen(e));

	}
	break;
	case TownScene:
	{
		TCHAR a[128];
		wsprintf(a, _T("Current Battle Message Line : %d"), GAME_MANAGER->GetCurMsgLine());
		TextOut(BackMemDC, 10, 10, a, lstrlen(a));
	}
	break;
	}
}

void SceneManager::DrawTitleScene(HDC FrontDC)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(FrontDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	DrawBG(BackMemDC, resTitle_bg);

	Draw_Selector(BackMemDC);

	Draw_Image(BackMemDC, posTitle1, resTitle_txt1);
	Draw_Image(BackMemDC, posTitle2, resTitle_txt2);
	Draw_Image(BackMemDC, posBtn1, resTitle_btn1);

	if (GAME_MANAGER->HaveSaveFile())
		Draw_Image(BackMemDC, posBtn2, resTitle_btn2_on);
	else
		Draw_Image(BackMemDC, posBtn2, resTitle_btn2_off);

	Draw_Image(BackMemDC, posBtn3, resTitle_btn3);

	// Draw BackDC onto FrontDC
	TransparentBlt(FrontDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 1, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);

}
void SceneManager::DrawTownScene(HDC FrontDC)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(FrontDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	// Town (Field)
	//
	// Draw BG
	DrawBG(BackMemDC, resTown_bg);
	// Draw PC and PC's shadow
	DrawPC_Town_Shadow(BackMemDC);
	DrawPC_Town(BackMemDC);

	// Town (Inside)



	// Draw BackDC onto FrontDC
	TransparentBlt(FrontDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 1, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));

	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);
}
void SceneManager::DrawBattleScene(HDC FrontDC, STATUS_PC *status_pc, STATUS_MOB *status_mob)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(FrontDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	// Draw BG
	DrawBG(BackMemDC, resBattle_bg);

	// Set Monster position
	POINT mob_pos = { GAME_MANAGER->GetStatus_MOB().pos_x, GAME_MANAGER->GetStatus_MOB().pos_y };
	POINT pc_pos = { status_pc->pos_x, status_pc->pos_y };



	// Draw Hit VFX for Monster
	if (GAME_MANAGER->GetBattleStep() == PC_Action)
	{
		// Draw Monster
		Battle_DrawMonster(BackMemDC, mob_pos, resMob_rat);
		Battle_DrawFX(BackMemDC, mob_pos, FALSE, resWPN_shortsword_fx);
	}
	else if (status_mob->battlestate != Monster_Dead)
		Battle_DrawMonster(BackMemDC, mob_pos, resMob_rat);


	// Draw Attack Weapon for PC
	if (GAME_MANAGER->GetBattleStep() == PC_Action)
	{
		Battle_DrawWPN(BackMemDC, pc_pos, FALSE, resWPN_shortsword);
	}

	// Draw PC
	DrawPC_Battle(BackMemDC, status_pc);

	// Showbattle Messages
	switch (GAME_MANAGER->GetBattleStep())
	{
	case ShowBattleMenu:
		Battle_ShowMenu(BackMemDC);
		break;
	case PC_Action_Result:
		Battle_ShowMessageBox(BackMemDC);
		if (GAME_MANAGER->GetUiState_BattleMessageBox())
			Battle_ShowMessageText(BackMemDC);
		break;
	case Loot:
		Battle_ShowMessageBox(BackMemDC);
		if (GAME_MANAGER->GetUiState_BattleMessageBox())
			Battle_ShowMessageText(BackMemDC);
		break;
	}

	// Draw Hp Bars
	if(status_mob->hp >0)
		Battle_DrawHP_bar(BackMemDC);


	if (GAME_MANAGER->GetBattleStep() == PC_Action_Result || GAME_MANAGER->GetBattleStep() == MOB_Atcion_Result)
		Battle_DrawDamageNumber(BackMemDC);


#ifdef _DEBUG
	ShowDebugMessageOnScreen(BackMemDC);
#endif

	// Draw BackDC onto FrontDC
	TransparentBlt(FrontDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 1, BackMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB(255, 0, 255));


	// Delete Used DC, HBITMAP
	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);



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

void SceneManager::Draw_Selector(HDC BackMemDC)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(BackMemDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_walk);

	frameCounter++;
	frameNumber = (frameCounter / CHARACTER_FRAME_MAX) % CHARACTER_FRAME_MAX;

	if (frameCounter > CHARACTER_FRAME_MAX * CHARACTER_FRAME_MAX - 1) frameCounter = 0;

	TransparentBlt(BackMemDC, posSelector.x, posSelector.y + 60 * GAME_MANAGER->GetCurMenu(), CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, frameNumber * CHARACTER_SIZE, 2 * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));
	//TransparentBlt(destDC, startX, startY, CHARACTER_SIZE, CHARACTER_SIZE-1, hMemDC, frameNumber * CHARACTER_SIZE, 1 * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawPC_Town(HDC BackMemDC)
{	

	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(BackMemDC);

	// Draw PC
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_walk);
	TransparentBlt(BackMemDC, GAME_MANAGER->GetStatus_PC().pos_x, GAME_MANAGER->GetStatus_PC().pos_y, CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, frameNumber * CHARACTER_SIZE, GAME_MANAGER->GetStatus_PC().facing * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE - 1, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawPC_Town_Shadow(HDC BackMemDC)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(BackMemDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_shadow);

	TransparentBlt(BackMemDC, GAME_MANAGER->GetStatus_PC().pos_shadow_x, GAME_MANAGER->GetStatus_PC().pos_shadow_y + 2, CHARACTER_SIZE, CHARACTER_SIZE - 1, hMemDC, 0, 0, CHARACTER_SIZE, CHARACTER_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::DrawPC_Battle(HDC BackMemDC, STATUS_PC *status_pc)
{
	if (frameCounter == 0)
	{
		switch (GAME_MANAGER->GetBattleStep())
		{
		case PC_Action:
			status_pc->battlestate = Player_Wait;
			GAME_MANAGER->NextBattleStep();
			GAME_MANAGER->SetCurMsgLine(1);
			ResetMsgBox_FrameNumber();
			break;
		}
	}

	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(BackMemDC);

	// Draw PC	
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resPC_battle);
	TransparentBlt(BackMemDC,
		status_pc->pos_x, status_pc->pos_y,
		CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1,
		hMemDC,
		frameNumber * CHARACTER_SIZE_BATTLE, (status_pc->battlestate % 4) * CHARACTER_SIZE_BATTLE,
		CHARACTER_SIZE_BATTLE, CHARACTER_SIZE_BATTLE - 1,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Draw_Image(HDC BackMemDC, POINT & position, HBITMAP &src)
{
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	GetObject(src, sizeof(BITMAP), &bm);

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit4);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit4);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	TransparentBlt(BackMemDC, position.x, position.y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));


	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_ShowMenu(HDC BackMemDC)
{
	POINT BattleMenu_1_on = { GAME_MANAGER->GetStatus_PC().pos_x - BATTLE_MENU_SIZE/2, GAME_MANAGER->GetStatus_PC().pos_y - BATTLE_MENU_SIZE * 1.2 };
	POINT BattleMenu_2_on = { GAME_MANAGER->GetStatus_PC().pos_x + BATTLE_MENU_SIZE, GAME_MANAGER->GetStatus_PC().pos_y - BATTLE_MENU_SIZE * 1.2 };
	POINT BattleMenu_1_off = { GAME_MANAGER->GetStatus_PC().pos_x - BATTLE_MENU_SIZE/2, GAME_MANAGER->GetStatus_PC().pos_y - BATTLE_MENU_SIZE };
	POINT BattleMenu_2_off = { GAME_MANAGER->GetStatus_PC().pos_x + BATTLE_MENU_SIZE, GAME_MANAGER->GetStatus_PC().pos_y - BATTLE_MENU_SIZE };

	if (GAME_MANAGER->GetCurMenu() == menuAttack)
	{
		Draw_Image(BackMemDC, BattleMenu_1_on, resUI_btnAttack_on);
		Draw_Image(BackMemDC, BattleMenu_2_off, resUI_btnDefense_off);
	}
	else
	{
		Draw_Image(BackMemDC, BattleMenu_1_off, resUI_btnAttack_off);
		Draw_Image(BackMemDC, BattleMenu_2_on, resUI_btnDefense_on);
	}
}

void SceneManager::Battle_ShowMessageBox(HDC BackMemDC)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	GetObject(resUI_Battlemsg, sizeof(BITMAP), &bm);

	hMemDC = CreateCompatibleDC(BackMemDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_Battlemsg);
		
	if (msg_Box_frame < BATTLE_MSG_BOX_FRAMES-1)
	{
		TransparentBlt(BackMemDC, BATTLE_POS_MSG_BOX_X, BATTLE_POS_MSG_BOX_Y, BATTLE_MSG_BOX_WIDTH, BATTLE_MSG_BOX_HEIGHT,
			hMemDC, 0, msg_Box_frame * BATTLE_MSG_BOX_HEIGHT, BATTLE_MSG_BOX_WIDTH, BATTLE_MSG_BOX_HEIGHT, RGB(255, 0, 255));
		GAME_MANAGER->SetUiState_BattleMessageBox(FALSE);
	}
	else
	{
		TransparentBlt(BackMemDC, BATTLE_POS_MSG_BOX_X, BATTLE_POS_MSG_BOX_Y, BATTLE_MSG_BOX_WIDTH, BATTLE_MSG_BOX_HEIGHT,
			hMemDC, 0, msg_Box_frame * BATTLE_MSG_BOX_HEIGHT, BATTLE_MSG_BOX_WIDTH, BATTLE_MSG_BOX_HEIGHT, RGB(255, 0, 255));
		GAME_MANAGER->SetUiState_BattleMessageBox(TRUE);
	}

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_ShowMessageText(HDC BackMemDC)
{
	static int nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
	static int nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);
	static int nLen_BattleResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage);

	static int nLen_ExpMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp);
	static int nLen_GoldMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold);
	static int nLen_FameMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame);
	
	if (GAME_MANAGER->GetBattleStep() == Loot)
	{
		switch (GAME_MANAGER->GetCurMsgLine())
		{
		case 1:
			if (nLen_ExpMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp) - (nLen_ExpMessage));
				nLen_ExpMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
				SIZE tmpSize;
				POINT startPos = { 58, 472 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp), &tmpSize);

				nLen_GoldMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp);
				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 2:
			if (nLen_GoldMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold) - (nLen_GoldMessage));
				nLen_GoldMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold));

				SIZE tmpSize;
				POINT startPos = { 58, 488 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold), &tmpSize);

				nLen_ExpMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp);
				nLen_FameMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame);
				
				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(2, TRUE);

				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 3:
			if (nLen_FameMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold));
				TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage_Loot().Fame, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame) - (nLen_FameMessage));
				nLen_FameMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold));
				TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage_Loot().Fame, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame));

				SIZE tmpSize;
				POINT startPos = { 58, 504 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage_Loot().Fame, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame), &tmpSize);

				nLen_ExpMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp);
				nLen_GoldMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold);


				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(2, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(3, TRUE);

				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 100:
		{
			//	// reset text count variables.
		

			TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage_Loot().Exp, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp));
			TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage_Loot().Gold, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold));
			TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage_Loot().Fame, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame));


			nLen_ExpMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Exp);
			nLen_GoldMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Gold);
			nLen_FameMessage = lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame);


			SIZE tmpSize;
			POINT startPos = { 58, 504 };
			GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage_Loot().Fame, lstrlen(GAME_MANAGER->GetBattleMessage_Loot().Fame), &tmpSize);

			GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
			GAME_MANAGER->SetCurMsgLine_state(2, TRUE);
			GAME_MANAGER->SetCurMsgLine_state(3, TRUE);

			Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
		}
		break;
		}
	}
	else if (GAME_MANAGER->GetBattleStep() == PC_Action_Result)
	{
		switch (GAME_MANAGER->GetCurMsgLine())
		{
		case 1:
			if (nLen_AttackMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage) - (nLen_AttackMessage));
				nLen_AttackMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
				SIZE tmpSize;
				POINT startPos = { 58, 472 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage), &tmpSize);

				nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);

				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);

				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 2:
			if (nLen_AttackResultMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage) - (nLen_AttackResultMessage));
				nLen_AttackResultMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));

				SIZE tmpSize;
				POINT startPos = { 58, 488 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage), &tmpSize);
				
				nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
				nLen_BattleResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage);

				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(2, TRUE);				

				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 3:
			if (nLen_BattleResultMessage > 0)
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));
				TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage) - (nLen_BattleResultMessage));
				nLen_BattleResultMessage--;
			}
			else
			{
				TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
				TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));
				TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage));

				SIZE tmpSize;
				POINT startPos = { 58, 504 };
				GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage), &tmpSize);

				nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
				nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);

				GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(2, TRUE);
				GAME_MANAGER->SetCurMsgLine_state(3, TRUE);

				Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
			}
			break;
		case 100:
		{
			//	// reset text count variables.
			//	nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
			//	nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);
			//	nLen_BattleResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage);

			TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
			TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));
			TextOut(BackMemDC, 58, 504, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage));


			nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
			nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);
			nLen_BattleResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage);
			SIZE tmpSize;
			POINT startPos = { 58, 504 };
			GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage().BattleResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().BattleResultMessage), &tmpSize);

			GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
			GAME_MANAGER->SetCurMsgLine_state(2, TRUE);
			GAME_MANAGER->SetCurMsgLine_state(3, TRUE);

			Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
		}
		break;
		case 200:
		{
			// reset text count variables.
			nLen_AttackMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage);
			nLen_AttackResultMessage = lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage);

			TextOut(BackMemDC, 58, 472, GAME_MANAGER->GetBattleMessage().AttackMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackMessage));
			TextOut(BackMemDC, 58, 488, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage));

			SIZE tmpSize;
			POINT startPos = { 58, 488 };
			GetTextExtentPoint(BackMemDC, GAME_MANAGER->GetBattleMessage().AttackResultMessage, lstrlen(GAME_MANAGER->GetBattleMessage().AttackResultMessage), &tmpSize);

			GAME_MANAGER->SetCurMsgLine_state(1, TRUE);
			GAME_MANAGER->SetCurMsgLine_state(2, TRUE);
			Battle_ShowMessageText_marker(BackMemDC, startPos, tmpSize);
		}
		break;
		}
	}

}

void SceneManager::Battle_ShowMessageText_marker(HDC BackMemDC, POINT &startPos, SIZE &tmpSize)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;

	hMemDC = CreateCompatibleDC(BackMemDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_Battlemsg_marker);

	frameCounter++;
	frameNumber = (frameCounter / CHARACTER_FRAME_MAX) % CHARACTER_FRAME_MAX;

	if (frameCounter > CHARACTER_FRAME_MAX * CHARACTER_FRAME_MAX - 1) frameCounter = 0;

	TransparentBlt(BackMemDC, startPos.x + tmpSize.cx , startPos.y, UI_MSG_MARKER_SIZE, UI_MSG_MARKER_SIZE, hMemDC, frameNumber * UI_MSG_MARKER_SIZE, 0, UI_MSG_MARKER_SIZE, UI_MSG_MARKER_SIZE, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_DrawFX(HDC BackMemDC, POINT & position, bool SrcIsVertical, HBITMAP & src)
{
	// Create Back Memory DC
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit4 = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit4);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit4);

	SelectObject(hMemDC, (HBITMAP)src);
	TransparentBlt(BackMemDC, position.x, position.y, WPN_VFX_SIZE, WPN_VFX_SIZE,
		hMemDC, frameNumber * WPN_VFX_SIZE, 0, WPN_VFX_SIZE, WPN_VFX_SIZE,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_DrawWPN(HDC BackMemDC, POINT & position, bool SrcIsVertical, HBITMAP & src)
{
	// Create Back Memory DC
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	SelectObject(hMemDC, (HBITMAP)src);
	TransparentBlt(BackMemDC, position.x - WPN_MOD_LEFT, position.y - WPN_MOD_UP, WPN_WIDTH, WPN_HEIGHT,
		hMemDC, frameNumber * WPN_WIDTH, 0, WPN_WIDTH, WPN_HEIGHT,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_DrawMonster(HDC BackMemDC, POINT & position, HBITMAP &src)
{
	// Create Back Memory DC
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, src);
	


	// Get Size of src image
	GetObject(src, sizeof(BITMAP), &bm);
	
	static int height = bm.bmHeight;

	if (GAME_MANAGER->GetBattleStep() == ShowBattleMenu)
		height = bm.bmHeight;
	
	if (GAME_MANAGER->GetStatus_MOB().battlestate == Monster_Dying)
	{		
		if (height > 0)
		{
			TransparentBlt(BackMemDC, position.x + (-1 * (frameCounter % shake_fast)), position.y, bm.bmWidth, height, hMemDC, 0, 0, bm.bmWidth, height, RGB(255, 0, 255));
			height -= 2;
		}
		else
		{
			GAME_MANAGER->NextBattleStep();
			GAME_MANAGER->SetCurMsgLine(1);
			GAME_MANAGER->SetCurMsgLine_state(1,FALSE);
			GAME_MANAGER->SetCurMsgLine_state(2,FALSE);
			GAME_MANAGER->SetCurMsgLine_state(3,FALSE);
		}
	}
	else if (GAME_MANAGER->GetBattleStep() == PC_Action)
	{
		TransparentBlt(BackMemDC, position.x + (-1 * (frameCounter % shake_mid)), position.y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(BackMemDC, position.x, position.y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));
	}


	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
}

void SceneManager::Battle_DrawHP_bar(HDC BackMemDC)
{
	// Create Back Memory DC
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_hpbar_small);

	GetObject(resUI_hpbar_small, sizeof(BITMAP), &bm);


	// calculate hp bar length per 1 HP
	double pixelperhp_PC = 0;
	double pixelperhp_MOB = 0;

	//pixelperhp_PC = PORTRAIT_SIZE / (double)pc_stat.hp_max);
	//pixelperhp_MOB = PORTRAIT_SIZE / (double)mob_stat.hp_max;
	pixelperhp_PC = bm.bmWidth / (double)GAME_MANAGER->GetStatus_PC().hp_max;
	pixelperhp_MOB = bm.bmWidth / (double)GAME_MANAGER->GetStatus_MOB().hp_max;

	BITMAP MonsterSize;

	GetObject(resMob_rat, sizeof(BITMAP), &MonsterSize);

	// HP bar background for Monster
	TransparentBlt(BackMemDC, 
		GAME_MANAGER->GetStatus_MOB().pos_x, GAME_MANAGER->GetStatus_MOB().pos_y + MonsterSize.bmHeight + bm.bmHeight,
		bm.bmWidth, bm.bmHeight/2, 
		hMemDC, 
		0, 0, 
		bm.bmWidth, bm.bmHeight/2,
		RGB(255, 0, 255));


	// actual HP of Monster	

	TransparentBlt(BackMemDC,
		GAME_MANAGER->GetStatus_MOB().pos_x, GAME_MANAGER->GetStatus_MOB().pos_y + MonsterSize.bmHeight + bm.bmHeight,
		pixelperhp_MOB * GAME_MANAGER->GetStatus_MOB().hp, bm.bmHeight / 2,
		hMemDC,
		0, bm.bmHeight / 2,
		pixelperhp_MOB * GAME_MANAGER->GetStatus_MOB().hp, bm.bmHeight / 2,
		RGB(255, 0, 255));



	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

	
}

void SceneManager::Battle_DrawDamageNumber(HDC BackMemDC)
{
	TCHAR numbers[8];
	wsprintf(numbers, _T("%d"), GAME_MANAGER->GetBattleMessage().damage);


	// Create Back Memory DC
	HDC hMemDC = CreateCompatibleDC(BackMemDC);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	DeleteObject(hBit);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, resUI_numbers);

	if (lstrlen(numbers) > 0)
	{
		switch (GAME_MANAGER->GetBattleStep())
		{
		case PC_Action_Result:
			if (GAME_MANAGER->GetCurMsgLine_state(1))
			{
				for (int i = 0; i < lstrlen(numbers); i++)
				{
					TransparentBlt(BackMemDC,
						GAME_MANAGER->GetStatus_MOB().pos_x + 35 + i * 18 , GAME_MANAGER->GetStatus_MOB().pos_y + 32 -3,
						UI_FONT_SIZE, UI_FONT_SIZE,
						hMemDC,
						(numbers[i] - 48) * UI_FONT_SIZE, 0,
						UI_FONT_SIZE, UI_FONT_SIZE,
						RGB(255, 0, 255));
				}
			}
			break;
		}
	}


	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

}



void SceneManager::AddFrameCounter(int amount)
{
	frameCounter += amount;

	if (frameCounter > CHARACTER_FRAME_MAX * CHARACTER_FRAME_MAX) frameCounter = 0;


}

void SceneManager::SetFramecounter(int value)
{
	frameCounter = value;
}

void SceneManager::AddMsgBox_frameNumber()
{
	msg_Box_frame++;

	if (msg_Box_frame > BATTLE_MSG_BOX_FRAMES - 1)
		msg_Box_frame = BATTLE_MSG_BOX_FRAMES - 1;
}

void SceneManager::ResetMsgBox_FrameNumber()
{
	msg_Box_frame = 0;
}

void SceneManager::SetAnimationFrame(int animationFrame)
{
	frameNumber = animationFrame;
}

int SceneManager::GetFrameCounter()
{
	return frameCounter;
}

int SceneManager::GetAnimationFrameNumber()
{
	return frameNumber;
}
