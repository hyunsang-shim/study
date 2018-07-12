#pragma once
#include <vector>
/*

매니져
화면에 그려 주는데, 계속 표시되어야 하는 것들을 관리한다.
또는 지속적인 일관성 있는 관리가 필요할 경우 여기서 관리한다.

*/


#include <windows.h>
#include <string>

#define PI 3.14

//아이디, 텍스트 입력 관련
#define ID_MAX_SIZE 8
#define FONT_SIZE 12
#define LABEL_MARGIN 3

//방어 블럭
#define NUM_OF_GUARDS 15
#define GUARD_HEIGHT 15
#define DEFAULT_GUARD_HP 5

//포탑 관련
#define HEAD_MIN_DEGREE 170
#define HEAD_MAX_DEGREE 10
#define CANNON_LENGTH 60
#define MAX_BULLET_ON_SCREEN 20

enum Scenes {
	eSceneTitle = 0,
	eSceneGame,
	eSceneScore,
	eSceneRetry
};

//총알 객체
typedef struct __bullet_struct
{
	double centerX;
	double centerY;
	int size;
	int speed;
	int power;

} stBullet;

//총알을 담아 둘 배열
std::vector<stBullet> vBullets;

//적들의 구조체
typedef struct __Enemies__
{
	double centerX;
	double centerY;
	int size;
	int speed;
	int HP;
	
} stENEMY;

//적들을 담아 둘 배열
std::vector<stENEMY> vEnemies;

class cGameManager
{
public:
	cGameManager();	
	~cGameManager();
	int getCurrentScene();
	void SetCurrentScene(int scene);
	void SetInputLabel(HWND hwnd);
	void SetInputBox(HWND hwnd);
	RECT GetInputLabel();
	RECT GetInputBox();

public:
	static cGameManager* GetInstance()
	{		
		static cGameManager instance;
		return &instance;
	}

private:
	int CurrentScene = eSceneTitle;
	RECT InputLabel;
	RECT InputBox;
};

