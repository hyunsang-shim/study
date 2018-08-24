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
	void Test();
	void Init();
	void InitTitleScene();
	void InitTownScene();
	void InitBattleScene();

	
	//
	// Scene Update and draw
	//
	void UpdateScene(HDC hdc);
	void DrawScene(HDC hdc);
	void ChangeScene(int destSceneidx);
	bool HaveSaveFile();
	


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
	void DoBattle();

	//
	// methods for set variables
	//
	void SetCurScene(int SceneName);
	void SetCurMenu(int menu);
	void SetPC_Direction(int direction);
	void SetPC_State(int state);
	void SetBattleState_PC(int state);
	void SetBattleState_Mob(int state);
	void SetPC_COORD(int row, int col);
	void SetPC_XY(int row, int col);
	void SetPC_COORD_NEXT(int row, int col);
	void SetEventID(int eventID);

	
	//
	// methods for get variables
	//
	int GetCurScene();
	int GetCurMenu();
	int GetDirection_PC();
	int GetSpeed_PC();
	int GetPC_State();
	int GetBattleState_PC();
	int GetBattleState_Mob();
	POINT GetPC_XY();
	POINT GetPC_COORD();
	POINT GetPC_COORD_NEXT();
	int GetEventID();
	STATUS_PC GetStatus_PC();
	STATUS_MOB GetStatus_MOB();



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

	//
	// position and character statuses
	//
	int PC_Direction = FacingRight;
	int PC_Speed = 4;
	int PC_State = Idle;
	
	int BattleState_PC = Player_Ready;
	int BattleState_Mob = Monster_Ready;
	int BattleState = Battle_Ready;

	STATUS_PC status_pc;
	STATUS_MOB status_mob;

	POINT PC_XY;
	POINT PC_XY_SHADOW;

	POINT PC_COORD;
	POINT PC_COORD_NEXT;
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

