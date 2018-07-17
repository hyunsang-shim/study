#pragma once
#include <vector>

#define SPRITE_WIDTH 25
#define SPRITE_HEIGHT 30
#define PLAYER_SPEED_MAX 15
#define PLAYER_SPEED_MIN 3


enum PlayerStatus {
	IDLE = 0,
	MOVING,
	DRAWING,
	RETURNING,
	DIEING,
	GAMEOVER
};

class Manager
{
	
public:
	std::vector<SIZE> DrawingPosXY;
	Manager();
	~Manager();
	void subLife();
	void AddLifeStock(int life);
	int GetLifeStock();
	int getPLAYER_STATUS();
	void setPLAYER_STATUS(int status);
	int getPLAYER_SPEED();
	void setPLAYER_SPEED(int x);

private:
	int life;
	int PLAYER_STATUS = IDLE;
	int speed = 4;
	int PLAYER_SPEED = PLAYER_SPEED_MIN;

public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

};

