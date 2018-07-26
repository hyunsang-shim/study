#include "stdafx.h"
#include "tBlocks.h"


tBlocks::tBlocks()
{
	for (int i = 0; i < PLAY_AREA_HEIGHT; i++)
	{
		for (int j = 0; j < PLAY_AREA_WIDTH; j++)
		{
			PLAY_AREA_STATUS[i][j] = EMPTY;

			if (i == (PLAY_AREA_HEIGHT - 1))
				PLAY_AREA_STATUS[i][j] = WALL;

			if ((j == 0) || (j == (PLAY_AREA_WIDTH - 1)))
				PLAY_AREA_STATUS[i][j] = GROUND;
		}
	}
}


void tBlocks::InitTetrimino(int shape, int rotate, std::vector<RECT> *t)
{
	CurX = PLAY_AREA_WIDTH / 2 * BOX_SIZE + PLAY_AREA_LEFT_MARGIN;
	CurY = 1 * BOX_SIZE;

	t->clear();
	RECT tmp;
	int mod = BOX_SIZE / 2;

	if (dictionary[shape][1] >= rotate)
	{
		int start = 8 * rotate;
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[shape][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[shape][i+1] * BOX_SIZE - mod;
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
			tmp.top = GetCurY() + shapes[shape][i+1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[shape][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[shape][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}
	}

	SetShape(shape);
	SetRotation(rotate);
	SetUnlanded();
}


int tBlocks::GetCurX()	{	return CurX;	}
int tBlocks::GetCurY()	{	return CurY;	}
void tBlocks::SetCurX(int newX)	{	CurX = newX;	}
void tBlocks::SetCurY(int newY)	{	CurY = newY;	}

void tBlocks::Rotate(std::vector<RECT> *t)
{
	//회전할 수 있으면
	if (CheckRotate(t))
	{
		//회전을 진행한다.
		// 더 회전할 수 있으면 테트리미노를 회전시킨다.
		if ((dictionary[this->GetShape()][1] > (this->GetRotation() + 1)))
			this->SetRotation(this->GetRotation() + 1);
		else
			this->SetRotation(0);	// 끝까지 갔으면 처음으로
	}
}


void tBlocks::MoveRight(std::vector<RECT> *t)
{
	if (CheckRight(t))
	{
		// printf("Move : x = %d, y = %d  -->  ", CurX, CurY);
		CurX += BOX_SIZE;
		// printf("Move : x = %d, y = %d\n", CurX, CurY);
	}

	UpdateTetriminoBoxes(t);
}
void tBlocks::MoveLeft(std::vector<RECT> *t)
{
	if (CheckLeft(t))
	{
		printf("Move : x = %d, y = %d  -->  ", CurX, CurY);
		CurX = CurX - BOX_SIZE;
		CurY = CurY;
		printf("Move : x = %d, y = %d\n", CurX, CurY);
	}

	UpdateTetriminoBoxes(t);
}


void tBlocks::Down(std::vector<RECT> *t)
{
	// tetrimino is landed but not fixed. -> yet can move!
	if (isLanded())
	{
		// for console output.
		printf("BOOM!!!\n");
		// write code as follow.
		// let playarea's attribute to be changed. EMPTY -> OCCUPIED. (fill inside as tetrimino's own color)
		TetriminoToBlocks(t);
		// check the playarea for filled horezontal lines. if it is, delete it if possible.
		// check gameover condition.
		// game isn't over, then add point(score) 
		// gameover -> update Tetrimino image shown on "next" area. 
		// !gameover -> Re-Initialize Tetrimino as shown as "next" area.
		InitTetrimino(rand()%7, 0, t);
	}
	else if (CheckBelow(t))
	{	
		// add Y Coord.
		CurY += BOX_SIZE;

		// if can't move again, it's landed.
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

	UpdateTetriminoBoxes(t);
}



bool tBlocks::CheckRight(std::vector<RECT>* t)
{
	int mod = BOX_SIZE / 2;

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod) > ((PLAY_AREA_WIDTH - 2) * BOX_SIZE))
			return false;
	}
	return true;
}


bool tBlocks::CheckLeft(std::vector<RECT>* t)
{
	int mod = BOX_SIZE / 2;

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE - mod ) < BOX_SIZE + PLAY_AREA_LEFT_MARGIN)
			return false;
	}
	return true;
}


bool tBlocks::CheckBelow(std::vector<RECT>* t)
{
	for (int i = 0; i < 4; i++)
	{
		int col = ((t->begin() + i)->left + BOX_SIZE / 2) / BOX_SIZE;
		int row = ((t->begin() + i)->top + BOX_SIZE / 2) / BOX_SIZE + 1;
		
		if ( (GetCurY() + (shapes[this->GetShape()][i]) * BOX_SIZE + BOX_SIZE/2) > ((PLAY_AREA_HEIGHT - 2) * BOX_SIZE) - BOX_SIZE)
		{
			return false;
		}
		if (PLAY_AREA_STATUS[row][col] != EMPTY)
		{
			return false;
		}	
		
	}
	return true;
}


bool tBlocks::CheckRotate(std::vector<RECT>* t)
{
	bool chk = false;
	// for the check, just rotate once.
	// when check is completed, return is needed
	int oldRotation = GetRotation();

	if ((dictionary[this->GetShape()][1] >(this->GetRotation() + 1)))
		this->SetRotation(this->GetRotation() + 1);
	else
		this->SetRotation(0);	// restart from the beginning.

	int mod = BOX_SIZE / 2;
	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		// check right whether it's possible
		if ( (GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE) > ((PLAY_AREA_WIDTH - 2) * BOX_SIZE) - mod)
		{
			chk = false;
			this->SetRotation(oldRotation);
			break;
		}
		// check left whether it's possible
		else if ( (GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE) < BOX_SIZE)
		{ 
			chk = false;
			this->SetRotation(oldRotation);
			break;
		}
		// check below whether it's possible
		else if ((GetCurY() + shapes[this->GetShape()][i] * BOX_SIZE) > ((PLAY_AREA_HEIGHT - 2) * BOX_SIZE))
		{
			chk = false;
			this->SetRotation(oldRotation);
			break;
		}
		else
			chk = true;
	}

	//Completed the Check, return it to the former shape.
	this->SetRotation(oldRotation);
	return chk;
	
}

bool tBlocks::CheckRotate_L()
{
	if ((dictionary[this->GetShape()][1] >(this->GetRotation() + 1)))
		this->SetRotation(this->GetRotation() + 1);
	else
		this->SetRotation(0);	// 끝까지 갔으면 처음으로

	int mod = BOX_SIZE / 2;

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod) < BOX_SIZE )
			return false;
	}
	return true;
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
	RECT tmp;
	int mod = BOX_SIZE / 2;


	int start = 8 * (GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		tmp.left = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE - mod;
		tmp.top = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE - mod + BOX_SIZE;
		tmp.right = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod;
		tmp.bottom = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE + mod + BOX_SIZE;

		t->push_back(tmp);
	}

	return;
}

void tBlocks::TetriminoToBlocks(std::vector<RECT>* t)
{
	// Tetrimino into Blocks.
	// make tetrimino immobilize and set it to playarea's block (Occupied)

	// set playarea attribute EMPTY -> OCCUPIED

	for (int i = 0; i < t->size(); i++)
	{
		int col = ( (t->begin() + i)->left + BOX_SIZE / 2) / BOX_SIZE;
		int row = ( (t->begin() + i)->top + BOX_SIZE / 2 ) / BOX_SIZE;

		PLAY_AREA_STATUS[row][col] = GetShape();
	}

}

tBlocks::~tBlocks()
{
}
