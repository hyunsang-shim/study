#pragma once
#include <windows.h>
#include <vector>
#include <cstdlib>
#include "Throne.h"

class cTriangle : public cThrone
{
public:
	cTriangle();
	cTriangle(LPARAM lparam, int Flag);
	~cTriangle();
	void setPoints(int idx, LPARAM lparam, int Flag);
	void Draw(HDC hdc, LPARAM lparam);

private:
	POINT points[3] = { {0,0}, {0,0},{0,0} };
	double mySize = 10;
};