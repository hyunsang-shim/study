#pragma once
#include "cManager.h"

class BattleManager : public cManager
{
public:
	BattleManager();
	void DoBattle(HDC hdc);	
	void ShowBattleMenu(HDC hdc);
	~BattleManager();


private:
};

