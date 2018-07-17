#include <windows.h>
#include <TCHAR.H>
#include <math.h>

#include "API2D.h"
API2D g_API2D;


#define MAX_LOADSTRING 100
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
	WndClass.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ�� �տ� ���ִ� �� �����ϴ�. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
		_T("������ â �̸�"),						// Ÿ��Ʋ �̸�
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
	HDC hdc, memdc1, memdc2;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_CREATE:
		g_API2D.Init(hwnd);
		SetTimer(hwnd, 123, 30, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		g_API2D.Draw(hdc);
		g_API2D.PrintText(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_TIMER:
		g_API2D.Update();
		InvalidateRgn(hwnd, 0, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			g_API2D.setDir(true);

			g_API2D.SetPosX(3);
		}
		else if (wParam == VK_LEFT)
		{
			g_API2D.setDir(false);
			g_API2D.SetPosX(-3);
		}
		else
		{
			g_API2D.setDir(true);
			g_API2D.SetPosX(3);
		}

	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}