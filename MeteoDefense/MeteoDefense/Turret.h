#pragma once
#include <Windows.h>
#include "cGameManager.h"
class Turret : public cGameManager
{
public:
	Turret();
	~Turret();
	void InitTurret();
	void shoot();
	double getSPS();
	void LvUpSPS();
	void LvUpATK();
	void setBasePos(HWND hwnd, RECT rect);
	void DrawPlayer(HDC hdc, LPARAM *lParam) const;
	double GetHeadX();
	double GetHeadY();
	double GetRootX();
	double GetRootY();
	void setHeadX(double x);
	void setHeadY(double Y);




private:
	double RootPosX;
	double RootPosY;
	double HeadPosX;
	double HeadPosY;
	int ATTACK;
	int ShotMax;
	double CUR_SPS;
	const int MAX_SPS = 5;
	const int MIN_SPS = 0.5;
	int LvATK;
	int LvSPD;
	const int LvATK_MAX = 99;
	const int LvSPD_MAX = 99;
};

