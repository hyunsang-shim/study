#include <windows.h>
#include <TCHAR.H>
#include <math.h>


#define PI 3.14
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");	// _T는 유니코드로 변환시켜주는 매크로 앞에 써주는 게 안전하다. _T("str");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),		// 클래스 이름
		_T("심현상의 첫번째 윈도우"),						// 타이틀 이름
		WS_OVERLAPPEDWINDOW,							// 스타일
		200,											// 좌상단 x 좌표
		300,											// 좌상단 y 좌표
		600,											// 가로 크기
		400,											// 세로 크기
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


void DrawGrid(HDC hdc)
{
	int LINE_MAX = 200;
	int LINE_TERM = LINE_MAX / 10;
	for (int i = LINE_TERM; i <= LINE_MAX; i += LINE_TERM)
	{
		MoveToEx(hdc, i, 0, NULL);
		LineTo(hdc, i, LINE_MAX + LINE_TERM);

		MoveToEx(hdc, 0, i, NULL);
		LineTo(hdc, LINE_MAX + LINE_TERM, i);
	}

}
void DrawStar(HDC hdc, POINT* PolyPoints)
{
	Polygon(hdc, PolyPoints, 10);
}

void DrawRectangle(HDC hdc)
{
	static int TL_X = 10;
	static int TL_Y = 10;
	static int BR_X = 200;
	static int BR_Y = 200;
	int padding = 10;

	for (TL_X, TL_Y; TL_X < BR_X, TL_Y < BR_Y; TL_X += padding, TL_Y += padding, BR_X -= padding, BR_Y -= padding)
	{
		Rectangle(hdc, TL_X, TL_Y, BR_X, BR_Y);
	}
}

// hdc, 바깥 원이 표시되는 간격(각도)
void DrawCircles(HDC hdc, int angle_term)
{
	int CENTER_X = 150;
	int CENTER_Y = 150;
	int Radius = 50;
	Ellipse(hdc, CENTER_X - Radius, CENTER_Y - Radius, CENTER_X + Radius, CENTER_Y + Radius);

	double newCENTER_X;
	double newCENTER_Y;
	double newRadius = Radius * angle_term * PI / 180 /2;
	double diff;
	Ellipse(hdc, CENTER_X - Radius, CENTER_Y - Radius, CENTER_X + Radius, CENTER_Y + Radius);

	//라디안 각도 = 각도 * 파이 / 180
	for (int i = 0; i < 360; i += angle_term)
	{
		newCENTER_X = CENTER_X + cos(i*PI / 180) * (Radius + newRadius);
		newCENTER_Y = CENTER_Y + sin(i*PI / 180) * (Radius + newRadius);
		
		double a = (CENTER_X + cos((i + angle_term) * PI / 180) * Radius) - (CENTER_X + cos(i*PI / 180) * Radius);
		double b = (CENTER_Y + sin((i + angle_term) * PI / 180) * Radius) - (CENTER_Y + sin(i*PI / 180) * Radius);

		if (newRadius * 2 < pow((pow(a, 2.0) + pow(b, 2.0)), 0.5))
			diff = (pow((pow(a, 2.0) + pow(b, 2.0)), 0.5)/2 + newRadius);
		else if (newRadius * 2 > pow((pow(a, 2.0) + pow(b, 2.0)), 0.5))
			diff = (newRadius - pow((pow(a, 2.0) + pow(b, 2.0)), 0.5)/2);
		else
			diff = 0;
	
		Ellipse(hdc, newCENTER_X - newRadius - diff, newCENTER_Y + newRadius + diff,
			newCENTER_X + newRadius + diff, newCENTER_Y - newRadius-diff);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect = { 0,0,1000,1000 };
	static TCHAR str[100];
	static int count, ypos;
	static int before_enter;
	static SIZE size;
	POINT PolyPoints[10] = { { 100,10 }, {120, 30}, {160, 30}, {130, 55}, {145,100}, {100, 75},{ 55,100 },{ 70, 55 }, { 40, 30 },{ 80, 30 } };

	switch (iMsg)
	{
	case WM_CREATE:
		count = 0;
		ypos = 0;
		CreateCaret(hwnd, NULL, 5, 15);
		ShowCaret(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);	
		if (wParam == VK_BACK && count > 0) count--;
		else if (wParam == VK_RETURN)
		{		
			GetTextExtentPoint(hdc, str, _tcslen(str), &size);
			ypos += size.cy;
			before_enter += (size.cx +count);
			str[count++] = wParam;			
		}
		else
		{
			str[count++] = wParam;
			GetTextExtentPoint(hdc, str, _tcslen(str), &size);
		}
		str[count] = NULL;
		size.cx -= before_enter;
		InvalidateRgn(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);

		break; 	
	case WM_PAINT:
		//좌표 지정 후 출력
		/*
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, _T("Hello World!"), _tcslen(_T("Hello Woeld!")));
		EndPaint(hwnd, &ps);
		*/

		//출력 영역 설정 후 출력
		//hdc = BeginPaint(hwnd, &ps);
		//WM_CHAR 문자열을 창을 다시 올렸을 때 나오도록 추가함
	/*	DrawText(hdc, str, _tcslen(str), &rect, DT_TOP | DT_LEFT);
		SetCaretPos(size.cx, ypos);
		EndPaint(hwnd, &ps);*/

		hdc = BeginPaint(hwnd, &ps);
		// 격자 그리기		
		//DrawGrid(hdc);
		

		//사각형 그리기
		//DrawRectangle(hdc);
		

		//다각형 그리기
		//DrawStar(hdc,PolyPoints);

		//원 그리기
		DrawCircles(hdc, 30);

		
		break;


	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}