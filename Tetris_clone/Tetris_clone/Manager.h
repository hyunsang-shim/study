#pragma once
#include "stdafx.h"

#define BOX_SIZE 30
#define PLAY_AREA_WIDTH 15
#define PLAY_AREA_HEIGHT 23

enum playarea_status {

	EMPTY = 0,
	OCCUPIED,
	WALL,
	GROUND,
	TETRIMINO
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
	void SetPLAY_AREA_STATUS(int row, int col, int val);
	int GetPLAY_AREA_STATUS(int row, int col);	
	void SetShape(int shape);
	void SetRotation(int rotation);
	int GetShape();
	int GetRotation();
	//int GetDownTimer();
	//void SetDownTimer(int value);
	~Manager();

public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

private:
	int PLAY_AREA_STATUS[PLAY_AREA_HEIGHT][PLAY_AREA_WIDTH] = { 0 };
	int Shape;
	int Rotation;
};

