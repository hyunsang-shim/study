#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <string>
#include <ctime>
#include "cGameManager.h"

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void TitleScene(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam, RECT Screen);
void InputID(HWND hwnd, HDC hdc, TCHAR *input, SIZE *size, cGameManager *Manager);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndMain;

	WndMain.style = CS_HREDRAW | CS_VREDRAW;
	WndMain.lpfnWndProc = WinProc;
	WndMain.cbClsExtra = 0;
	WndMain.cbWndExtra = 0;
	WndMain.hInstance = hInstance;
	WndMain.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndMain.hCursor = LoadCursor(NULL, IDC_IBEAM);
	WndMain.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndMain.lpszMenuName = NULL;
	WndMain.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ�� �տ� ���ִ� �� �����ϴ�. _T("str");
	RegisterClass(&WndMain);
	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
		_T("Meteo Defense v0.1"),						// Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,							// ��Ÿ��
		0,											// �»�� x ��ǥ
		0,											// �»�� y ��ǥ
		800,											// ���� ũ��
		600,											// ���� ũ��
		NULL,											// �θ� ������ �ڵ�
		NULL,											// �޴� �ڵ�
		hInstance,										// ���� ���α׷� �ν��Ͻ�
		NULL											// ������ ����
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//rand �Լ��� ���� �õ� �ʱ�ȭ
	srand(time(NULL));

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
	static RECT Screen;
	cGameManager Manager;
	static SIZE size;
	static int count = 0;
	TCHAR input[ID_MAX_SIZE];
	Manager.GetInstance();	

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &Screen);
		CreateCaret(hwnd, NULL, 5, 15);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		switch (Manager.getCurrentScene())
		{
		case eSceneTitle:
			TitleScene(hwnd, hdc, wParam, lParam, Screen);
			InputID(hwnd, hdc, input, &size, &Manager);
			break;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		switch (Manager.getCurrentScene())
		{
			if (wParam == VK_RETURN)
			{
				count = 0;
				input[count] = NULL;
				HideCaret(hwnd);
				Manager.SetCurrentScene(eSceneTitle);
			}
			else if (wParam == VK_BACK && count > 0) count--;
			else
			{
				if (count < ID_MAX_SIZE - 1)
					input[count++] = wParam;

				input[count] = NULL;
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


void TitleScene(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam, RECT Screen)
{
	TextOut(hdc, 
		Screen.right / 2 - lstrlen(_T("���̵� �Է��ϼ���.")) / 2, Screen.top + Screen.bottom / 4, 
		_T("���̵� �Է��ϼ���."), lstrlen(_T("���̵� �Է��ϼ���.")) );
	Rectangle(hdc, 
		Screen.right / 2 - 80, Screen.top + Screen.bottom / 4 + 30, 
		Screen.right / 2 + 100, Screen.top + Screen.bottom / 4 + 80	);
}

void InputID(HWND hwnd, HDC hdc, TCHAR *input, SIZE *size, cGameManager *Manager)
{
	GetTextExtentPoint(hdc, input, _tcslen(input), size);
	TextOut(hdc, (Manager->GetInputLabel()).left, (Manager->GetInputLabel()).top, input, _tcslen(input));
	SetCaretPos((Manager->GetInputBox()).left + size->cx, (Manager->GetInputBox()).top);
	ShowCaret(hwnd);
}