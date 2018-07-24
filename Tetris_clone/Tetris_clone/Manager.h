#pragma once
#include "stdafx.h"

#define BOX_SIZE 30
#define PLAY_AREA_WIDTH 12
#define PLAY_AREA_HEIGHT 22




class Manager
{
public:
	Manager();
	~Manager();



public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

private:
	int PLAY_AREA_STATUS[PLAY_AREA_HEIGHT][PLAY_AREA_WIDTH] = { 0 };

};

