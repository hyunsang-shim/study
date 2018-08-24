
#include "stdafx.h"
#include "cManager.h"
#include "SceneManager.h"


cManager::cManager()
{
	CurScene = BattleScene;	
}

cManager::~cManager()
{
	scnManager->UnLoadResource();
	delete scnManager;
}


//
// prepare and initialize
//
void cManager::Test()
{
	HDC tmpDC = GetDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")));
	scnManager->ShowBattleMenu(tmpDC);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	
}

void cManager::Init()
{
	scnManager = new SceneManager;
	scnManager->LoadResource();
	CurScene = BattleScene;
}

void cManager::InitTitleScene()
{
	CurScene = TitleScene;
	PC_Direction = FacingRight;
	CurMenu = menuNew;
}

void cManager::InitTownScene()
{
	CurScene = TownScene;
	status_pc.coord_x = status_pc.coord_next_x = 8;
	status_pc.coord_y = status_pc.coord_next_y = 11;
	status_pc.pos_x = status_pc.coord_next_x * 48;
	status_pc.pos_y = status_pc.coord_next_y * 48;
	status_pc.pos_shadow_x = status_pc.pos_x + 8;
	status_pc.pos_shadow_y = status_pc.pos_y + 18;
	status_pc.facing = FacingUp;
	status_pc.movestate = Idle;
	status_pc.battlestate = Player_Wait;
	status_pc.speed = 4;

	CurMenu = menuYes;

}

void cManager::InitBattleScene()
{
	CurScene = BattleScene;	
	CurMenu = menuAttack;

	status_pc.atk = 10;
	status_pc.def = 1;
	status_pc.hp = 15;
	status_pc.hp_max = 15; 
	status_pc.coord_x = status_pc.coord_next_x = 13;
	status_pc.coord_y = status_pc.coord_next_y = 8;
	status_pc.pos_x = status_pc.coord_next_x * 48;
	status_pc.pos_y = status_pc.coord_next_y * 48;
	status_pc.pos_shadow_x = status_pc.pos_x + 8;
	status_pc.pos_shadow_y = status_pc.pos_y + 18;
	status_pc.facing = FacingLeft;
	status_pc.movestate = Idle;
	status_pc.battlestate = Player_Ready; 		
	status_pc.speed = 4; 		
		
	status_mob.atk = 7;
	status_mob.def = 1;
	status_mob.hp = 35;
	status_mob.hp_max = 35;
}



//
// Scene Update and draw
//

void cManager::UpdateScene(HDC hdc)
{
	switch (CurScene)
	{
	case TitleScene:
		break;
	case BattleScene:
		DoBattle();
		break;
	case TownScene:
		if (status_pc.movestate == Moving)
			MoveCharacter();
		break;
	}
}

void cManager::DrawScene(HDC hdc)
{
	switch (CurScene)
	{
	case TitleScene:
		scnManager->DrawTitleScene(hdc, CurMenu, status_pc.facing);
		break;
	case TownScene:
		scnManager->DrawTownScene(hdc, &status_pc);
		break;
	case BattleScene:
		scnManager->DrawBattleScene(hdc, BattleState, &status_pc, &status_mob);
		break;
	}
}

void cManager::ChangeScene(int destSceneidx)
{

	switch (destSceneidx)
	{
	case TitleScene:
		InitTitleScene();
		break;
	case TownScene:
		InitTownScene();
		break;
	case BattleScene:
		InitBattleScene();
		break;
	case GameOverScene:
		CurScene = GameOverScene;
		break;
	case ShopGym:
		CurScene = ShopGym;
		break;
	case ShopChurch:
		CurScene = ShopChurch;
		break;
	case ShopBlacksmith:
		CurScene = ShopBlacksmith;
		break;
	case ShopGuild:
		CurScene = ShopGuild;
		break;
	case House:
		CurScene = House;
		break;
	}

}

bool cManager::HaveSaveFile()
{
	return false;
}


//
// resource related
//



//
// UI related
//



//
// Process Input
//
void cManager::key(WPARAM wParam)
{
	switch (CurScene)
	{
	case TitleScene:
		PC_Direction = FacingRight;
		switch (wParam)
		{
		case VK_UP:
			if (CurMenu == menuNew)
				CurMenu = menuQuit;
			else if (CurMenu == menuQuit)
				if (HaveSaveFile())
					CurMenu = menuLoad;
				else
					CurMenu = menuNew;
			else
				SetCurMenu(menuNew);
			break;
		case VK_DOWN:
			if (CurMenu == menuNew)
				if (HaveSaveFile())
					CurMenu = menuLoad;
				else
					CurMenu = menuQuit;
			else if (CurMenu == menuLoad)
				CurMenu = menuQuit;
			else
				CurMenu = menuNew;
			break;
		case VK_RETURN:
			switch (CurMenu)
			{
			case menuQuit:
				if (wParam == VK_RETURN)
					SendMessage(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), WM_CLOSE, 0, 0);
				break;
			case menuNew:
				ChangeScene(TownScene);				
				break;
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
				if (status_pc.movestate == Moving)
				{
					MoveCharacter();
					break;
				}
				else
				{
					status_pc.facing = FacingUp;
					if (PeekNextCoord())
					{
						status_pc.movestate = Moving;
						status_pc.coord_y -= 1;
						status_pc.coord_next_y = status_pc.coord_y;
						MoveCharacter();
					}
					break;
				}
			case VK_DOWN:
				if (status_pc.movestate == Moving)
				{
					MoveCharacter();
					break;
				}
				else
				{
					status_pc.facing = FacingDown;
					if (PeekNextCoord())
					{
						status_pc.movestate = Moving;
						status_pc.coord_y += 1;
						status_pc.coord_next_y = status_pc.coord_y;
						MoveCharacter();
					}
					break;
				}
			case VK_LEFT:
				if (status_pc.movestate == Moving)
				{
					MoveCharacter();
					break;
				}
				else
				{
					status_pc.facing = FacingLeft;
					if (PeekNextCoord())
					{
						status_pc.movestate = Moving;
						status_pc.coord_x -= 1;						
						status_pc.coord_next_x = status_pc.coord_x;
						MoveCharacter();
					}
					break;
				}
			case VK_RIGHT:
				if (status_pc.movestate == Moving)
				{
					MoveCharacter();
					break;
				}
				else
				{
					status_pc.facing = FacingRight;
					if (PeekNextCoord())
					{
						status_pc.movestate = Moving;
						status_pc.coord_x += 1;
						status_pc.coord_next_x = status_pc.coord_x;
						MoveCharacter();
					}
					break;
				}
			case VK_SPACE:	// for testing purpose
				ChangeScene(BattleScene);
				break;
			}
		EventId = TownMap[status_pc.coord_y][status_pc.coord_x];
			//std::cout << "PC Coord (current, next) : (" << PC_COORD.y << "," << PC_COORD.x << "), (" << PC_COORD_NEXT.y << "," << PC_COORD_NEXT.y << "  EventID : " << EventId << "\n";
		break;
	case BattleScene:
		if (BattleState == Battle_Ready)
			{
				switch (wParam)
				{
				case VK_LEFT:
					CurMenu = menuAttack;
					status_mob.atk = 1;
					break;
				case VK_RIGHT:
					CurMenu = menuDefense;
					status_mob.atk = 20;
					break;
				case VK_UP:
					status_pc.hp = status_pc.hp_max;
					break;
				case VK_ESCAPE:
					ChangeScene(TownScene);
					EventId = 1;
					break;
				case VK_RETURN:
					status_pc.battlestate = Battle_On;
					BattleState_PC = Player_Attack_Move;					
					break;
				}
				break;
			}
		else if (BattleState_PC == Player_Win)
			{
				switch (wParam)
				{
				case VK_RETURN:
					ChangeScene(TownScene);
					SetEventID(1);
					break;
				}
				break;
			}
		else if (BattleState_PC == Player_Lose && wParam == VK_RETURN)
			ChangeScene(TitleScene);
		break;
	}
}


//
// compute things
//
int cManager::calcDamage(STATUS_PC * pc, STATUS_MOB * mob)
{
	mob->hp -= pc->atk - mob->def;

	return pc->atk - mob->def;
}

int cManager::calcDamage(STATUS_MOB * mob, STATUS_PC * pc)
{
	pc->hp -= mob->atk - pc->def;

	return mob->atk - pc->def;
}

bool cManager::PeekNextCoord()
{	
	switch (status_pc.facing)
	{
	case FacingLeft:
		if (status_pc.coord_x - 1 < 0)
			return false;
		else
			return TownMap[status_pc.coord_y][status_pc.coord_x-1];
	case FacingRight:
		if (status_pc.coord_x + 1 >= MAP_COL)
			return false;
		else
			return TownMap[status_pc.coord_y][status_pc.coord_x+1];
	case FacingUp:
		if (status_pc.coord_y - 1 < 0)
			return false;
		else
			return TownMap[status_pc.coord_y-1][status_pc.coord_x];
	case FacingDown:
		if (status_pc.coord_y + 1 >= MAP_ROW)
			return false;
		else
			return TownMap[status_pc.coord_y+1][status_pc.coord_x];
	}

}

void cManager::MoveCharacter()
{
	// Move Character from currend coordinate to next coordinate.
	// should ignore input while moving


	int DestX = status_pc.coord_next_x * 48;
	int DestY = status_pc.coord_next_y * 48;

	// Set x position
	if (DestX - status_pc.pos_x > 0)
		status_pc.pos_x += status_pc.speed;
	else if (DestX - status_pc.pos_x < 0)
		status_pc.pos_x -= status_pc.speed;
	
	// Set y position
	if (DestY - status_pc.pos_y > 0)
		status_pc.pos_y += status_pc.speed;
	else if (DestY - status_pc.pos_y < 0)
		status_pc.pos_y -= status_pc.speed;

	printf("Moving : row %d(%d) col %d(%d) \n", status_pc.pos_x, status_pc.coord_x, status_pc.pos_y, status_pc.coord_y);

	// change character status to Idle whel reaches target position.
	if ((status_pc.pos_x == DestX) && (status_pc.pos_y == DestY))
	{
		if (status_pc.movestate == Moving)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;

		}
		else if (BattleState_PC == Player_Attack_Move)
		{
			status_pc.facing = FacingLeft;
			status_pc.battlestate = Player_Attacking;
		}
		else if (BattleState_PC == Player_Return_Move)
		{
			status_pc.battlestate = Player_Wait;
			//SetBattleState_PC(WaitForMessage);
			status_pc.facing = FacingLeft;
		}
	}


	// TODO : check for event
	if (EventId > 1)
		ChangeScene(EventId);
}

void cManager::DoBattle()
{
	switch (BattleState)
	{
	case Battle_Ready:
		// battle is ready
		// show battle menu
		break;
	case Battle_On:
		//Battle is On.
		// do attack, move, hit, die or win
		break;
	case Battle_Wait:
		//Wait for Battle Message to be shown
		break;
	}

}

//
// methods for set variables
//
void cManager::SetCurScene(int SceneName)
{
	this->CurScene = SceneName;
}

void cManager::SetCurMenu(int menu)
{
	CurMenu = menu;
}

void cManager::SetPC_Direction(int direction)
{
	if (PC_Direction != direction)
		PC_Direction = direction;
}

void cManager::SetPC_State(int state)
{
	PC_State = state;
}

void cManager::SetBattleState_PC(int state)
{
	BattleState_PC = state;
}

void cManager::SetBattleState_Mob(int state)
{
	BattleState_Mob = state;
}

void cManager::SetPC_COORD(int row, int col)
{

	PC_COORD.x = col;
	PC_COORD.y = row;
}

void cManager::SetPC_XY(int row, int col)
{
	PC_XY.x = col * 48;
	PC_XY.y = row * 48;
}

void cManager::SetPC_COORD_NEXT(int row, int col)
{
	PC_COORD_NEXT.x = col;
	PC_COORD_NEXT.y = row;
}

void cManager::SetEventID(int eventID)
{
	this->EventId = eventID;
}



//
// methods for get variables
//
int cManager::GetCurScene()
{
	return CurScene;
}

int cManager::GetCurMenu()
{
	return CurMenu;;
}

int cManager::GetDirection_PC()
{
	return PC_Direction;;
}

int cManager::GetSpeed_PC()
{
	return PC_Speed;;
}

int cManager::GetPC_State()
{
	return PC_State;;
}

int cManager::GetBattleState_PC()
{
	return BattleState_PC;;
}

int cManager::GetBattleState_Mob()
{
	return BattleState_Mob;;
}

POINT cManager::GetPC_XY()
{
	return PC_XY;
}

POINT cManager::GetPC_COORD()
{
	return PC_COORD;;
}

POINT cManager::GetPC_COORD_NEXT()
{
	return PC_COORD_NEXT;
}

int cManager::GetEventID()
{
	return EventId;;
}

STATUS_PC cManager::GetStatus_PC()
{
	return status_pc;
}

STATUS_MOB cManager::GetStatus_MOB()
{
	return status_mob;
}










