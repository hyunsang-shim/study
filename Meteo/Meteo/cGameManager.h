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
#define GUARD_HEIGHT 15
#define DEFAULT_GUARD_HP 5

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

//�Ѿ��� ��� �� �迭
std::vector<stBullet> vBullets;

//������ ����ü
typedef struct __Enemies__
{
	double centerX;
	double centerY;
	int size;
	int speed;
	int HP;
	
} stENEMY;

//������ ��� �� �迭
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

