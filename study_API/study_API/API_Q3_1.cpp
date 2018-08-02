#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include "Circle.h"
#include <cstdlib>
#include <ctime>
#include <vector>

#define PI 3.14
const int radius = 15;
static int posX = 0;
static int posY = 0;
static int last_circle = 0;
int last_cnt = 0;
int tmp = 0;
std::vector<Circle> vCircles;
std::vector<Circle>::iterator iter;

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//�Ʒ� winMain2�� WinMain���� �ٲ㼭 ���
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
	WndClass.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ�� �տ� ���ִ� �� �����ϴ�. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
		_T("������ Ÿ��Ʋ"),						// Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,							// ��Ÿ��
		0,											// �»�� x ��ǥ
		0,											// �»�� y ��ǥ
		800,											// ���� ũ��
		800,											// ���� ũ��
		NULL,											// �θ� ������ �ڵ�
		NULL,											// �޴� �ڵ�
		hInstance,										// ���� ���α׷� �ν��Ͻ�
		NULL											// ������ ����
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
	
	vCircles[last_circle].setSpeedX(rand() % 3 + 3 * ( rand() % 201 - 100 ) / 100 );
	vCircles[last_circle].setSpeedY(rand() % 3 + 3 * ( rand() % 201 - 100) / 100 );
	vCircles[last_circle].setRadius(radius);
	vCircles[last_circle].setPosX(((WORD)(((DWORD_PTR)(lparam)) & 0xffff)));
	vCircles[last_circle].setPosY(((WORD)((((DWORD_PTR)(lparam)) >> 16) & 0xffff)));
	vCircles[last_circle++].setValid(true);	
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	
	SYSTEMTIME st;
	static RECT rectView;
	static int last_cnt = 0;
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
						{
							vCircles[i].overlaps(hdc, vCircles[j], rectView);

							if (!vCircles[j].checkValid())
							{
								iter = vCircles.begin() + j;
								vCircles.erase(iter);
								last_circle--;
								iter = vCircles.begin();
								//j--;
							}
							if (!vCircles[i].checkValid())
							{
								iter = vCircles.begin() + i;
								vCircles.erase(iter);
								last_circle--;
								iter = vCircles.begin();
								if (i > 1)
									i--;
								else
									i = 0;
							}
						}
					}
				}			
			TCHAR mass[20];
			wsprintf(mass, "%d", vCircles[i].getRadius());
			TextOut(hdc, rectView.left + 10, rectView.top + 10, mass, lstrlen(mass));

			if (vCircles.size() < 1)
			{
				addCircle();
				setCircle(lParam);
				last_cnt = 1;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
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
			wsprintf(tmp, "���� ���� ���� : %d��", vCircles.size());
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