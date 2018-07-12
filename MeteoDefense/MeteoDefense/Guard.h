#pragma once
#include <windows.h>
#include <vector>
#include "cGameManager.h"

class Guard : public cGameManager
{
public:
	Guard();
	void SetGuards(HDC hdc, RECT RectView, int idx);
	void setHp(int hp);
	int getHp();
	void DoDMG(int dmg);
	void DrawGuard(HDC hdc);
	void setDead();
	RECT getmyPos();
	RECT getmyPos_Label();
	
	~Guard();

private:
	int hp;
	RECT MyPos;
	RECT MyPos_Label;
	bool isDead;
};

