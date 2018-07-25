#include "stdafx.h"
#include "tBlocks.h"


tBlocks::tBlocks()
{
}

void tBlocks::InitTetrimino(int shape, int rotate, std::vector<RECT> *t)
{
	CurX = PLAY_AREA_WIDTH / 2 * BOX_SIZE;
	CurY = 2 * BOX_SIZE;

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
}


int tBlocks::GetCurX()
{
	return CurX;
}

int tBlocks::GetCurY()
{
	return CurY;
}

void tBlocks::SetCurX(int newX)
{
	CurX = newX;
}

void tBlocks::SetCurY(int newY)
{
	CurY = newY;
}

void tBlocks::Rotate(std::vector<RECT> *t)
{
	//회전할 수 있으면
	if (CheckRotate_R(t))
	{
		//회전을 진행한다.

		// 더 회전할 수 있으면 테트리미노를 회전시킨다.
		if ((dictionary[this->GetShape()][1] > (this->GetRotation() + 1)))
			this->SetRotation(this->GetRotation() + 1);
		else
			this->SetRotation(0);	// 끝까지 갔으면 처음으로

		//회전 시키기 전에 지금 테트리미노를 정리한다.
		t->clear();
		RECT tmp;

		int mod = BOX_SIZE / 2;

		int start = 8 * (this->GetRotation());
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}	
	}
}
void tBlocks::MoveRight(std::vector<RECT> *t)
{
	if (CheckRight(t))
	{
		t->clear();
		RECT tmp;
		int mod = BOX_SIZE / 2;

		printf("Move : x = %d, y = %d  -->  ", CurX, CurY);

		CurX = CurX + BOX_SIZE;
		CurY = CurY;

		printf("Move : x = %d, y = %d\n", CurX, CurY);

		int start = 8 * (GetRotation());
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[GetShape()][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[GetShape()][i + 1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[GetShape()][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[GetShape()][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}
	}
}
void tBlocks::MoveLeft(std::vector<RECT> *t)
{
	if (CheckLeft(t))
	{
		t->clear();
		RECT tmp;
		int mod = BOX_SIZE / 2;

		printf("Move : x = %d, y = %d  -->  ", CurX, CurY);

		CurX = CurX - BOX_SIZE;
		CurY = CurY;

		printf("Move : x = %d, y = %d\n", CurX, CurY);

		int start = 8 * (GetRotation());
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[GetShape()][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[GetShape()][i + 1] * BOX_SIZE - mod;
			tmp.right = GetCurX() + shapes[GetShape()][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[GetShape()][i + 1] * BOX_SIZE + mod;

			t->push_back(tmp);
		}
	}
}
void tBlocks::Down(std::vector<RECT> *t)
{
	t->clear();
	RECT tmp;
	static int cnt = 1;
	int mod = BOX_SIZE / 2;

	CurY += BOX_SIZE;

	if (CurY > (PLAY_AREA_HEIGHT - 2) * BOX_SIZE)
	{
		printf("쿵! 떨어졌습니다!\n");
		CurY -= BOX_SIZE;

		int start = 8 * (this->GetRotation());
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
	else {
		int start = 8 * (this->GetRotation());
		for (int i = start; i < start + 8; i += 2)
		{
			tmp.left = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE - mod;
			tmp.top = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE - mod + BOX_SIZE;
			tmp.right = GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod;
			tmp.bottom = GetCurY() + shapes[this->GetShape()][i + 1] * BOX_SIZE + mod + BOX_SIZE;

			t->push_back(tmp);
		}
	}
	
	

}
bool tBlocks::CheckRight(std::vector<RECT>* t)
{
	int mod = BOX_SIZE / 2;

	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod) >((PLAY_AREA_WIDTH - 2) * BOX_SIZE))
			return false;
	}
	return true;
}
bool tBlocks::CheckLeft(std::vector<RECT>* t)
{
	for (int i = 0; i < t->size(); i++)
	{
		if ((t->begin() + i)->left < BOX_SIZE)
			return false;
	}
	return true;
}
bool tBlocks::CheckRotate_R(std::vector<RECT>* t)
{

	// for the check, just rotate once.
	// when check is completed, return is needed
	if ((dictionary[this->GetShape()][1] >(this->GetRotation() + 1)))
		this->SetRotation(this->GetRotation() + 1);
	else
		this->SetRotation(0);	// restart from the beginning.

	int mod = BOX_SIZE / 2;
	int start = 8 * (this->GetRotation());
	for (int i = start; i < start + 8; i += 2)
	{
		if ((GetCurX() + shapes[this->GetShape()][i] * BOX_SIZE + mod) < ((PLAY_AREA_WIDTH -2 ) * BOX_SIZE) )
		{
			//Completed the Check, return it to the former shape 
			this->SetRotation(this->GetRotation() - 1);
			return false;
		}
	}

	//Completed the Check, return it to the former shape.
	this->SetRotation(this->GetRotation() - 1);	
	return true;
	
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
tBlocks::~tBlocks()
{
}
