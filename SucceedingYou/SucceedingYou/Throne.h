#pragma once
#include <windows.h>
#include <vector>

enum ObjType {
	eTriangle = 0,
	eRectangle = 1,
	eStar = 2,
	eCircle = 3,
	eEnlarge = 4,
	eEnsmall = 5
};

class cThrone
{
public:
	cThrone();	
	bool getFlag();
	void setFlag(int flag);
	double getCenterX();
	double getCenterY(); 
	double getSize();
	double getSizeMin();
	double getSizeMax();
	double getSizeMod();
	virtual void DrawObject(HDC hdc, LPARAM lparam, double size);
	~cThrone();

private:
	double CenterX;
	double CenterY;
	double Size;
	bool Flag;
	double sizeMax = 40;
	double sizeMin = 10;
	double sizeMod = 5;
	int Kind;
};

