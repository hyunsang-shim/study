
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
	history = { 0 };
}

void cManager::InitTownScene()
{
	CurScene = TownScene;
	CurMenu = menuYes;
	BattleStep = NotInBattle;
	EventId = 1;


	status_pc.coord_x = status_pc.coord_next_x = 8;
	status_pc.coord_y = status_pc.coord_next_y = 11;
	status_pc.pos_x = status_pc.coord_next_x * 48;
	status_pc.pos_y = status_pc.coord_next_y * 48;
	status_pc.pos_shadow_x = status_pc.pos_x;
	status_pc.pos_shadow_y = status_pc.pos_y+2;
	status_pc.facing = FacingUp;
	status_pc.movestate = Idle;
	status_pc.battlestate = Player_Wait;
	status_pc.speed = 4;

	CurMsgLine_State[0] = FALSE;
	CurMsgLine_State[1] = FALSE;
	CurMsgLine_State[2] = FALSE;



}

void cManager::InitBattleScene()
{
	CurScene = BattleScene;	
	CurMenu = menuAttack;
	BattleStep = ShowBattleMenu;
	scnManager->SetAnimationFrame(0);

	status_pc.atk = 5;
	status_pc.def = 2;
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
		
	status_mob.atk = 3;
	status_mob.def = -1;
	status_mob.hp = 7;
	status_mob.hp_max = 7;
	status_mob.coord_x = status_mob.coord_next_x = BATTLE_POS_MOB_DEFAULT_X;
	status_mob.coord_y = status_mob.coord_next_y = BATTLE_POS_MOB_DEFAULT_Y;
	status_mob.pos_x = status_mob.coord_next_x * 48;
	status_mob.pos_y = status_mob.coord_next_y * 48;
	status_mob.battlestate = Monster_Ready;	
	status_mob.movestate = Idle;

}

void cManager::InitGameOverScene()
{
	CurScene = GameOverScene;
	CurMsgLine = 1;
}


//
// Scene Update and draw
//
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
		InitGameOverScene();
		break;
	}

}

void cManager::UpdateScene(HDC FrontDC)
{	
	switch (CurScene)
	{
	case BattleScene:
		UpdateBattle();
		break;
	case TownScene:
		UpdateTown();	
		break;
	case GameOverScene:
		UpdateGameOverScene();
		break;
	}
}

void cManager::DrawScene(HDC FrontDC)
{
	switch (CurScene)
	{
	case TitleScene:
		scnManager->DrawTitleScene(FrontDC);
		break;
	case TownScene:
		scnManager->DrawTownScene(FrontDC);
		break;
	case BattleScene:
		scnManager->DrawBattleScene(FrontDC, &status_pc, &status_mob);		
		break;
	case GameOverScene:
		scnManager->DrawGameOverScene(FrontDC);

	}
}


bool cManager::HaveSaveFile()
{
	return false;
}

void cManager::UpdateTitle()
{
	// advance character frames
	scnManager->AddFrameCounter(1);
	int n = 0;
	if (scnManager->GetFrameCounter() % CHARACTER_FRAME_MAX == 0)
	{
		n = scnManager->GetAnimationFrameNumber() + 1;
		if (n >= CHARACTER_FRAME_MAX)
			n = 0;

		scnManager->SetAnimationFrame(n);
	}
}

void cManager::UpdateTown()
{	
	// advance character frames
	scnManager->AddFrameCounter(1);
	int n = 0;
	if (scnManager->GetFrameCounter() % CHARACTER_FRAME_MAX == 0)
	{
		n = scnManager->GetAnimationFrameNumber() + 1;
		if (n >= CHARACTER_FRAME_MAX)
			n = 0;

		scnManager->SetAnimationFrame(n);
	}
	EventId = TownMap[status_pc.coord_y][status_pc.coord_x];

	if (status_pc.movestate == Moving)
		MoveCharacter();

	// Draw Event Scene
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
	// advance character frames
	scnManager->AddFrameCounter(1);
	int n = 0;
	if (scnManager->GetFrameCounter() % CHARACTER_FRAME_MAX == 0)
	{
		n = scnManager->GetAnimationFrameNumber() + 1;
		if (n >= CHARACTER_FRAME_MAX)
			n = 0;

		scnManager->SetAnimationFrame(n);
	}

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
		SetBattleMessage(&status_pc);
		dmg_counter = calcDamage(&status_pc, &status_mob);		
		CurMsgLine = 1;
		CurMsgLine_State[0] = FALSE;
		CurMsgLine_State[1] = FALSE;
		CurMsgLine_State[2] = FALSE;
		break;
		// 4	플레이어 캐릭터 행동 결과 출력	show result of PC action
	case PC_Action_Result:
		scnManager->AddMsgBox_frameNumber();

		if (CurMsgLine == 1 && CurMsgLine_State[0] == TRUE)
			CurMsgLine = 2;
		else if (CurMsgLine == 2 && CurMsgLine_State[1] == TRUE)
			if (0 >= status_mob.hp)
				CurMsgLine = 3;
			else
				CurMsgLine = 200;
		else if (CurMsgLine == 3 && CurMsgLine_State[2] == TRUE)
			CurMsgLine = 100;

		if (CurMsgLine >= 2 && dmg_counter > 0)
		{
			if (scnManager->GetFrameCounter() % 3 == 0)
			{
				status_mob.hp--;
				dmg_counter--;
			}
		}
	break;
		// 5	몬스터 사망 확인	check whether mob die or not
	case Check_Mob_Die:
		if (status_mob.hp <= 0)
		{
			GainLoot();
			scnManager->ResetMsgBox_FrameNumber();
			UI_state_MSGW = FALSE;
			CurMsgLine = 0;
			BattleStep = Kill_Mob;
		}
		else
		{
			BattleStep = PC_Return;
			status_pc.battlestate = Player_Return_Move;
			status_mob.coord_next_x = BATTLE_POS_MOB_ATTACK_X;
			CurMsgLine = 0;
		}
		break;
		// 6	몬스터 사망 처리	kill monster
	case Kill_Mob:
		status_mob.battlestate = Monster_Dying;
		SetBattleMessage_Loot();
		history.monster_killed++;
		break;
		// 7 루팅		
	case Loot:
		// 1	경험치 획득	loot XP.
		// 2	골드 획득	loot Gold.
		// 3	전리품 획득	loot etc. 
		scnManager->AddMsgBox_frameNumber();
		status_mob.battlestate = Monster_Dead;
		status_pc.battlestate = Player_Win;		

		if (CurMsgLine == 1 && CurMsgLine_State[0] == TRUE)
			CurMsgLine = 2;
		else if (CurMsgLine == 2 && CurMsgLine_State[1] == TRUE)
			if (MSG_Battle.damage >= status_mob.hp)
				CurMsgLine = 3;
		else if (CurMsgLine == 3 && CurMsgLine_State[2] == TRUE)
			CurMsgLine = 100;

		break;
		// 8	전투 종료->마을 씬 복귀	end battle.Return to town scene
	case Return_To_Town:
		if (CurMsgLine == 1 && CurMsgLine_State[0] == TRUE)
			CurMsgLine = 2;
		break;
		// 9	플레이어 캐릭터 복귀	return PC to start position
	case PC_Return:
		MoveCharacter();
		break;
		// 10	몬스터 캐릭터 이동	move mob
	case MOB_Move:
		MoveCharacter(&status_mob);
		break;
		// 11	몬스터 캐릭터 행동	mob action
	case MOB_Action:
		SetBattleMessage(&status_mob);
		dmg_counter = calcDamage(&status_mob, &status_pc);
		CurMsgLine = 1;
		CurMsgLine_State[0] = FALSE;
		CurMsgLine_State[1] = FALSE;
		CurMsgLine_State[2] = FALSE;
		break;
		// 12	몬스터 캐릭터 행동 결과 출력	show result of mob action
	case MOB_Action_Result:
		//		메시지 라인 1
		//		메시지 라인 2
		//		메시지 라인 3
		scnManager->AddMsgBox_frameNumber();

		if (CurMsgLine == 2 && CurMsgLine_State[2] == TRUE)
			CurMsgLine = 100; 
		else if (CurMsgLine == 2 && CurMsgLine_State[1] == TRUE)
			if (status_pc.hp <= 0)
				CurMsgLine = 3;
			else
				CurMsgLine = 200;
		else  if (CurMsgLine == 1 && CurMsgLine_State[0] == TRUE)
			CurMsgLine = 2;

		if (CurMsgLine >= 2 && dmg_counter > 0)
		{
			if (scnManager->GetFrameCounter() % 3 == 0)
			{
				status_pc.hp--;
				dmg_counter--;
			}
		}

		if (CurMsgLine == 200 || CurMsgLine == 100)
		{
			BattleStep = Check_PC_Die;
		}
		break;
		// 13	캐릭터 사망 확인	check whether PC die or not
	case Check_PC_Die:
		if (status_pc.hp <= 0)
		{
			scnManager->ResetMsgBox_FrameNumber();
			UI_state_MSGW = FALSE;
			CurMsgLine = 0;
			BattleStep = Kill_PC;
		}
		else
		{
			BattleStep = MOB_Return;
			status_mob.coord_next_x = BATTLE_POS_MOB_DEFAULT_X;
			status_mob.battlestate = Monster_Return_Move;
			CurMsgLine = 0;
		}
		break;
		// 14	캐릭터 사망 처리	kill PC
	case Kill_PC:
		scnManager->AddMsgBox_frameNumber(); 
		SetBattleMessage_Result(Player_Lose);
		status_mob.battlestate = Monster_Wait;
		status_pc.battlestate = Player_Lose;
		break;
		// 15	전투 종료->게임오버 씬	end battle.Go to gameover scene.
	case Goto_Gameover:
		ChangeScene(GameOverScene);
		break;
	case MOB_Return:
		MoveCharacter(&status_mob);
		break;
	}
}

void cManager::UpdateGameOverScene()
{

}

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
		case VK_SPACE:
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
		case VK_RETURN:
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
				case VK_RETURN:
				case VK_SPACE:
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
			case PC_Action_Result:
				if (wParam)
				{
					if (CurMsgLine_State[1] == TRUE && status_mob.hp > 0)
					{							
						status_pc.battlestate = Player_Return_Move;
						status_pc.coord_next_x = BATTLE_POS_PC_DEFAULT_X;
						InitBattleMessage();						
						CurMsgLine = 1;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE;
						BattleStep = PC_Return;
					}
					else if (CurMsgLine_State[2] == TRUE)
					{
						status_mob.battlestate = Monster_Dying;					
						BattleStep = Kill_Mob;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE;
					}
				}
				break;
			case Kill_Mob:
				if (wParam)
				{
					if (CurMsgLine == 100 && CurMsgLine_State[2] == TRUE)
					{						
						CurMsgLine = 1;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE; 
						status_mob.battlestate = Monster_Dead;
						BattleStep = Loot;
					}
				}
				break;
			case Loot:
				if (wParam)
				{
					if (CurMsgLine == 3 && CurMsgLine_State[2] == TRUE)
					{						
						CurMsgLine = 1;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE;

						SetBattleMessage_Result(Player_Win);
						BattleStep = Return_To_Town;

					}
				}
				break;
			case Return_To_Town:
				if (wParam)
				{
					if (CurMsgLine == 2 && CurMsgLine_State[1] == TRUE)
					{
						CurMsgLine = 1;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE;
						ChangeScene(TownScene);
					}
				}
				break;
			case MOB_Action_Result:
				if (wParam)
				{
					if (CurMsgLine_State[2] == TRUE)
					{
						status_pc.battlestate = Player_Lose;
						BattleStep = Check_PC_Die;
					}
					else if (CurMsgLine_State[1] == TRUE && status_pc.hp > 0)
					{
						status_mob.battlestate = Monster_Return_Move;
						InitBattleMessage();
						CurMsgLine = 1;
						CurMsgLine_State[0] = FALSE;
						CurMsgLine_State[1] = FALSE;
						CurMsgLine_State[2] = FALSE;
						BattleStep = MOB_Return;
					}
				}
				break;
			case Kill_PC:
				if (wParam)
				{
					if (CurMsgLine == 2 && CurMsgLine_State[1] == TRUE)
					{
						BattleStep = Goto_Gameover;
					}
					else if (CurMsgLine == 1 && CurMsgLine_State[0] == TRUE)
					{
						CurMsgLine = 2;
					}
					
				}
				break;
		}
		break;
		case GameOverScene:
		{
			if (wParam)
			{
				if (CurMsgLine <= 4)
					CurMsgLine++;
				else
					ChangeScene(TitleScene);
			}
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
	// Move Character from current coordinate to next coordinate.
	// should ignore input while moving

	int DestX = status_pc.coord_next_x * 48;
	int DestY = status_pc.coord_next_y * 48;

	// Set x position
	if (DestX - status_pc.pos_x > 0)
	{
		status_pc.pos_x += status_pc.speed;
		status_pc.pos_shadow_x += status_pc.speed;
	}
	else if (DestX - status_pc.pos_x < 0)
	{
		status_pc.pos_x -= status_pc.speed;
		status_pc.pos_shadow_x -= status_pc.speed;
	}
	
	// Set y position
	if (DestY - status_pc.pos_y > 0)
	{
		status_pc.pos_y += status_pc.speed;
		status_pc.pos_shadow_y += status_pc.speed;
	}
	else if (DestY - status_pc.pos_y < 0)
	{
		status_pc.pos_y -= status_pc.speed;
		status_pc.pos_shadow_y -= status_pc.speed;
	}

	// change character status to Idle when reaches target position.
	if ((status_pc.pos_x == DestX) && (status_pc.pos_y == DestY))
	{

		if (BattleStep == PC_Move)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;
			BattleStep = PC_Action;
			status_pc.battlestate = Player_Attacking;
			scnManager->SetFramecounter(1);
			scnManager->SetAnimationFrame(0);
		}

		if (BattleStep == PC_Return)
		{
			status_pc.movestate = Idle;
			status_pc.coord_next_x = status_pc.coord_x;
			status_pc.coord_next_y = status_pc.coord_y;
			BattleStep = MOB_Move;
			status_pc.battlestate = Player_Ready;
			scnManager->SetFramecounter(1);
			scnManager->SetAnimationFrame(0);
			status_mob.coord_x = BATTLE_POS_MOB_ATTACK_X;
		}

		if (BattleStep == NotInBattle)
		{
			if (status_pc.movestate == Moving)
			{
				status_pc.movestate = Idle;
				status_pc.coord_next_x = status_pc.coord_x;
				status_pc.coord_next_y = status_pc.coord_y;
				scnManager->SetFramecounter(1);
				scnManager->SetAnimationFrame(0);
			}
		}
	}

	// TODO : check for event
	if (EventId > 1)
		ChangeScene(EventId);
}
void cManager::MoveCharacter(STATUS_MOB *mob)
{
	// Move Character from current coordinate to next coordinate.
	// should ignore input while moving

	int DestX = status_mob.coord_next_x * 48;
	int DestY = status_mob.coord_next_y * 48;

	// Set x position
	if (DestX - status_mob.pos_x > 0)
	{
		status_mob.pos_x += 4;
	}
	else if (DestX - status_mob.pos_x < 0)
	{
		status_mob.pos_x -= 4;
	}

	// change character status to Idle whel reaches target position.
	if ((status_mob.pos_x == DestX) && (status_mob.pos_y == DestY))
	{

		if (BattleStep == MOB_Move)
		{
			status_mob.movestate = Idle;
			status_mob.coord_next_x = status_mob.coord_x;
			status_mob.coord_next_y = status_mob.coord_y;
			BattleStep = MOB_Action;
			status_mob.battlestate = Monster_Attacking;
		}

		if (BattleStep == MOB_Return)
		{
			status_mob.movestate = Idle;
			status_mob.coord_next_x = status_mob.coord_x;
			status_mob.coord_next_y = status_mob.coord_y;
			BattleStep = ShowBattleMenu;
			status_mob.battlestate = Monster_Ready;
		}

	}
}


void cManager::ApplyDamage(STATUS_PC *pc, int damage)
{
	status_pc.hp -= damage;
}

void cManager::ApplyDamage(STATUS_MOB *mob, int damage)
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

void cManager::SetBattleMessage(STATUS_PC *pc)
{
	MSG_Battle.damage = calcDamage(&status_pc, &status_mob);

	// reset message buffers
	InitBattleMessage();

	// set message buffers
	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!"), status_pc.NAME);
	if (MSG_Battle.damage >= 1)
	{
		wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 %d의 피해를 주었다!"), status_mob.NAME, MSG_Battle.damage);
	}
	else
		wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게 아무런 피해도 주지 못했다!"), status_mob.NAME);

	if (MSG_Battle.damage >= status_mob.hp)
	{
		wsprintf(MSG_Battle.BattleResultMessage, _T("%s를 쓰러뜨렸다!"), status_mob.NAME);
	}
}
void cManager::SetBattleMessage(STATUS_MOB *mob)
{
	MSG_Battle.damage = calcDamage(&status_mob, &status_pc);
	
	// reset message buffers
	InitBattleMessage();


	// set message buffers
	wsprintf(MSG_Battle.AttackMessage, _T("%s의 공격!"), status_mob.NAME);
	if (MSG_Battle.damage >= 1)
	{
		wsprintf(MSG_Battle.AttackResultMessage, _T("%s에게서 %d의 피해를 입었다."), status_mob.NAME, MSG_Battle.damage);
	}
	else
		wsprintf(MSG_Battle.AttackResultMessage, _T("%s의 공격은 아무런 효과가 없었다!"), status_mob.NAME);

	if (MSG_Battle.damage >= status_pc.hp)
	{		
		wsprintf(MSG_Battle.BattleResultMessage, _T("%s는 체력이 다했다...."), status_pc.NAME);
	}
}
void cManager::InitBattleMessage()
{
	memset(MSG_Battle.AttackMessage, 0, sizeof(MSG_Battle.AttackMessage));
	memset(MSG_Battle.AttackResultMessage, 0, sizeof(MSG_Battle.AttackResultMessage));
	memset(MSG_Battle.BattleResultMessage, 0, sizeof(MSG_Battle.BattleResultMessage));
}

void cManager::SetBattleMessage_Loot()
{
	// reset message buffers
	InitBattleMessage_Loot();

	// set message buffers
	wsprintf(MSG_Battle_Loot.Exp, _T("%d의 경험치를 얻었다!"), status_mob.hp_max);
	wsprintf(MSG_Battle_Loot.Gold, _T("%d의 골드를 얻었다!"), status_mob.hp_max / 3);
	wsprintf(MSG_Battle_Loot.Fame, _T("%d의 명성을 얻었다!"), (status_mob.hp_max / 10) > 1 ? status_mob.hp_max / 10 : 1);
}

void cManager::SetBattleMessage_Result(short PlayerBattleState)
{
	// reset message buffer
	InitBattleMessage_Result();

	// set message buffers
	switch (PlayerBattleState)
	{
	case Player_Win:
		wsprintf(MSG_Battle_Result.Result, _T("전투에서 승리했다!"));
		wsprintf(MSG_Battle_Result.Move, _T("오늘도 보람찬 하루였다. 마을로 돌아가자."));
		break;
	case Player_Lose:
		wsprintf(MSG_Battle_Result.Result, _T("전투에서 패배했다..."));
		wsprintf(MSG_Battle_Result.Move, _T("내 인생은... 이렇게 끝났다..."));
		break;
	}

}

void cManager::InitBattleMessage_Result()
{
	memset(MSG_Battle_Result.Result, 0, sizeof(MSG_Battle_Result.Result));
	memset(MSG_Battle_Result.Move, 0, sizeof(MSG_Battle_Result.Move));
}

void cManager::InitBattleMessage_Loot()
{
	memset(MSG_Battle_Loot.Exp, 0, sizeof(MSG_Battle_Loot.Exp));
	memset(MSG_Battle_Loot.Gold, 0, sizeof(MSG_Battle_Loot.Gold));
	memset(MSG_Battle_Loot.Fame, 0, sizeof(MSG_Battle_Loot.Fame));
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

void cManager::SetCurMsgLine_state(short idx, bool value)
{
	CurMsgLine_State[idx - 1] = value;
}

void cManager::GainLoot()
{
	status_pc.Exp = status_mob.hp_max;
	history.exp_earned += status_mob.hp_max;
	status_pc.Gold = status_mob.hp_max / 3;
	status_pc.Fame = (status_mob.hp_max / 10) > 1 ? status_mob.hp_max / 10 : 1;
	history.fame_earned = (status_mob.hp_max / 10) > 1 ? status_mob.hp_max / 10 : 1;
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

bool cManager::GetCurMsgLine_state(short idx)
{
	return CurMsgLine_State[idx-1];
}

HISTORY cManager::GetHistory()
{
	return history;
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

LOOT_MSG cManager::GetBattleMessage_Loot()
{
	return MSG_Battle_Loot;
}

RESULT_MSG cManager::GetBattleMessage_Result()
{
	return MSG_Battle_Result;
}










