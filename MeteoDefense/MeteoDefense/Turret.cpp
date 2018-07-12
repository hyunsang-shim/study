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

	// ���� ������ ������ ���ϰ����ϱ�, ��������... ���콺 ��ġ�� ������ ������ ���Ƿ� �����.	
	// ������ �ִ� �� ���� ������ ���� ���ϱ�
	// http://beanexpert.tistory.com/entry/Vision-%EB%91%90-%EC%A7%81%EC%84%A0-%EC%82%AC%EC%9D%B4%EC%9D%98-%EA%B0%81%EB%8F%84-%EC%82%AC%EC%9D%B4%EA%B0%81-%EA%B5%AC%ED%95%98%EA%B8%B0 
	// ���̰� = atan((y2-cy) / x2 - cx)) - atan((y1 -cy) / x1-cx))
	// cx, cy�� ������ �������� �̵���Ű�µ� ��� �� ��.
	// ���⼭�� ������ �����Ǿ������Ƿ�, 

	static double R;

	R = atan(HIWORD(lParam) / LOWORD(lParam)) - atan(this->HeadPosY / this->HeadPosX);


	//���� ���뿡 �ִ� ���� ��ǥ�� 
	//x' = ����(x) + cos(���� R) * ������
	//y' = ����(y) + sin(���� R) * ������
	double X = this->RootPosX + (cos(R * 3.14159 / 180) * CANNON_LENGTH);
	double Y = this->RootPosY - (sin(R * 3.14159 / 180) * CANNON_LENGTH);
	setHeadX(X);
	setHeadY(Y);

	
	//���� �������� �̵�
	MoveToEx(hdc, this->RootPosX, this->RootPosY, NULL);
	//���� ������ ���� �ߴ´�.
	LineTo(hdc, this->HeadPosX, this->HeadPosY);

	//������ ���� ��ü�� �׸���.
	Ellipse(hdc, this->RootPosX - 25, this->RootPosY - 10, this->RootPosX + 25, this->RootPosX + 10);
}
