#pragma once
#include <vector>
/*

�Ŵ���
ȭ�鿡 �׷� �ִµ�, ��� ǥ�õǾ�� �ϴ� �͵��� �����Ѵ�.
�Ǵ� �������� �ϰ��� �ִ� ������ �ʿ��� ��� ���⼭ �����Ѵ�.

*/


#include <windows.h>
#include <string>

#define PI 3.14

//���̵�, �ؽ�Ʈ �Է� ����
#define ID_MAX_SIZE 8
#define FONT_SIZE 12
#define LABEL_MARGIN 3

//��� ��
#define NUM_OF_GUARDS 15
#define GUARD_HEIGHT 20
#define DEFAULT_GUARD_HP 5
#define GUARD_POS_TOP_MODIFIER 160

//��ž ����
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

//�Ѿ� ��ü
typedef struct __bullet_struct
{
	double centerX;
	double centerY;
	int size;
	int speed;
	int power;

} stBullet;



//������ ����ü
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
	
	// GET �޼��� ����
	int getCurrentScene();
	RECT GetInputLabel();
	RECT GetInputBox();
	TCHAR* GetPLAYER_ID();
	int GetPLAYER_SCORE();
	RECT GetPosDisplayLabel_ID();
	RECT GetPosDisplayLabel_Score();

	// SET �޼��� ����
	void SetCurrentScene(int scene);
	void SetInputArea(HWND hwnd);
	void SetPLAYER_ID(TCHAR* id);
	void SetPlayer_Dead();	
	void SetGuard(HDC hdc, RECT *screen, stGUARD *thisGuard, int id);
	void SetPosDisplayLabel_ID(RECT *screen);
	void SetPosDisplayLabel_Score(RECT *screen);

	//���� ����
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
	

	//�̸� �Է¿� ��ġ����
	RECT posInputLabel;
	RECT posInputBox;

	//�̸� ǥ�ÿ� ��ġ��
	RECT posDisplayLabel_ID;
	RECT posDisplayLabel_Score;

	bool isPlayerDead = false;



};

