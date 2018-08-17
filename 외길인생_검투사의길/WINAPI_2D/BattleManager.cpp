#include "stdafx.h"
#include "BattleManager.h"


BattleManager::BattleManager()
{
}


// Main Battle Loop
void BattleManager::DoBattle(HDC hdc)
{

	if (GetCurScene() != BattleScene)
		return;
	else
	{
		switch (GetPC_State())
		{
		case Ready:
			ShowBattleMenu(hdc);
		}
	}

	/*

	// take Exception
	 if curScene != battleScene
		return;
	 else
	 {
			switch(GetPC_State())
			{
				case Ready:
					show Battle Menu;
					wait for user input
					if return is an input, process the action (attack or defense)
					break;

					case Attacking:
						start PC's action
							start attack animation
							start attack fx(PC side)
							start attack fx(target side)
							show result - hit
							show result - damage
							show result - die or alive
								die - change state to win
								die - battle win process							
								alive - start target's action
									alive - start attack animation
									alive - start attack fx(target side)
									alive - start attack fx(PC side)
									alive - show result - hit
									alive - show result - damage
									alive - show result - die or alive
					break;
					case Win:
							start win animation (PC)
							show loot(s)
							change scene to town
					break;
					case Die:
						change scene to gameover
						show gameover menu
						wait for user input
							input - to title screen : change scene to title screen
							input - quit game : quit game
					break;
			}
		}
	*/


}


void BattleManager::ShowBattleMenu(HDC hdc)
{

}


BattleManager::~BattleManager()
{
}
