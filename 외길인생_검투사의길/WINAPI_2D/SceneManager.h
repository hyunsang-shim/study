#pragma once
#include "cManager.h"
#include "BattleManager.h"
#include <vector>

class SceneManager : public cManager
{
public:
	SceneManager();
	~SceneManager();
	void LoadResource();
	void UnLoadResource();
	void DrawScene(HDC hdc);
	void ChangeScene(int destSceneidx);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawSpriteShadow(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawBattler_Mob(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawBattler_PC(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawFX_PC(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
//	void DrawToFront(HDC destDC, HDC srcDC);
	void DrawTitleScene(HDC hdc);
	void DrawTownScene(HDC hdc);

	void DrawBattleScene(HDC hdc);
	void DoBattle(HDC BackMemDC);
	void ShowBattleMenu(HDC BackMemDC);
	void KeyInput(WPARAM wParam);
	bool PeekNextCoord(POINT CurPos);
	void MoveCharacter(POINT nextPoint);
	void SetPC_POS(int row, int col);
	POINT GetPC_POS();
	void SetPC_COORD(int row, int col);
	POINT GetPC_COORD();
	void SetPC_COORD_NEXT(int row, int col);
	POINT GetPC_COORD_NEXT();
	void SetEventID(int eventID);
	int GetEventID();
	void ShowEvent(int EventId);

	std::vector<HBITMAP> resources;



private:	
	POINT PC_POS;
	POINT PC_COORD;
	POINT PC_COORD_NEXT;
	short TownMap[14][17] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,200,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,1,1,0,1,1,0,400,0,0,
		0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
		0,0,300,0,1,1,1,1,1,0,1,1,1,0,500,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,600,0,0,0,0,0,0,0,0
	};
	 
	short BattleMap[14][17] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	//for town map movement test
	int tmpflag = -1;

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
	HBITMAP resBattle_btn_attack_on;
	HBITMAP resBattle_btn_attack_off;
	HBITMAP resBattle_btn_defense_on;
	HBITMAP resBattle_btn_defense_off;

	HBITMAP resWPN_shortsword;

	HBITMAP resMob_rat;

	HBITMAP resBattle_bg;

	BITMAP bm;

	int EventId;
};

