#include <windows.h>
#include <TCHAR.H>
#include <math.h>

#define PI 3.14
#define BSIZE 40

double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}

LRESULT CALLBACK Wnd0Proc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//아래 winMain2를 WinMain으로 바꿔서 사용
int WINAPI WinMain3(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	WndClass;
	static BOOL Selection;


	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = Wnd0Proc;
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
		500,											// 가로 크기
		500,											// 세로 크기
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

LRESULT CALLBACK Wnd0Proc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	
	SYSTEMTIME st;	
	static int x, y;
	static int flag = 0;
	static BOOL Selection;
	static BOOL Drag;
	static int	startX, startY, oldX, oldY;
	int endX, endY;
	int mx, my;
	static RECT rectView;

	POINT PolyPoints[10] = { { 100,10 },{ 120, 30 },{ 160, 30 },{ 130, 55 },{ 145,100 },{ 100, 75 },{ 55,100 },{ 70, 55 },{ 40, 30 },{ 80, 30 } };

	switch (iMsg)
	{
	case WM_CREATE:
		startX = oldX = 50;
		startY = oldY = 50;
		x = 50, y = 50;
		Selection = FALSE;
		Drag = FALSE;
		GetClientRect(hwnd, &rectView);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//if (Selection)
		//	Rectangle(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		//Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, oldX, oldY);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		/*mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(x, y, mx, my)) Selection = TRUE;
		InvalidateRgn(hwnd, NULL, TRUE);*/
		oldX = LOWORD(lParam);
		oldY = HIWORD(lParam);
		Drag = TRUE;
		break;
	case WM_RBUTTONDOWN:
		/*Selection = FALSE;
		x = 50;
		y = 50;*/
		Drag = FALSE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (y - 10 - BSIZE > rectView.top)
			{
				y -= 10;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			else
				y = rectView.top + BSIZE;
			break;
		case VK_DOWN:
			if (y + 10 + BSIZE < rectView.bottom)
			{
				y += 10;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			else
				y = rectView.bottom - BSIZE;
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case VK_LEFT:
			if (x - 10 + BSIZE < rectView.left)
			{
				x -= 10;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			else
				x = rectView.left + BSIZE;
			break;
		case VK_RIGHT:
			if (x + 10 + BSIZE > rectView.right)
			{
				x += 10;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			else
				x = rectView.right - BSIZE;
			break;
		}
		break;
	case WM_MOUSEMOVE:
		/*if (Selection)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			InvalidateRgn(hwnd, NULL, TRUE);
		}		*/
		hdc = GetDC(hwnd);
		if (Drag)
		{
		SetROP2(hdc, R2_XORPEN);
		SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
		endX = LOWORD(lParam);
		endY = HIWORD(lParam);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, oldX, oldY);
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, endX, endY);
		oldX = endX; oldY = endY;
		}

		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}