#pragma once

#define SPRITE_WIDTH 25
#define SPRITE_HEIGHT 30
#define PLAYER_SPEED_MAX 15
#define PLAYER_SPEED_MIN 4


enum PlayerStatus {
	IDLE = 0,
	MOVING,
	DRAWING,
	DRAWING_DONE,
	RETURNING,
	DIEING,
	GAMEOVER
};

class Manager
{
	
public:
	Manager();
	~Manager();
	void subLife();
	void AddLifeStock(int life);
	int GetLifeStock();
	int getPLAYER_STATUS();
	void setPLAYER_STATUS(int status);
	int getPLAYER_SPEED();
	void setPLAYER_SPEED(int x);
	int getWidthMax();
	int getHeightMax();
	void setWidthMax(int width);
	void setHeightMax(int height);

private:
	int life;
	int PLAYER_STATUS = IDLE;
	int PLAYER_SPEED = PLAYER_SPEED_MIN;
	int WidthMax;
	int HeightMax;

public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

};

