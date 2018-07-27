#pragma once
#include "stdafx.h"

#define BOX_SIZE 30
#define PLAY_AREA_WIDTH 15
#define PLAY_AREA_HEIGHT 23
#define PLAY_AREA_LEFT_MARGIN 15

enum playarea_status {
		
	EMPTY = 0,
	TETRIMINO, 
	OCCUPIED_0,
	OCCUPIED_1,
	OCCUPIED_2,
	OCCUPIED_3,
	OCCUPIED_4,
	OCCUPIED_5,
	OCCUPIED_6,		
	WALL,
	GROUND
};

enum tetrimino_shape {
	shape_I = 0,
	shape_O,
	shape_S,
	shape_Z,
	shape_L,
	shape_J,
	shape_T
};

enum move_dirs {
	move_left = -1,
	move_right = 1,
	move_down = 1,
	move_up = -1
};
class Manager
{
public:
	Manager();	
	void SetShape(int shape);
	void SetRotation(int rotation);
	int GetShape();
	int GetRotation();
	void SetLanded();
	void SetUnlanded();
	bool isLanded();
	void SetDownSpeed(int speed);
	int GetDownSpeed();
	//int GetDownTimer();
	//void SetDownTimer(int value);
	int PLAY_AREA_STATUS[PLAY_AREA_HEIGHT][PLAY_AREA_WIDTH] = { 0 };
	~Manager();

public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

private:	
	int Shape;
	int Rotation;
	bool LandingState;
	int DownSpeed = 1000;
};