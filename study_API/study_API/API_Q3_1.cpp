#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include "Circle.h"
#include <cstdlib>
#include <ctime>
#include <vector>

#define PI 3.14
const int radius = 20;
static int posX = 0;
static int posY = 0;
static int last_circle = 0;

std::vector<Circle> vCircles;

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//아래 winMain2를 WinMain으로 바꿔서 사용
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndClass;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WindProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");	// _T는 유니코드로 변환시켜주는 매크로 앞에 써주는 게 안전하다. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// 클래스 이름
		_T("심현상의 첫번째 윈도우"),						// 타이틀 이름
		WS_OVERLAPPEDWINDOW,							// 스타일
		0,											// 좌상단 x 좌표
		0,											// 좌상단 y 좌표
		800,											// 가로 크기
		800,											// 세로 크기
		NULL,											// 부모 윈도우 핸들
		NULL,											// 메뉴 핸들
		hInstance,										// 응용 프로그램 인스턴스
		NULL											// 윈도우 정보
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
void addCircle()
{
	Circle c1(posX, posY, radius);
	vCircles.push_back(c1);
}

void setCircle(LPARAM lparam)
{
	vCircles[last_circle].setSpeedX(rand() % 3 + 3);
	vCircles[last_circle].setSpeedY(rand() % 3 + 3);
	vCircles[last_circle].setRadius(radius);
	vCircles[last_circle].setPosX(((WORD)(((DWORD_PTR)(lparam)) & 0xffff)));
	vCircles[last_circle].setPosY(((WORD)((((DWORD_PTR)(lparam)) >> 16) & 0xffff)));
	vCircles[last_circle].setDir(rand()%61);
	vCircles[last_circle++].setValid(true);
	
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	
	SYSTEMTIME st;
	static RECT rectView;
	static int last_cnt = 0;
	static int tmp = 0;
	static int del_count = 0;


	switch (iMsg)
	{
	case WM_CREATE:		
		GetClientRect(hwnd, &rectView);
		break;
	case WM_LBUTTONDOWN:
		addCircle();
		setCircle(lParam);
		last_cnt++;
		SetTimer(hwnd, 1, 50/3, NULL);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_TIMER:
		for (int i = 0; i < vCircles.size(); i++)
		{
			if (vCircles[i].checkValid())
				vCircles[i].move(rectView);
		}
		for (int i = 0; i < vCircles.size()-1; i++)
		{
			if (vCircles[i].checkValid())
				for (int j = i + 1; j < vCircles.size(); j++)
				{
					if (vCircles[j].checkValid())
					{
						if (vCircles[i].checkValid() && vCircles[j].checkValid())
							vCircles[i].overlaps(vCircles[j], rectView);
					}
				}			
		}
		InvalidateRgn(hwnd, NULL, TRUE);

		//그린 후에는 비활성 된 애들 자리에 활성된 애들을 땡겨 넣는다.
		for (int i = 0; i < vCircles.size(); i++)
		{
			if (!vCircles[i].checkValid())
			{
				tmp = i;
				for (int j = i; j < vCircles.size() - 1; j++)
				{
					if (vCircles[j].checkValid())
					{
						tmp = j;
						break;
					}
				}

				if (tmp != i)
				{
					vCircles[i] = vCircles[tmp];
					last_cnt = tmp = i;

				}
			}
		}
		if(last_cnt+1 <= vCircles.size())
			vCircles.resize(last_cnt);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		(HBRUSH)GetStockObject(WHITE_PEN);
		if (vCircles.size() >= 1)
		{
			for (int i = 0; i < vCircles.size(); i++)
			{
				if (vCircles[i].checkValid())
					Ellipse(hdc, vCircles[i].getPosX() - vCircles[i].getRadius(), vCircles[i].getPosY() - vCircles[i].getRadius(),
						vCircles[i].getPosX() + vCircles[i].getRadius(), vCircles[i].getPosY() + vCircles[i].getRadius());
			}
			TCHAR tmp[100];
			wsprintf(tmp, "현재 원의 개수 : %d개", vCircles.size());
			TextOut(hdc, rectView.left + 10, rectView.top + 10, tmp, lstrlen(tmp));
		}
		EndPaint(hwnd, &ps);
		break; 
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}