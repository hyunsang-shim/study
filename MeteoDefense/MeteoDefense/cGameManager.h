#pragma once
#include <windows.h>
#include <string>

#define PI 3.14
#define ID_MAX_SIZE 8
#define FONT_SIZE 12
#define NUM_OF_GUARDS 15
#define GUARD_HEIGHT 15
#define DEFAULT_GUARD_HP 5
#define GUARD_POS_TOP_MODIFIER 160
#define LABEL_MARGIN 3
#define HEAD_MIN_DEGREE 170
#define HEAD_MAX_DEGREE 10
#define CANNON_LENGTH 60


enum screen_modes {
	scene_title = 0,
	scene_game,
	scene_score
};

enum game_status {
	ready = 0,
	play,
	gameover,
};


class cGameManager
{
public:
	cGameManager();	
	TCHAR getID();
	void setID(TCHAR *id);
	RECT getIdLabel();
	RECT getPLAY_AREA();
	void setPLAY_AREA(HWND hwnd);
	~cGameManager();	
	virtual void DrawPlayer(HDC hdc, LPARAM* lParam) const;

public:
	static cGameManager* GetInstance()
	{
		static cGameManager instance;
		return &instance;
	}

private:
	TCHAR id[ID_MAX_SIZE];
	unsigned long int Gold;
	RECT PLAY_AREA;

};

