#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include "./resource.h"

#define PI 3.14

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndClass;
	hInst = hInstance;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WinProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");	// _T는 유니코드로 변환시켜주는 매크로 앞에 써주는 게 안전하다. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// 클래스 이름
		_T("윈도우 창 이름"),						// 타이틀 이름
		WS_OVERLAPPEDWINDOW,							// 스타일
		0,											// 좌상단 x 좌표
		0,											// 좌상단 y 좌표
		1000,											// 가로 크기
		1000,											// 세로 크기
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


void TextPrint(HDC hdc, int x, int y, TCHAR t[])
{
	int i, j;
	SetTextColor(hdc, RGB(255, 255, 255));
	for (i = -1; i <= 1; i++)
		for (j = -1; j <= 1; j++)
			TextOut(hdc, x + i, y + j, t, lstrlen(t));
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, x, y, t, lstrlen(t));
}
LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc1, memdc2;
	PAINTSTRUCT ps;
	static HBITMAP old_hBit1, old_hBit2, new_hBit1, new_hBit2;
	static int x=0, y=0;
	static int posY;
	TCHAR	Word[] = _T("Succeeding you, Father!");
	static RECT rectView;
	static int add = 1;

	switch (iMsg)
	{
	case WM_CREATE:
		new_hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1,15, NULL);
		posY = 0;
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rectView);
		hdc = BeginPaint(hwnd, &ps);
		memdc1 = CreateCompatibleDC(hdc);
		memdc2 = CreateCompatibleDC(memdc1);
		if (new_hBit1 == NULL)
			new_hBit1 = CreateCompatibleBitmap(hdc, 697, 504);
		old_hBit1 = (HBITMAP)SelectObject(memdc1, new_hBit1);
		old_hBit2 = (HBITMAP)SelectObject(memdc2, new_hBit2);
		//StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc2, 0, 0, 697, 504, SRCCOPY); 
		//StretchBlt(hdc, 0, 0, 697, 504, memdc2, 0, 0, 697, 504, SRCCOPY);
		BitBlt(memdc1, 0, 0, 697, 504, memdc2, 0, 0,SRCCOPY);
		SetBkMode(memdc1, TRANSPARENT);
		TextPrint(memdc1, 200, posY, Word);
		BitBlt(hdc, 0, 0, 697, 504, memdc1, 0, 0, SRCCOPY);
		SelectObject(memdc1, old_hBit1);
		SelectObject(memdc2, old_hBit2);
		DeleteDC(memdc2);
		DeleteDC(memdc1);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		if (new_hBit1) DeleteObject(new_hBit1);
		DeleteObject(new_hBit2);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:
		posY += add;

		if (posY + 10 > 504)
		{			
			posY -= 5;
			add *= -1;			
		}
		else if (posY < rectView.top)
		{
			posY = 1;
			add *= -1;
		}
		InvalidateRgn(hwnd, NULL, FALSE);		
		return 0;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}