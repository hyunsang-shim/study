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

Manager::~Manager()
{
}
