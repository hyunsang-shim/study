//#include <windows.h>
//#include <TCHAR.H>
//#include <math.h>
//
//#define PI 3.14
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
////�Ʒ� winMain2�� WinMain���� �ٲ㼭 ���
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
//	WndClass.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ�� �տ� ���ִ� �� �����ϴ�. _T("str");
//	RegisterClass(&WndClass);
//	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
//		_T("�������� ù��° ������"),						// Ÿ��Ʋ �̸�
//		WS_OVERLAPPEDWINDOW,							// ��Ÿ��
//		0,											// �»�� x ��ǥ
//		0,											// �»�� y ��ǥ
//		1000,											// ���� ũ��
//		1000,											// ���� ũ��
//		NULL,											// �θ� ������ �ڵ�
//		NULL,											// �޴� �ڵ�
//		hInstance,										// ���� ���α׷� �ν��Ͻ�
//		NULL											// ������ ����
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
//�Ʒ� winMain2�� WinMain���� �ٲ㼭 ���
int WINAPI WinMain1(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
	WndClass.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ�� �տ� ���ִ� �� �����ϴ�. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
		_T("�������� ù��° ������"),						// Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,							// ��Ÿ��
		0,											// �»�� x ��ǥ
		0,											// �»�� y ��ǥ
		1000,											// ���� ũ��
		1000,											// ���� ũ��
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

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT rectView;
	SYSTEMTIME st;
	TCHAR read_clock[100];

	POINT PolyPoints[10] = { { 100,10 },{ 120, 30 },{ 160, 30 },{ 130, 55 },{ 145,100 },{ 100, 75 },{ 55,100 },{ 70, 55 },{ 40, 30 },{ 80, 30 } };

	switch (iMsg)
	{
	case WM_CREATE:		
		GetClientRect(hwnd, &rectView);
		x = 20; y = 20;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		GetLocalTime(&st);
		wsprintf(read_clock, "%�� %d��(%s) %d�� %d�� %d��", st.wMonth, st.wDay, st.wDayOfWeek, st.wHour, st.wMinute, st.wSecond);
		TextOut(hdc, rectView.right - 300, rectView.top + 10, read_clock, lstrlen(read_clock));
		EndPaint(hwnd, &ps);
		break; 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT) SetTimer(hwnd, 1, 70, NULL);
		break;
	case WM_TIMER:
		x += 20;
		if (x + 20 > rectView.right) x -= 20;

	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

