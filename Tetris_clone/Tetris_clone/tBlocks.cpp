#include "stdafx.h"
#include "tBlocks.h"
#include "Tetris_clone.h"


tBlocks::tBlocks()
{
}

tBlocks::tBlocks(int x, int y)
{
	CurX = x;
	CurY = y;
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


std::vector<POINT> tBlocks::GetShape_XY(int shape, int rotate)
{
	std::vector<POINT> this_shape;

	POINT tmp;
	if (dictionary[shape][1] >= rotate)
	{
		int start = shape * 8 * rotate;
		for (int i = start; i < start + 8; i++)
		{
			tmp.x = this->shapes[shape][i++];
			tmp.y = this->shapes[shape][i];
			this_shape.push_back(tmp);
		}
	}

	return this_shape;
}



RECT tBlocks::GetRect()
{
	RECT tmp;
	int mod = BOX_SIZE / 2;
	tmp.left = GetCurX() - mod;
	tmp.right = GetCurX() + mod;
	tmp.top = GetCurY() - mod;
	tmp.bottom = GetCurY() + mod;

	return tmp;
}

tBlocks::~tBlocks()
{
}
