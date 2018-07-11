#pragma once
class Turret
{
public:
	Turret();
	~Turret();

private:
	int ATTACK;
	int ShotMax;
	int CUR_SPS = 1;
	const int MAX_SPS = 10;
	const int MIN_SPS = 1;
	int LvATK;
	int LvSPD;

};

