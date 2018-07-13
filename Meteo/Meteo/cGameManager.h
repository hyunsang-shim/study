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
#define GUARD_HEIGHT 20
#define DEFAULT_GUARD_HP 5
#define GUARD_POS_TOP_MODIFIER 160

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



//적들의 구조체
typedef struct __Enemies__
{
	double centerX;
	double centerY;
	int size;
	int speed;
	int HP;
	
} stENEMY;

typedef struct __Guards__
{
	RECT MyPos;
	int CurHP;
	int MaxHP;
	SIZE Label_HP;
} stGUARD;



class cGameManager
{
public:
	cGameManager();	
	~cGameManager();
	
	// GET 메서드 모음
	int getCurrentScene();
	RECT GetInputLabel();
	RECT GetInputBox();
	TCHAR* GetPLAYER_ID();
	int GetPLAYER_SCORE();
	RECT GetPosDisplayLabel_ID();
	RECT GetPosDisplayLabel_Score();

	// SET 메서드 모음
	void SetCurrentScene(int scene);
	void SetInputArea(HWND hwnd);
	void SetPLAYER_ID(TCHAR* id);
	void SetPlayer_Dead();	
	void SetGuard(HDC hdc, RECT *screen, stGUARD *thisGuard, int id);
	void SetPosDisplayLabel_ID(RECT *screen);
	void SetPosDisplayLabel_Score(RECT *screen);

	//점수 관련
	void AddScore(UINT score);


public:
	static cGameManager* GetInstance()
	{
		static cGameManager instance;

		return &instance;
	}

private:
	int CurrentScene = eSceneTitle;
	TCHAR PLAYER_ID[ID_MAX_SIZE];
	UINT PLAYER_SCORE = 0;
	

	//이름 입력용 위치값들
	RECT posInputLabel;
	RECT posInputBox;

	//이름 표시용 위치값
	RECT posDisplayLabel_ID;
	RECT posDisplayLabel_Score;

	bool isPlayerDead = false;



};

