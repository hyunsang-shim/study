#pragma once
#include "Manager.h"

class tBlocks : public Manager
{

public:
	tBlocks();
	void InitTetrimino();
	void Rotate();
	int GetCurX();
	int GetCurY();
	void SetCurX(int newX);
	void SetCurY(int newY);
	void MoveRight();
	void MoveLeft();
	void Down();
	bool CheckSpace(POINT points[]);
	void HardDrop();
	std::vector<int> GetBlockColor(int shape);
	//void UpdateTetriminoBoxes(std::vector<RECT> *t);
	void UpdateTetrimino();
	void EraseTetrimino();
	void OccupyPlayArea();
	~tBlocks();
private:
	int CurX;
	int CurY;
	//7 = 블럭 외형
	//32 = 4 * 2 * 4 (4회전, 2좌표(x,y), 4칸씩 한세트) 
	int shapes[7][32] = {
		// 0번 = I자
		{ 0,0, -2,0, -1,0, 1,0,		0,0, 0,-2, 0,-1, 0,1,},
		// 1번 = O자
		{ 0,0, -1,-1, 0,-1, -1,0, },
		// 2번 = S자
		{ 0,0, 0,1, -1,0, -1,-1,	0,0, 0,-1, 1,-1, -1,0, },
		// 3번 = Z자
		{ 0,0, 0,-1, 1,0, -1,-1,	0,0, 1,0, 1,-1, 0,1, },
		// 4번 = L자 
		{ 0,0, 0,-1, 0,-2, 1,0,		0,0, 1,0, 2,0, 0,1,		0,0, 0,1, 0,2, -1,0,	0,0, 0,-1, -1,0, -2,0},
		// 5번 = J자
		{ 0,0, -1,0, 0,-1, 0,-2,	0,0, 1,0, 2,0, 0,-1,	0,0, 0,1, 0,2, 1,0,		0,0, -1,0, -2,0, 0,1 },
		// 6번 - T자
		{ 0,0, 0,1, -1,0, 1,0,		0,0, -1,0, 0,-1, 0,1,	0,0, 0,-1, -1,0, 1,0,	0,0, 1,0, 0,-1, 0,1 } };

	// 외형, 유효 회전 수, R, G, B
	int dictionary[7][5] = { 
		{ 0, 2,		200,	25,		25  },
		{ 1, 1,		0,		176,	240 },
		{ 2, 2,		255,	255,	168 },
		{ 3, 2,		200,	100,	255 },
		{ 4, 4,		255,	128,	50  },
		{ 5, 4,		50,		255,	200 },
		{ 6, 4,		25,		200,	25  } };
	
};

