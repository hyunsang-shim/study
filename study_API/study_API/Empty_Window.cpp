//#include <windows.h>
//#include <TCHAR.H>
//#include <math.h>
//
//#define PI 3.14
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
////아래 winMain2를 WinMain으로 바꿔서 사용
//int WINAPI WinMain1(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
//{
//	HWND		hwnd;
//	MSG			msg;
//	WNDCLASS	WndClass;
//
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	WndClass.lpfnWndProc = WndProc;
//	WndClass.cbClsExtra = 0;
//	WndClass.cbWndExtra = 0;
//	WndClass.hInstance = hInstance;
//	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
//	WndClass.hCursor = LoadCursor(NULL, IDC_IBEAM);
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	WndClass.lpszMenuName = NULL;
//	WndClass.lpszClassName = _T("Window Class Name");	// _T는 유니코드로 변환시켜주는 매크로 앞에 써주는 게 안전하다. _T("str");
//	RegisterClass(&WndClass);
//	hwnd = CreateWindow(_T("Window Class Name"),		// 클래스 이름
//		_T("심현상의 첫번째 윈도우"),						// 타이틀 이름
//		WS_OVERLAPPEDWINDOW,							// 스타일
//		0,											// 좌상단 x 좌표
//		0,											// 좌상단 y 좌표
//		1000,											// 가로 크기
//		1000,											// 세로 크기
//		NULL,											// 부모 윈도우 핸들
//		NULL,											// 메뉴 핸들
//		hInstance,										// 응용 프로그램 인스턴스
//		NULL											// 윈도우 정보
//	);
//
//	ShowWindow(hwnd, nCmdShow);
//	UpdateWindow(hwnd);
//
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return (int)msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;	
//	SYSTEMTIME st;	
//
//	POINT PolyPoints[10] = { { 100,10 },{ 120, 30 },{ 160, 30 },{ 130, 55 },{ 145,100 },{ 100, 75 },{ 55,100 },{ 70, 55 },{ 40, 30 },{ 80, 30 } };
//
//	switch (iMsg)
//	{
//	case WM_CREATE:		
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hwnd, &ps);
//		EndPaint(hwnd, &ps);
//		break; 
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//
//	return DefWindowProc(hwnd, iMsg, wParam, lParam);
//}

#include <windows.h>
#include <TCHAR.H>
#include <math.h>

#define PI 3.14

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndClass;

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

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT rectView;
	
	switch (iMsg)
	{
	case WM_CREATE:		
		GetClientRect(hwnd, &rectView);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break; 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

