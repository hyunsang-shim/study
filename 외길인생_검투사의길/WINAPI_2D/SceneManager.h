#pragma once

#include "stdafx.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void LoadResource();
	void UnLoadResource();
	

	void DrawUI(HDC hdc);
	void DrawUI_Font(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawUI_HPbar(HDC destDC);
	void DrawUI_Portrait(HDC destDC, int &player_battlestate, int &monster_battlestate);
	void DrawUI_Image(HDC destDC, POINT &point, HBITMAP &src);
	void DrawUI_Selector(HDC destDC, POINT &point, HBITMAP &src, int &frameNumber, int &direction);


	void DrawBattler_Mob(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawBattler_PC(HDC destDC, STATUS_PC *status_pc, HBITMAP src, int frameNumber);
	void DrawActor_PC(HDC destDC, int &start_x, int &start_y, HBITMAP &src, int &frameNumber, int &PC_Direction);
	void DrawActor_PC_Shadow(HDC destDC, int &start_x, int &start_y, HBITMAP src);

	void DrawFX_PC(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawATK_VFX(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void drawDamage(HDC destDC, POINT pos, int damage);
//	void DrawToFront(HDC destDC, HDC srcDC);
	void DrawTitleScene(HDC hdc, int &CurMenu, int &PC_Direction);
	void DrawTownScene(HDC hdc, STATUS_PC *status_pc);
	void DrawBattleScene(HDC destDC, int &BattleState, STATUS_PC *status_pc, STATUS_MOB *status_mob);
	//void DrawBattleScene(HDC hdc, int &BattleState_PC);
	void DrawBG(HDC destDC, HBITMAP &src);


	void DoBattle(HDC BackMemDC);
	void ShowBattleMenu(HDC BackMemDC, STATUS_PC *status_pc);

	void KeyInput(WPARAM wParam, int &CurScene, int &CurMenu);
	bool PeekNextCoord(POINT CurPos);
	void MoveCharacter(POINT nextPoint);

	
	void ShowEvent(int EventId);
	void ShowMessage(HDC BackMemDC);


	//resource Lists
	HBITMAP resTitle_bg;
	HBITMAP resTitle_txt1;
	HBITMAP resTitle_txt2;
	HBITMAP resTitle_btn1;
	HBITMAP resTitle_btn2_on;
	HBITMAP resTitle_btn2_off;
	HBITMAP resTitle_btn3;
	HBITMAP resTown_bg;
	HBITMAP resPC_walk;
	HBITMAP resPC_shadow;
	HBITMAP resPC_battle;
	HBITMAP resPC_face;

	HBITMAP resBattle_btn_attack_on;
	HBITMAP resBattle_btn_attack_off;
	HBITMAP resBattle_btn_defense_on;
	HBITMAP resBattle_btn_defense_off;

	HBITMAP resWPN_shortsword;
	HBITMAP resWPN_shortsword_fx;

	HBITMAP resMob_rat;
	HBITMAP resMob_face;

	HBITMAP resBattle_bg;
	HBITMAP resUI_numbers;
	HBITMAP resUI_hpbar_big;
	HBITMAP resUI_hpbar_small;

	BITMAP bm;

	DAMAGE_FONT damage_font;

	POINT title1 = { 210, 0 };
	POINT title2 = { 210, 96 };
	POINT btn1 = { 600, 400 };
	POINT btn2 = { 600, 460 };
	POINT btn3 = { 600, 520 };
	POINT selector = { 550, 390 };
	
private:	
	
	//for town map movement test
	int tmpflag = -1;

	
	
	// for shaking amount
	int shake_fast = 5;
	int shake_mid = 8;
	int shake_slow = 15;
};

