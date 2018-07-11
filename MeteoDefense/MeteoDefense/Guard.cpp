#include "Guard.h"

Guard::Guard()
{
}

void Guard::SetGuards(HDC hdc, RECT RectView, std::vector<Guard> vector, int idx)
{
	double width = RectView.right / NUM_OF_GUARDS;

	MyPos.left = RectView.left + idx * width;
	MyPos.right = MyPos.left + width;
	MyPos.top = RectView.bottom - 150 - GUARD_HEIGHT;
	MyPos.bottom = RectView.bottom - 150;

	Rectangle(hdc, MyPos.left, MyPos.top, MyPos.right, MyPos.bottom);
}

void Guard::setHp(int idx, int dmg)
{
	this->hp -= dmg;
}

RECT Guard::getmyPos()
{
	return this->MyPos;
}

int Guard::getHp()
{
	return this-> hp;
}

Guard::~Guard()
{
}
