#include "stdafx.h"
#include "Manager.h"


Manager::Manager()
{
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

			if (i == (PLAY_AREA_HEIGHT - 1))
				PLAY_AREA_STATUS[i][j] = WALL;

			if ((j == 0) || (j == (PLAY_AREA_WIDTH - 1)))
				PLAY_AREA_STATUS[i][j] = GROUND;
		}
	}
}

Manager::~Manager()
{
}
