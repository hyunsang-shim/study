
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
	scnManager->ShowBattleMenu(tmpDC, &status_pc);
	ReleaseDC(FindWindow(_T("Oneway_Life"), _T("외길인생 : 검투사의 길")), tmpDC);
	
}

void cManager::Init()
{
	scnManager = new SceneManager;
	scnManager->LoadResource();
	CurScene = TitleScene;
	status_pc.facing = FacingRight;
}

void cManager::InitTitleScene()
{
	CurScene = TitleScene;
	status_pc.facing = FacingRight;
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
	BattleState = Battle_Ready;

	status_pc.atk = 10;
	status_pc.def = 1;
	status_pc.hp = 15;
	status_pc.hp_max = 15; 
	status_pc.coord_x = status_pc.coord_next_x = BATTLE_POS_PC_DEFAULT_X;
	status_pc.coord_y = status_pc.coord_next_y = BATTLE_POS_PC_DEFAULT_Y;
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
	status_mob.battlestate = Monster_Ready;

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

		if (EventId > 1)
			switch (EventId)
			{
			case Exit:
				ChangeScene(BattleScene);
				break;
			}
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
		status_pc.facing = FacingRight;
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
		switch (BattleState)
		{
			case Battle_Ready:
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
					BattleState = Battle_On;
					if (CurMenu == menuAttack)
					{
						status_pc.battlestate = Player_Attack_Move;
						status_pc.movestate = Moving;
						status_pc.coord_next_x = BATTLE_POS_PC_ATTACK_X;
					}
					else if (CurMenu == menuDefense)
					{
						status_pc.battlestate = Player_Wait;
					}
					break;
				}
				break;
			}
			break;
			case Battle_End:
			{
				switch (status_pc.battlestate)
				{
				case Player_Win:

					break;
				case Player_Lose:
					BattleState = Battle_End;
					break;
				}
			}
			break;
			case Battle_On:
			{
				if (wParam == VK_ESCAPE)
					ChangeScene(TownScene);
			}
			break;
		}
		break;
	}
}


//
// compute things
//
int cManager::calcDamage(STATUS_PC * pc, STATUS_MOB * mob)
{
	
	return pc->atk - mob->def;
}

int cManager::calcDamage(STATUS_MOB * mob, STATUS_PC * pc)
{
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

	printf("posx : %d ( %d )  Cur coord : %d %d, Next coord : %d %d\n", status_pc.pos_x, status_pc.pos_x/48, status_pc.coord_x, status_pc.coord_y, status_pc.coord_next_x, status_pc.coord_next_y);

	// change character status to Idle whel reaches target position.
	if ((status_pc.pos_x == DestX) && (status_pc.pos_y == DestY))
	{
		if (status_pc.movestate == Moving)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;
			
			if (status_pc.battlestate == Player_Attack_Move)
			{
				status_pc.battlestate = Player_Attacking;
				calcDamage(&status_pc, &status_mob);
			}
			else if (status_pc.battlestate == Player_Return_Move)
			{				
				status_pc.battlestate = Player_Wait;				
				status_mob.battlestate = Monster_Attack_Move;
				status_pc.facing = FacingLeft;
			}
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
		switch (status_pc.battlestate)
		{
		case Player_Ready:
			if (status_pc.hp <= 0)
				status_pc.battlestate = Player_Lose;
			else if (status_mob.hp <= 0)
				status_pc.battlestate = Player_Win;
			break;
		case Player_Attack_Move:
			MoveCharacter();
			break;
		case Player_Attacking:
			status_mob.battlestate = Monster_Hit;	
			break;
		case Player_Wait:
			if (status_mob.battlestate = Monster_Ready);
			// scnManager()->ShowBattleMessage(MSG_Battle);
			else if (status_mob.battlestate = Monster_Attacking)
				status_pc.battlestate = Player_Hit;
			else if (status_mob.battlestate = Monster_Return_Move)
				status_pc.battlestate = Player_Ready;
			break;
		case Player_Return_Move:
			status_mob.battlestate = status_mob.battlestate = Monster_Ready;
			break;
			
		}
	break;
	case Battle_Wait:
		//Wait for Battle Message to be shown
		if (status_pc.battlestate == Player_WaitAttackMessage)
		{
			SetBattleMessage(&status_pc, &status_mob);
			calcDamage(&status_pc, &status_mob);
			BattleState = Battle_PlayerAttackResult;

		}
		else if (status_mob.battlestate == Monster_WaitAttackMessage)
		{
			SetBattleMessage(&status_mob, &status_pc);
			calcDamage(&status_mob, &status_pc);
			BattleState = Battle_MonsterAttackResult;
		}
		break;
	case Battle_PlayerAttackResult:
		if (!UI_state_MSGW)
		{
			/*BattleState = Battle_On;
			status_pc.battlestate = Player_Ready;
			status_mob.battlestate = Monster_Ready;*/
		}
		break;
	case Battle_MonsterAttackResult:
		if (MSG_Battle.damage-- > 0)
		{
			ApplyDamage(&status_pc, 1);
			std::cout<<"MSG_Battle.damage : 공격자 [" << *status_mob.NAME << "] 데미지 [" << MSG_Battle.damage << "]";
			std::cout << "전투 상태 : " << BattleState << " 몬스터 상태 : " << status_pc.battlestate << "\n";
		}
		else
		{
			BattleState = Battle_On;
			status_mob.battlestate = Monster_WaitAttackMessage;
		}

		break;
	}

}

void cManager::ApplyDamage(STATUS_PC * pc, int damage)
{
	status_pc.hp -= damage;
}

void cManager::ApplyDamage(STATUS_MOB * mob, int damage)
{
	status_mob.hp -= damage;
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


void cManager::SetEventID(int eventID)
{
	this->EventId = eventID;
}

void cManager::SetUI_state_MSGW(bool val)
{
	UI_state_MSGW = val;
}

void cManager::SetBattleState(int battleState)
{
	BattleState = battleState;
}

void cManager::SetBattleMessage(STATUS_PC *pc, STATUS_MOB *mob)
{
	MSG_Battle.damage = calcDamage(&status_pc, &status_mob);

	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!\n"), status_pc.NAME);
	wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 %d의 피해를 주었다."), status_mob.NAME, MSG_Battle.damage);
	wsprintf(MSG_Battle.BattleResultMessage, _T("%s를 쓰러뜨렸다!"), status_mob.NAME);
}
void cManager::SetBattleMessage(STATUS_MOB *mob, STATUS_PC *pc)
{
	MSG_Battle.damage = calcDamage(&status_mob, &status_pc);
	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!\n"), status_mob.NAME);
	wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 %d의 피해를 주었다."), status_pc.NAME, MSG_Battle.damage);
	wsprintf(MSG_Battle.BattleResultMessage, _T("%s를 쓰러뜨렸다!"), status_pc.NAME);
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

int cManager::GetBattleState()
{
	return BattleState;;
}


int cManager::GetEventID()
{
	return EventId;;
}

bool cManager::GetUI_state_MSGW()
{
	return UI_state_MSGW;
}

STATUS_PC cManager::GetStatus_PC()
{
	return status_pc;
}

STATUS_MOB cManager::GetStatus_MOB()
{
	return status_mob;
}

BATTLE_MSG cManager::GetBattleMessage()
{
	return MSG_Battle;
}










