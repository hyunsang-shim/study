#include "stdafx.h"
#include "Manager.h"


Manager::Manager()
{
	NewPlayArea();
	SetNextTetriminos();
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

void Manager::SetLanded()
{
	this->LandingState = true;
}

void Manager::SetUnlanded()
{
	this->LandingState = false;

}

bool Manager::isLanded()
{
	return LandingState;
}

void Manager::SetDownSpeed(int speed)
{
	DownSpeed = speed;
}

int Manager::GetDownSpeed()
{
	return DownSpeed;
}

void Manager::NewPlayArea()
{
	for (int i = 0; i < PLAY_AREA_HEIGHT; i++)
	{
		for (int j = 0; j < PLAY_AREA_WIDTH; j++)
		{
			PLAY_AREA_STATUS[i][j] = EMPTY;

			if (j == 0 || j == (PLAY_AREA_WIDTH-1))
				PLAY_AREA_STATUS[i][j] = WALL;

			if (i == (PLAY_AREA_HEIGHT-1))
				PLAY_AREA_STATUS[i][j] = GROUND;

		}
	}
}

void Manager::SetNextTetriminos()
{
	std::vector<int> tmp;

	for (int i = 0; i < 8; i++)	tmp.push_back(i);

	for (int i = 0; i < 7; i++)
	{
		int idx = rand() % (8 - i);
		//printf("8-i = %d, i = %d, idx = %d\n", 8-i, i, idx);
		NextTetriminos[i] = tmp.at(idx);
		printf("NextTetriminos[%d] : %d\n", i, NextTetriminos[i]);
		tmp.erase(tmp.begin() + idx);		
	}
}

void Manager::SetNext(int nextId)
{
	if (nextId > 6)
	{
		SetNextTetriminos();
		NextTetriminoId = 0;
	}
	else
	NextTetriminoId = nextId;
}

int Manager::GetNextTetriminoId()
{
	return NextTetriminoId;
}

Manager::~Manager()
{
}
