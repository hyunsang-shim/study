#pragma once

#include "stdafx.h"

class SceneManager
{	
public:
	SceneManager();
	~SceneManager();
	void LoadResource();
	void UnLoadResource();

	// for Debug
	void ShowDebugMessageOnScreen(HDC BackMemDC);

	// Draw BG
	void DrawBG(HDC destDC, HBITMAP &src);

	// Draw Scene Parts. Characters, shadows, shop and etc
	void DrawPC_Town(HDC BackMemDC);
	void DrawPC_Battle(HDC BackMemDC, STATUS_PC *status_pc);
	void DrawPC_Town_Shadow(HDC BackMEmDC);
	void Draw_Selector(HDC BackMemDC);

	// Draw Common things
	void Draw_Image(HDC BackMemDC, POINT &position, HBITMAP &src);

	//Battle Related
	void Battle_ShowMenu(HDC BackMemDC);
	void Battle_ShowMessageBox(HDC BackMemDC);
	void Battle_ShowMessageText(HDC BackMemDC);
	void Battle_ShowMessageText_marker(HDC BackMemDC, POINT &startPos, SIZE &tmpSize);
	void Battle_DrawFX(HDC BackMemDC, bool SrcIsVertical, HBITMAP &src);
	void Battle_DrawWPN(HDC BackMemDC, bool SrcIsVertical, HBITMAP &src);
	void Battle_DrawMonster(HDC BackMemDC, STATUS_MOB *status_mob, HBITMAP &src);
	void Battle_DrawHP_bar(HDC BackMemDC);
	void Battle_DrawDamageNumber(HDC BackMemDC);

	// Draw Whole Scenes
	void DrawTitleScene(HDC FrontDC);
	void DrawTownScene(HDC FrontDC);	
	void DrawBattleScene(HDC FrontDC, STATUS_PC *status_pc, STATUS_MOB *status_mob);
	void DrawGameOverScene(HDC FrontDC);


	// frame related
	void AddFrameCounter(int amount);
	void SetFramecounter(int value);
	void AddMsgBox_frameNumber();
	void ResetMsgBox_FrameNumber();
	void SetAnimationFrame(int animationFrame);

	int GetFrameCounter();
	int GetAnimationFrameNumber();

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

	HBITMAP resGameover_bg;


	HBITMAP resUI_btnAttack_on;
	HBITMAP resUI_btnAttack_off;
	HBITMAP resUI_btnDefense_on;
	HBITMAP resUI_btnDefense_off;

	HBITMAP resWPN_shortsword;
	HBITMAP resWPN_shortsword_fx;

	HBITMAP resMob_rat;
	HBITMAP resMob_face;

	HBITMAP resBattle_bg;
	HBITMAP resUI_numbers;
	HBITMAP resUI_hpbar_big;
	HBITMAP resUI_hpbar_small;
	HBITMAP resUI_Battlemsg;
	HBITMAP resUI_Battlemsg_marker;

	HBITMAP resUItrans_horizontal_lones;

	BITMAP bm;

	DAMAGE_FONT damage_font;

	POINT posTitle1 = { 210, 0 };
	POINT posTitle2 = { 210, 96 };
	POINT posBtn1 = { 600, 400 };
	POINT posBtn2 = { 600, 460 };
	POINT posBtn3 = { 600, 520 };
	POINT posSelector = { 550, 390 };
	
private:	
	
	//for town map movement test
	int tmpflag = -1;

	RECT Battle_MSG_Label = { 58, 472, 760, 600 };

	// for Animation Frame management
	int frameNumber = 0;
	int frameCounter = 0;
	int msg_Box_frame = 0;
	
	// for shaking amount
	int shake_fast = 5;
	int shake_mid = 8;
	int shake_slow = 15;
};

