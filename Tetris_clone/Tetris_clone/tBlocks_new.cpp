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

bool tBlocks::CheckRight(std::vector<RECT>* t)
{

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		//현재 테트리모 칸 +1 위치값이 빈 칸 또는 자신이 아니면
		if ( (PLAY_AREA_STATUS[ CurY + ( i + 1 ) ][ CurX + i + 1 ] != EMPTY) 
			|| (PLAY_AREA_STATUS[ CurY + ( i + 1 ) ][ CurX + i + 1 ] != TETRIMINO) )
			return false;
	}
	return true;
}

bool tBlocks::CheckLeft(std::vector<RECT>* t)
{
	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((PLAY_AREA_STATUS[CurY + (i + 1)][CurX + i - 1] != EMPTY) 
			|| (PLAY_AREA_STATUS[CurY + (i + 1)][CurX + i - 1 ] != TETRIMINO))
			return false;
	}
	return true;
}

bool tBlocks::CheckBelow(std::vector<RECT>* t)
{
	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((PLAY_AREA_STATUS[CurY + (i + 1) + 1 ][CurX + i] != EMPTY)
			|| (PLAY_AREA_STATUS[CurY + (i + 1) +1 ][CurX + i] != TETRIMINO))
			return false;
	}
	return true;
}

bool tBlocks::CheckRotate(std::vector<RECT>* t)
{
	bool chk = false;

	int oldRotation = GetRotation();

	if ((dictionary[this->GetShape()][1] >(this->GetRotation() + 1)))
		this->SetRotation(this->GetRotation() + 1);
	else
		this->SetRotation(0);	// restart from the beginning.

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((PLAY_AREA_STATUS[CurY + (i + 1)][CurX + i] != EMPTY)
			|| (PLAY_AREA_STATUS[CurY + (i + 1)][CurX + i] != TETRIMINO))
			chk = false;
	}
	chk = true;


	SetRotation(oldRotation);
	return chk;
}

std::vector<int> tBlocks::GetBlockColor(int shape)
{
	std::vector<int> Color;
	Color.push_back(dictionary[shape][2]);
	Color.push_back(dictionary[shape][3]);
	Color.push_back(dictionary[shape][4]);

	return Color;
}

void tBlocks::UpdateTetriminoBoxes(std::vector<RECT>* t)
{
	t->clear();
	Rect tmp;
	int mod = BOX_SIZE / 2;

	int start = 8 * (GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		tmp.left = GetCurX() + shapes[shape][i] * BOX_SIZE - mod;
		tmp.top = GetCurY() + shapes[shape][i + 1] * BOX_SIZE - mod;
		tmp.right = GetCurX() + shapes[shape][i] * BOX_SIZE + mod;
		tmp.bottom = GetCurY() + shapes[shape][i + 1] * BOX_SIZE + mod;

		t->push_back(tmp);
	}
}

void tBlocks::TetriminoToBlocks(std::vector<RECT>* t)
{
	// Tetrimino into Blocks.
	// make tetrimino immobilize and set it to playarea's block (Occupied)

	// set playarea attribute EMPTY -> OCCUPIED

	for (int i = 0; i < 4; i++)
	{
		int col = ((t->begin() + i)->left + BOX_SIZE / 2) / BOX_SIZE;
		int row = ((t->begin() + i)->top + BOX_SIZE / 2) / BOX_SIZE;

		PLAY_AREA_STATUS[row][col] = GetShape()+2;
	}

}
