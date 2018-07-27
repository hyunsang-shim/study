#include "stdafx.h"
#include "tBlocks.h"

tBlocks::tBlocks() {}
tBlocks::~tBlocks() {}

// initialize a new tetrimino
void tBlocks::InitTetrimino()
{
	// sets shape
	SetShape(GetNextTetriminoId());

	int curShape = GetNextTetriminoId();

	// sets it's rotation
	SetRotation(0);
	// sets landing status as false;
	SetUnlanded();
	// sets next tetrimino's id

	SetNext(curShape + 1);
	CurX = TETRIMINO_START_X;
	CurY = TETRIMINO_START_Y;	
	
	// sets tetrimino info. to the stage(PLAY_AREA_STATUS)
	int start = 8 * (GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		PLAY_AREA_STATUS[CurY + shapes[curShape][i+1] ][CurX + shapes[curShape][i]] = curShape + 2;
	}

	//UpdateTetriminoBoxes(t);
	UpdateTetrimino();

}

// returns current column idx on play_area
int tBlocks::GetCurX() { return CurX; }
// returns current row idx on play_area 
int tBlocks::GetCurY() { return CurY; }
// sets center of Tetrimino's column idx on play_area
void tBlocks::SetCurX(int x) { CurX = x; }
// sets center of Tetrimino's row idx on play_area
void tBlocks::SetCurY(int y) { CurY = y; }

// Rotates Tetrimino
void tBlocks::Rotate()
{

	//
	// generate temporal tetrimino for check.
	POINT points[4];
	int tmp_rotation;

	// get rotation info.
	if ((dictionary[GetShape()][1] > (GetRotation()+1)))
		tmp_rotation = GetRotation() + 1;
	// if none, back to first(idx 0) idx
	else
		tmp_rotation = 0;	// back to first;


	int start = 8 * tmp_rotation;
	int shape = GetShape();

	for (int i = start; i < start + 8; i += 2)
	{
		points[(i % 8) / 2].y = CurY + shapes[shape][(i + 1)];
		points[(i % 8) / 2].x = CurX + shapes[shape][i];
	}
	//
	// generation for temporal tetrimino ends.	//


	// check whether can be ratated.
	if (CheckSpace(points))
	{
		EraseTetrimino();

		// Rotate Tetrimino
		// if there's a next rotation available, increase rotation idx
		if ((dictionary[GetShape()][1] > (GetRotation() + 1)))
			SetRotation(GetRotation() + 1);
		// if none, back to first(idx 0) idx
		else
			SetRotation(0);	// back to first;

		UpdateTetrimino();
	}
}

// Move tetrimino rightward by 1 if possible
void tBlocks::MoveRight()
{
	EraseTetrimino();

	//
	// generate temporal tetrimino for check.
	//
	POINT points[4];
	int start = 8 * (this->GetRotation());
	int shape = GetShape();

	for (int i = start; i < start + 8; i += 2)
	{
		points[(i % 8) / 2].y = CurY + shapes[shape][(i + 1)];
		points[(i % 8) / 2].x = CurX + shapes[shape][i] + 1;
	}
	//
	// generation for temporal tetrimino ends.
	//


	if (CheckSpace(points))
	{
		CurX++;
	}

	UpdateTetrimino();

}

// Move tetrimino leftward by 1 if possible
void tBlocks::MoveLeft()
{
	EraseTetrimino();

	//
	// generate temporal tetrimino for check.
	//
	POINT points[4];
	int start = 8 * (this->GetRotation());
	int shape = GetShape();

	for (int i = start; i < start + 8; i += 2)
	{
		points[(i % 8) / 2].y = CurY + shapes[shape][(i + 1)];
		points[(i % 8) / 2].x = CurX + shapes[shape][i] - 1;
	}
	//
	// generation for temporal tetrimino ends.
	//


	if (CheckSpace(points))
	{
		CurX--;
	}

	UpdateTetrimino();

}

// Move tetrimino Downward by 1 if possible
void tBlocks::Down()
{
	EraseTetrimino();

	//
	// generate temporal tetrimino for check.
	//
	POINT points[4];
	int start = 8 * (this->GetRotation());
	int shape = GetShape();

	for (int i = start; i < start + 8; i += 2)
	{
		points[(i % 8) / 2].y = CurY + shapes[shape][(i + 1)] +1;
		points[(i % 8) / 2].x = CurX + shapes[shape][i];
	}
	//
	// generation for temporal tetrimino ends.
	//

	// tetrimino is landed but not fixed. -> yet can move!
	if (CheckSpace(points))
	{
		// add Y Coord.
		CurY++;
	}
	else
	{
		if (isLanded())
		{
			// check the playarea for filled horezontal lines. if it is, delete it if possible.
			// check gameover condition.
			// game isn't over, then add point(score) 
			// gameover -> update Tetrimino image shown on "next" area. 
			// !gameover -> Re-Initialize Tetrimino as shown as "next" area.
			OccupyPlayArea();
			InitTetrimino();
		}
		else 
			SetLanded();
	}

	UpdateTetrimino();
}

bool tBlocks::CheckSpace(POINT points[])
{
	for (int i = 0; i < 4; i++)
	{
		if ( (PLAY_AREA_STATUS[points[i].y][points[i].x] != EMPTY)
			&& (PLAY_AREA_STATUS[points[i].y][points[i].x] != TETRIMINO) )
			return false;
	}
	return true;
}

void tBlocks::HardDrop()
{
	do {
		Down();
	} while (!isLanded());
}

std::vector<int> tBlocks::GetBlockColor(int shape)
{
	std::vector<int> Color;
	Color.push_back(dictionary[shape][2]);
	Color.push_back(dictionary[shape][3]);
	Color.push_back(dictionary[shape][4]);

	return Color;
}
//
//void tBlocks::UpdateTetriminoBoxes(std::vector<RECT>* t)
//{
//	t->clear();
//	RECT tmp;
//	int mod = BOX_SIZE / 2;
//	int curShape = GetShape();
//
//
//	int start = 8 * (GetRotation());
//	for (int i = start; i < start + 8; i += 2)
//	{
//		tmp.left = GetCurX() + shapes[curShape][i] * BOX_SIZE - mod;
//		tmp.top = GetCurY() + shapes[curShape][i + 1] * BOX_SIZE - mod;
//		tmp.right = GetCurX() + shapes[curShape][i] * BOX_SIZE + mod;
//		tmp.bottom = GetCurY() + shapes[curShape][i + 1] * BOX_SIZE + mod;
//
//		t->push_back(tmp);
//	}
//}

void tBlocks::UpdateTetrimino()
{
	int curShape = GetShape();
	// sets tetrimino info. to the stage(PLAY_AREA_STATUS)
	int start = 8 * (GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		PLAY_AREA_STATUS[CurY + shapes[curShape][i + 1]][CurX + shapes[curShape][i]] = TETRIMINO;
	}
}

void tBlocks::EraseTetrimino()
{
	int curShape = GetShape();
	int start = 8 * (GetRotation());

	for (int i = start; i < start + 8; i += 2)
	{
		PLAY_AREA_STATUS[CurY + shapes[curShape][(i + 1)]][CurX + shapes[curShape][i]] = EMPTY;
	}
}

void tBlocks::OccupyPlayArea()
{
	int curShape = GetShape();
	// sets tetrimino info. to the stage(PLAY_AREA_STATUS)
	int start = 8 * (GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		PLAY_AREA_STATUS[CurY + shapes[curShape][(i + 1)]][CurX + shapes[curShape][i]] = curShape + 2;
	}

}