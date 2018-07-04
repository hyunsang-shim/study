#include <windows.h>
#include <TCHAR.H>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");	// _T�� �����ڵ�� ��ȯ�����ִ� ��ũ��
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// Ŭ���� �̸�
		_T("�������� ù��° ������"),						// Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,							// ��Ÿ��
		200,											// �»�� x ��ǥ
		300,											// �»�� y ��ǥ
		600,											// ���� ũ��
		400,											// ���� ũ��
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
			break;
	case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}