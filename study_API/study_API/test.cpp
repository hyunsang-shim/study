#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <cstdlib>


#define PI 3.14
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndClass;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
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
		_T("심현상의 첫번째 윈도우"),						// 타이틀 이름
		WS_OVERLAPPEDWINDOW,							// 스타일
		200,											// 좌상단 x 좌표
		200,											// 좌상단 y 좌표
		700,											// 가로 크기
		700,											// 세로 크기
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN		newPen, oldPen;
	HBRUSH		newBrush, oldBrush;
	RECT rect = { 0,0,1000,1000 };
	static TCHAR str[100];
	static SIZE size;			
	static RECT rectView;
	
	switch (iMsg)
	{
	case WM_CREATE:		
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;		
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);		
		EndPaint(hwnd, &ps);		
		break;

	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}