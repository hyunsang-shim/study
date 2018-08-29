
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

void cManager::Init()
{
	scnManager = new SceneManager;
	scnManager->LoadResource();
	CurScene = TitleScene;
	status_pc.facing = FacingUp;
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
	BattleStep = ShowBattleMenu;

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
void cManager::UpdateScene(HDC FrontDC)
{
	switch (CurScene)
	{
	//case TitleScene:
	//	UpdateTitle();
	//	break;
	case BattleScene:
		UpdateBattle();
		break;
	case TownScene:
		UpdateTown();	
		break;
	}
}

void cManager::DrawScene(HDC FrontDC)
{
	switch (CurScene)
	{
	case TitleScene:
		scnManager->DrawTitleScene(FrontDC);
		TextOut(FrontDC, 100, 100, _T("TitleScene"), lstrlen(_T("TitleScene")));
		break;
	case TownScene:
		scnManager->DrawTownScene(FrontDC);
		break;
	case BattleScene:
		scnManager->DrawBattleScene(FrontDC, &status_pc, &status_mob);
		TCHAR tmp[64];
		wsprintf(tmp, _T("BattleStep : %d"), BattleStep);
		TextOut(FrontDC, 100, 100, tmp, lstrlen(tmp));
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

void cManager::UpdateTitle()
{
}

void cManager::UpdateTown()
{	
	EventId = TownMap[status_pc.coord_y][status_pc.coord_x];

	if (status_pc.movestate == Moving)
		MoveCharacter();

	// Draw Event Scene

		// Town
			// Draw BG
			// Draw PC
		// Shop
	switch (EventId)
	{
		printf("Event id : [ %03d ]\n", EventId);
	case Exit:
		ChangeScene(BattleScene);
		break;
	}
			// Draw BlackBG
			// Draw ShopBG
			// Draw TownMenu(ShopID);
			// Draw Selector(CurMenu);
			// Draw MessageBox_Town	
	
}

void cManager::UpdateBattle()
{

	switch (BattleStep)
	{
		// 1	전투 메뉴 표시	show battle menu for player	
		// 2	플레이어 캐릭터 이동	move player character
	case PC_Move:
		switch (CurMenu)
		{
		case menuAttack:			
			status_pc.facing = FacingLeft;
			break;
		case menuDefense:			
			break;
		default:
			status_pc.facing = FacingRight;
			break;
		}

		MoveCharacter();
		break;
		// 3	플레이어 캐릭터 행동	do player character's action
	case PC_Action:
		SetBattleMessage(&status_pc, &status_mob);
		dmg = calcDamage(&status_pc, &status_mob);
		break;
		// 4	플레이어 캐릭터 행동 결과 출력	show result of PC action
	case PC_Action_Result:
		
	break;
		// 5	몬스터 사망 확인	check whether mob die or not
	case Check_Mob_Die:
		break;
		// 6	몬스터 사망 처리	kill monster
	case Kill_Mob:
		break;
		// 7	경험치 획득	loot XP.
	case Loot_XP:
		break;
		// 8	골드 획득	loot Gold.
	case Loot_Gold:
		break;
		// 9	전리품 획득	loot etc.
	case Loot_etc:
		break;
		// 10	전투 종료->마을 씬 복귀	end battle.Return to town scene
	case Return_To_Town:
		break;
		// 11	플레이어 캐릭터 복귀	return PC to start position
	case PC_Return:
		status_pc.facing = FacingRight;
		status_pc.coord_next_x = BATTLE_POS_PC_DEFAULT_X;
		MoveCharacter();
		break;
		// 12	몬스터 캐릭터 이동	move mob
	case MOB_Move:
		break;
		// 13	몬스터 캐릭터 행동	mob action
	case MOB_Action:
		break;
		// 14	몬스터 캐릭터 행동 결과 출력	show result of mob action
	case MOB_Atcion_Result:
		//		메시지 라인 1
		//		메시지 라인 2
		//		메시지 라인 3
		break;
		// 15	캐릭터 사망 확인	check whether PC die or not
	case Check_PC_Die:
		break;
		// 16	캐릭터 사망 처리	kill PC
	case Kill_PC:
		break;
		// 17	전투 종료->게임오버 씬	end battle.Go to gameover scene.
	case Goto_Gameover:
		break;
	}
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
		switch (BattleStep)
		{
			case ShowBattleMenu:
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
					BattleStep = ShowBattleMenu;
					if (CurMenu == menuAttack)
					{
						status_pc.battlestate = Player_Attack_Move;
						status_pc.movestate = Moving;
						status_pc.coord_next_x = BATTLE_POS_PC_ATTACK_X;
						BattleStep = PC_Move;
					}
					else if (CurMenu == menuDefense)
					{
						status_pc.battlestate = Player_Wait;
						BattleStep = MOB_Move;
					}
					break;
				}
				break;
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
		if (BattleStep == PC_Move)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;
			BattleStep = PC_Action;
			status_pc.battlestate = Player_Attacking;
			scnManager->frameCounter = 0;
			scnManager->frameNumber = 0;
		}
		else if (BattleStep == PC_Return)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;
			BattleStep = ShowBattleMenu;
			status_pc.battlestate = Player_Ready;
			scnManager->frameCounter = 0;
			scnManager->frameNumber = 0;
		}
	}


	// TODO : check for event
	if (EventId > 1)
		ChangeScene(EventId);
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

void cManager::SetUiState_BattleMessageBox(bool val)
{
	UI_state_MSGW = val;
}

void cManager::SetBattleMessage(STATUS_PC *pc, STATUS_MOB *mob)
{
	MSG_Battle.damage = calcDamage(&status_pc, &status_mob);

	// reset message buffers
	memset(MSG_Battle.AttackMessage, 0, sizeof(MSG_Battle.AttackMessage));
	memset(MSG_Battle.AttackResultMessage, 0, sizeof(MSG_Battle.AttackResultMessage));
	memset(MSG_Battle.BattleResultMessage, 0, sizeof(MSG_Battle.BattleResultMessage));

	// set message buffers
	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!"), status_pc.NAME);
	wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 %d의 피해를 주었다."), status_mob.NAME, MSG_Battle.damage);
	wsprintf(MSG_Battle.BattleResultMessage, _T("%s를 쓰러뜨렸다!"), status_mob.NAME);
}
void cManager::SetBattleMessage(STATUS_MOB *mob, STATUS_PC *pc)
{
	MSG_Battle.damage = calcDamage(&status_mob, &status_pc);


	// reset message buffers
	memset(MSG_Battle.AttackMessage, 0, sizeof(MSG_Battle.AttackMessage));
	memset(MSG_Battle.AttackResultMessage, 0, sizeof(MSG_Battle.AttackResultMessage));
	memset(MSG_Battle.BattleResultMessage, 0, sizeof(MSG_Battle.BattleResultMessage));

	// set message buffers
	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!"), status_mob.NAME);
	wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 %d의 피해를 주었다."), status_pc.NAME, MSG_Battle.damage);
	wsprintf(MSG_Battle.BattleResultMessage, _T("%s를 쓰러뜨렸다!"), status_pc.NAME);
}

void cManager::NextBattleStep()
{
	BattleStep++;
}

void cManager::SetBattleStep(int nextstep)
{
	BattleStep = nextstep;
}

void cManager::SetCurMsgLine(short newline)
{
	CurMsgLine = newline;
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


int cManager::GetBattleStep()
{
	return BattleStep;
}


int cManager::GetEventID()
{
	return EventId;;
}

bool cManager::GetUiState_BattleMessageBox()
{
	return UI_state_MSGW;
}

short cManager::GetCurMsgLine()
{
	return CurMsgLine;
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










