#include "stdafx.h"
#include "Manager.h"


Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::subLife()
{
	life--;

	if (life < 0)
		life = 0;
}

void Manager::AddLifeStock(int life)
{
	this->life += life;
}

int Manager::GetLifeStock()
{
	return this->life;
}

int Manager::getPLAYER_STATUS()
{
	return this->PLAYER_STATUS;
}

void Manager::setPLAYER_STATUS(int status)
{
	this->PLAYER_STATUS = status;
}

int Manager::getPLAYER_SPEED()
{
	return this->PLAYER_SPEED;
}

void Manager::setPLAYER_SPEED(int x)
{
	this->PLAYER_SPEED = x;
}
