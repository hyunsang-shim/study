#include "Turret.h"
#include <math.h>



Turret::Turret()
{
	ATTACK = 1;
	ShotMax = 1;
	CUR_SPS = 0.5;
	LvATK = 1;
	LvSPD = 1;
}


Turret::~Turret()
{
}

void Turret::InitTurret()
{

}


double Turret::GetHeadX()
{
	return this->HeadPosX;
}


double Turret::GetHeadY()
{
	return this->HeadPosY;
}


double Turret::GetRootX()
{
	return this->RootPosX;
}


double Turret::GetRootY()
{
	return this->RootPosY;
}


void Turret::setHeadX(double x)
{
	this->HeadPosX = x;
}
void Turret::setHeadY(double y)
{
	this->HeadPosX = y;
}


void Turret::setBasePos(HWND hwnd, RECT rect)
{
	RECT tmp;
	GetClientRect(hwnd, &tmp);

	RootPosX = tmp.right / 2;
	RootPosY = tmp.bottom -10;
	HeadPosX = RootPosX;
	HeadPosY = RootPosY - 100;

}

void Turret::DrawPlayer(HDC hdc, LPARAM* lParam) const
{

	// 직접 각도를 만들지 못하겠으니까, 땜빵으로... 마우스 위치를 나눠서 각도를 임의로 만든다.	
	// 교점이 있는 두 직선 사이의 각도 구하기
	// http://beanexpert.tistory.com/entry/Vision-%EB%91%90-%EC%A7%81%EC%84%A0-%EC%82%AC%EC%9D%B4%EC%9D%98-%EA%B0%81%EB%8F%84-%EC%82%AC%EC%9D%B4%EA%B0%81-%EA%B5%AC%ED%95%98%EA%B8%B0 
	// 사이각 = atan((y2-cy) / x2 - cx)) - atan((y1 -cy) / x1-cx))
	// cx, cy는 교점을 중점으로 이동시키는데 사용 한 값.
	// 여기서는 중점이 고정되어있으므로, 

	static double R;

	R = atan(HIWORD(lParam) / LOWORD(lParam)) - atan(this->HeadPosY / this->HeadPosX);


	//원의 자취에 있는 점의 좌표는 
	//x' = 중점(x) + cos(라디안 R) * 반지름
	//y' = 중점(y) + sin(라디안 R) * 반지름
	double X = this->RootPosX + (cos(R * 3.14159 / 180) * CANNON_LENGTH);
	double Y = this->RootPosY - (sin(R * 3.14159 / 180) * CANNON_LENGTH);
	setHeadX(X);
	setHeadY(Y);

	
	//포신 중점으로 이동
	MoveToEx(hdc, this->RootPosX, this->RootPosY, NULL);
	//포신 끝으로 선을 긋는다.
	LineTo(hdc, this->HeadPosX, this->HeadPosY);

	//포신을 덮는 몸체를 그린다.
	Ellipse(hdc, this->RootPosX - 25, this->RootPosY - 10, this->RootPosX + 25, this->RootPosX + 10);
}
