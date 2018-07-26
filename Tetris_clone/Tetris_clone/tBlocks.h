#pragma once
#include "Manager.h"

class tBlocks : public Manager
{

public:
	tBlocks();
	void InitTetrimino(int shape, int rotate, std::vector<RECT> *t);
	void Rotate(std::vector<RECT> *t);
	int GetCurX();
	int GetCurY();
	void SetCurX(int newX);
	void SetCurY(int newY);
	void MoveRight(std::vector<RECT> *t);
	void MoveLeft(std::vector<RECT> *t);
	void Down(std::vector<RECT> *t);
	bool CheckRight(std::vector<RECT> *t);
	bool CheckLeft(std::vector<RECT> *t);
	bool CheckBelow(std::vector<RECT> *t);
	bool CheckRotate(std::vector<RECT>* t);
	bool CheckRotate_L();
	//void HardDrop(std::vector<RECT> *t);
	std::vector<int> GetBlockColor(int shape);
	void UpdateTetriminoBoxes(std::vector<RECT> *t);
	void TetriminoToBlocks(std::vector<RECT> *t);
	~tBlocks();
private:
	int CurX;
	int CurY;
	int CurX2;
	int CurY2;
	//7 = ���� ����
	//32 = 4 * 2 * 4 (4ȸ��, 2��ǥ(x,y), 4ĭ�� �Ѽ�Ʈ) 
	int shapes[7][32] = {
		// 0�� = I��
		{ 0,0, -2,0, -1,0, 1,0,		0,0, 0,-2, 0,-1, 0,1,},
		// 1�� = O��
		{ 0,0, -1,-1, 0,-1, -1,0, },
		// 2�� = S��
		{ 0,0, 0,1, -1,0, -1,-1,	0,0, 0,-1, 1,-1, -1,0, },
		// 3�� = Z��
		{ 0,0, 0,-1, 1,0, -1,-1,	0,0, 1,0, 1,-1, 0,1, },
		// 4�� = L�� 
		{ 0,0, 0,-1, 0,-2, 1,0,		0,0, 1,0, 2,0, 0,1,		0,0, 0,1, 0,2, -1,0,	0,0, 0,-1, -1,0, -2,0},
		// 5�� = J��
		{ 0,0, -1,0, 0,-1, 0,-2,	0,0, 1,0, 2,0, 0,-1,	0,0, 0,1, 0,2, 1,0,		0,0, -1,0, -2,0, 0,1 },
		// 6�� - T��
		{ 0,0, 0,1, -1,0, 1,0,		0,0, -1,0, 0,-1, 0,1,	0,0, 0,-1, -1,0, 1,0,	0,0, 1,0, 0,-1, 0,1 } };

	// ����, ��ȿ ȸ�� ��, R, G, B
	int dictionary[7][5] = { 
		{ 0, 2,		200,	25,		25  },
		{ 1, 1,		0,		176,	240 },
		{ 2, 2,		255,	255,	168 },
		{ 3, 2,		200,	100,	255 },
		{ 4, 4,		255,	128,	50  },
		{ 5, 4,		50,		255,	200 },
		{ 6, 4,		25,		200,	25  } };
	
};
