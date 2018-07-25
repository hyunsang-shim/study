#include "stdafx.h"
#include "Manager.h"


Manager::Manager()
{
	for (int i = 0; i < PLAY_AREA_HEIGHT; i++)
		for (int j = 0; j < PLAY_AREA_WIDTH; j++)
		{
			PLAY_AREA_STATUS[i][j] = EMPTY;

			if (i == (PLAY_AREA_HEIGHT - 1))
				PLAY_AREA_STATUS[i][j] = WALL;

			if ((j == 0) || (j == (PLAY_AREA_WIDTH - 1)))
				PLAY_AREA_STATUS[i][j] = GROUND;
		}	

}

void Manager::SetPLAY_AREA_STATUS(int row, int col, int val)
{
	PLAY_AREA_STATUS[row][col] = val;
}

int Manager::GetPLAY_AREA_STATUS(int row, int col)
{
	return PLAY_AREA_STATUS[row][col];
}

void Manager::SetShape(int shape)
{
	this->Shape = shape;
}

void Manager::SetRotation(int rotation)
{
	this->Rotation = rotation;
}

int Manager::GetShape()
{
	return this->Shape;
}

int Manager::GetRotation()
{
	return this->Rotation;
}

//int Manager::GetDownTimer()
//{
//	return DownTimer;
//}
//
//void Manager::SetDownTimer(int value)
//{
//	DownTimer = value;
//}


Manager::~Manager()
{
}
