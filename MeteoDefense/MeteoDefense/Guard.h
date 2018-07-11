#pragma once
#include <windows.h>
#include <vector>
#include "cGameManager.h"

class Guard : public cGameManager
{
public:
	Guard();
	void SetGuards(HDC hdc, RECT RectView, std::vector<Guard> vector, int idx);
	void setHp(int idx, int hp);
	RECT getmyPos();
	int getHp();
	
	~Guard();

private:
	int hp;
	RECT MyPos;
};

