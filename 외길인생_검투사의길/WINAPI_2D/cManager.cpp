
#include "stdafx.h"
#include "cManager.h"


cManager::cManager()
{
	CurScene = TitleScene;
	hInst = GetModuleHandle(NULL);
}

void cManager::SetCurScene(int SceneName)
{
	this->CurScene = SceneName;
}


int cManager::calcDamage(STATUS_PC *pc, STATUS_MOB *mob)
{
	mob->hp -= pc->atk - mob->def;
	
	return pc->atk - mob->def;
	
}

int cManager::calcDamage(STATUS_MOB *mob, STATUS_PC *pc)
{
	pc->hp -= mob->atk - pc->def;


	return mob->atk - pc->def;
}

cManager::~cManager()
{
}

int cManager::GetCurScene()
{
	return CurScene;
}

void cManager::SetCurMenu(int menu)
{
	CurMenu = menu;
}

int cManager::GetCurMenu()
{
	return CurMenu;
}

void cManager::SetLastScene(int SceneName)
{
	this->lastScene = SceneName;
}

int cManager::GetLastScene()
{
	return this->lastScene;
}

bool cManager::HaveSaveFile()
{
	return false;
}

int cManager::GetDirection_PC()
{
	return PC_Direction;
}

void cManager::SetPC_Direction(int direction)
{
	//if (PC_Direction != direction)
		PC_Direction = direction;
}

int cManager::GetSpeed_PC()
{
	return PC_Speed;
}

void cManager::SetPC_State(int state)
{
	PC_State = state;
}

int cManager::GetPC_State()
{
	return PC_State;
}

int cManager::GetBattleState_PC()
{
	return BattleState_PC;
}

int cManager::GetBattleState_Mob()
{
	return BattleState_Mob;
}

void cManager::SetBattleState_PC(int state)
{
	BattleState_PC = state;
}

void cManager::SetBattleState_Mob(int state)
{
	BattleState_Mob = state;
}
