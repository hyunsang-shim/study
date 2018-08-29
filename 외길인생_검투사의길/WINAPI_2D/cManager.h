#pragma once

#include "stdafx.h"

class SceneManager;

class cManager
{
private:
	SceneManager *scnManager;

public:
	cManager();
	~cManager();
	//
	// prepare and initialize
	//
	void Init();
	void InitTitleScene();
	void InitTownScene();
	void InitBattleScene();

	
	//
	// Scene Update and draw
	//
	void UpdateScene(HDC FrontDC);
	void DrawScene(HDC FrontDC);
	void ChangeScene(int destSceneidx);
	bool HaveSaveFile();
	void UpdateTitle();
	void UpdateTown();
	void UpdateBattle();

	
	


	//
	// UI related
	//


	//
	// Process Input
	//
	void key(WPARAM wparam);



	//
	// compute things
	//
	int calcDamage(STATUS_PC *pc, STATUS_MOB *mob);
	int calcDamage(STATUS_MOB *mob, STATUS_PC *pc);
	bool PeekNextCoord();
	void MoveCharacter();
	void ApplyDamage(STATUS_PC *pc, int damage);
	void ApplyDamage(STATUS_MOB *mob, int damage);


	//
	// methods for set variables
	//
	void SetCurScene(int SceneName);
	void SetCurMenu(int menu);
	void SetEventID(int eventID);
	void SetUiState_BattleMessageBox(bool val);
	void SetBattleMessage(STATUS_PC *attacker, STATUS_MOB *defender);
	void SetBattleMessage(STATUS_MOB *attacker, STATUS_PC *defender);
	void NextBattleStep();
	void SetBattleStep(int nextstep);
	void SetCurMsgLine(short newline);

	
	//
	// methods for get variables
	//
	int GetCurScene();
	int GetCurMenu();
	int GetBattleStep();
	int GetEventID();
	bool GetUiState_BattleMessageBox();
	short GetCurMsgLine();
	STATUS_PC GetStatus_PC();
	STATUS_MOB GetStatus_MOB();
	BATTLE_MSG GetBattleMessage();
	
public:
	static cManager* GetInstance()
	{
		static cManager instance;
		
		

		return &instance;
	}

	//
	// private variables
	//
private:
	//
	// Scene related variables
	// 
	int EventId;
	int CurScene;
	int CurMenu = menuNew;
	int lastScene = TitleScene;	
	bool UI_state_MSGW = FALSE;
	int BattleStep = 0;
	short CurMsgLine = 0;

	//
	// position and character statuses
	//
	//
	int BattleState = Battle_Ready;

	STATUS_PC status_pc;
	STATUS_MOB status_mob;
	BATTLE_MSG MSG_Battle;

	POINT MOB_XY = { 96, 280 };

	//
	// map data
	//
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

	//
	//
	//
	
	int dmg;


	

	
};

