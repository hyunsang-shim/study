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
	void InitGameOverScene();

	
	//
	// Scene Update and draw
	//
	void ChangeScene(int destSceneidx); 
	void UpdateScene(HDC FrontDC);
	void DrawScene(HDC FrontDC);

	bool HaveSaveFile();
	void UpdateTitle();
	void UpdateTown();
	void UpdateBattle();
	void UpdateGameOverScene();

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
	void MoveCharacter(STATUS_MOB *mob);
	void ApplyDamage(STATUS_PC *pc, int damage);
	void ApplyDamage(STATUS_MOB *mob, int damage);


	//
	// methods for set variables
	//
	void SetCurScene(int SceneName);
	void SetCurMenu(int menu);
	void SetEventID(int eventID);
	void SetUiState_BattleMessageBox(bool val);
	void SetBattleMessage(STATUS_PC *pc);
	void SetBattleMessage(STATUS_MOB *mob);
	void InitBattleMessage();
	void SetBattleMessage_Loot();
	void InitBattleMessage_Loot();	
	void SetBattleMessage_Result(short PlayerBattleState);
	void InitBattleMessage_Result();

	void NextBattleStep();
	void SetBattleStep(int nextstep);
	void SetCurMsgLine(short newline);
	void SetCurMsgLine_state(short idx, bool value);
	void GainLoot();

	
	//
	// methods for get variables
	//
	int GetCurScene();
	int GetCurMenu();
	int GetBattleStep();
	int GetEventID();
	bool GetUiState_BattleMessageBox();
	short GetCurMsgLine();
	bool GetCurMsgLine_state(short idx);
	HISTORY GetHistory();
	STATUS_PC GetStatus_PC();
	STATUS_MOB GetStatus_MOB();
	BATTLE_MSG GetBattleMessage();
	LOOT_MSG GetBattleMessage_Loot();
	RESULT_MSG GetBattleMessage_Result();
	
	
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
	bool UI_state_MSGW_Loot = FALSE;
	int BattleStep = 0;
	short CurMsgLine = 0;
	bool CurMsgLine_State[3] = { FALSE, FALSE, FALSE };

	//
	// position and character statuses
	//
	//
	//int BattleState = Battle_Ready;

	STATUS_PC status_pc;
	STATUS_MOB status_mob;
	BATTLE_MSG MSG_Battle;
	LOOT_MSG MSG_Battle_Loot;
	RESULT_MSG MSG_Battle_Result;
	HISTORY history;


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
	
	int dmg_counter;


	

	
};

