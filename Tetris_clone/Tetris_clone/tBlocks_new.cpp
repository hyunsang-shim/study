#include "stdafx.h"
#include "tBlocks.h"

tBlocks::tBlocks() {}
tBlocks::~tBlocks() {}

// initialize a new tetrimino
void tBlocks::InitTetrimino(int shape, int rotate, std::vector<RECT> *t)
{
	CurX = TETRIMINO_START_X;
	CurY = TETRIMINO_START_Y;

	t->clear();
	RECT tmp;
	int mod = BOX_SIZE / 2;

	// Calculate the RECTs and push into container (tetrimino)
	// Referenceing dictionary for it's shape
	if (dictionary[shape][1] >= rotate)
	{
		int start = 8 * rotate;
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[shape][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[shape][i + 1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[shape][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[shape][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}
	}
	else
	{
		for (int i = 0; i < 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[shape][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[shape][i + 1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[shape][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[shape][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}
	}

	// sets shape
	SetShape(shape);
	// sets it's rotation
	SetRotation(rotate);
	// sets landing status as false;
	SetUnlanded();
}

// returns current column idx on play_area
int tBlocks::GetCurX() { return CurX; }
// returns current row idx on play_area 
int tBlocks::GetCurY() { return CurY; }
// sets center of Tetrimino's column idx on play_area
void tBlocks::SetCurX(int x) { CurX = x; }
// sets center of Tetrimino's row idx on play_area
void tBlocks::SetCurX(int y) { CurY = y; }

// Rotates Tetrimino
void tBlocks::Rotate(std::vector<RECT> *t)
{
	// check whether can be ratated.
	if (CheckRotate(t))
	{
		// Rotate Tetrimino
		// if there's a next rotation available, increase rotation idx
		if ((dictionary[this->GetShape()][1] > (this->GetRotation() + 1)))
			this->SetRotation(this->GetRotation() + 1);
		// if none, back to first(idx 0) idx
		else
			this->SetRotation(0);	// back to first;
	}
}


// Move tetrimino rightward by 1 if possible
void tBlocks::MoveRight(std::vector<RECT> *t)
{
	if (CheckRight(t))
	{
		CurX++;
	}

	// Updates tetrimino Boxes for drawing
	UpdateTetriminoBoxes(t);
}

// Move tetrimino leftward by 1 if possible
void tBlocks::MoveLeft(std::vector<RECT> *t)
{
	if (CheckLeft(t))
	{
		CurX--;
	}

	// Updates tetrimino Boxes for drawings
	UpdateTetriminoBoxes(t);
}


// Move tetrimino Downward by 1 if possible
void tBlocks::Down(std::vector<RECT> *t)
{
	// tetrimino is landed but not fixed. -> yet can move!
	if (isLanded())
	{	
		// write code as follow.
		// let playarea's attribute to be changed. EMPTY -> OCCUPIED. (fill inside as tetrimino's own color)
		TetriminoToBlocks(t);
		// check the playarea for filled horezontal lines. if it is, delete it if possible.
		// check gameover condition.
		// game isn't over, then add point(score) 
		// gameover -> update Tetrimino image shown on "next" area. 
		// !gameover -> Re-Initialize Tetrimino as shown as "next" area.
		InitTetrimino(GetNextTetrimino(), 0, t);
	}
	else if (CheckBelow(t))
	{
		// add Y Coord.
		CurY++;

		// if can't move again, it's landed.
		// still can move before auto down or input down again
		if (!CheckBelow(t))
		{
			SetLanded();
		}
	}
	else if (!CheckBelow(t))
	{
		SetLanded();
		printf("Landed!!\n");
	}

	// Updates tetrimino Boxes for drawings
	UpdateTetriminoBoxes(t);
}
