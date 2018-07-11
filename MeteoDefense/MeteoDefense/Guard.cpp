#include "Guard.h"

Guard::Guard()
{
}

void Guard::SetGuards(HDC hdc, RECT RectView, int idx)
{
	double width = RectView.right / NUM_OF_GUARDS;

	MyPos.left = RectView.left + idx * width;
	MyPos.right = MyPos.left + width;
	MyPos.top = RectView.bottom - 160 - GUARD_HEIGHT;
	MyPos.bottom = MyPos.top + 5 + GUARD_HEIGHT;

	Rectangle(hdc, MyPos.left, MyPos.top, MyPos.right, MyPos.bottom);
}

void Guard::setHp(int hp)
{
	this->hp = hp;
}

void Guard::DoDMG(int dmg)
{
	this->hp -= dmg;
}

RECT Guard::getmyPos()
{
	return this->MyPos;
}

RECT Guard::getmyPos_Label()
{
	RECT tmp;
	tmp.top = MyPos.top + 1;
	tmp.left = MyPos.left + 2;
	tmp.right = MyPos.right - 2;
	tmp.bottom = tmp.top + 16;

	return tmp;

}
int Guard::getHp()
{
	return this->hp;
}

Guard::~Guard()
{
}
