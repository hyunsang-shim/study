#include "Guard.h"
#include <tchar.h>

Guard::Guard()
{
}

void Guard::SetGuards(HDC hdc, RECT RectView, int idx)
{
	double width = RectView.right / NUM_OF_GUARDS;

	MyPos.left = RectView.left + idx * width;
	MyPos.right = MyPos.left + width;
	MyPos.top = RectView.bottom - GUARD_POS_TOP_MODIFIER - GUARD_HEIGHT;
	MyPos.bottom = MyPos.top + FONT_SIZE + GUARD_HEIGHT;
	isDead = false;

	Rectangle(hdc, MyPos.left, MyPos.top, MyPos.right, MyPos.bottom);
}

void Guard::DrawGuard(HDC hdc)
{
	if (!isDead)
	{
		Rectangle(hdc, MyPos.left, MyPos.top, MyPos.right, MyPos.bottom);
		TCHAR tmp[10];
		tmp[0] = L' ';
		(HBRUSH)GetStockObject(BLACK_PEN);
		wsprintf(tmp, _T(" %d "), (UINT)hp);
		DrawText(hdc, tmp, lstrlen(tmp), &MyPos_Label, DT_CENTER | DT_VCENTER);
	}
}

void Guard::setDead()
{
	isDead = true;
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
	tmp.top = MyPos.top + LABEL_MARGIN;
	tmp.left = MyPos.left + LABEL_MARGIN;
	tmp.right = MyPos.right - LABEL_MARGIN;
	tmp.bottom = tmp.top + FONT_SIZE + LABEL_MARGIN;

	return tmp;

}
int Guard::getHp()
{
	return this->hp;
}

Guard::~Guard()
{
}
