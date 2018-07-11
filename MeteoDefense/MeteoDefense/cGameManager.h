#pragma once
#include <windows.h>
#include <string>

#define PI 3.14
#define ID_MAX_SIZE 8
#define NUM_OF_GUARDS 15
#define GUARD_HEIGHT 15


enum screen_modes {
	scene_title = 0,
	scene_game,
	scene_score
};


class cGameManager
{
public:
	cGameManager();	
	TCHAR getID();
	void setID(TCHAR *id);
	~cGameManager();	


public:
	static cGameManager* GetInstance()
	{
		static cGameManager instance;
		return &instance;
	}

private:
	TCHAR id[ID_MAX_SIZE];
	unsigned long int Gold;

};

