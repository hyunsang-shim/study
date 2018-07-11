#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <string>
#include <ctime>
#include "cGameManager.h"
#include "Guard.h"


LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void TitleScreen(HDC hdc, HWND hwnd, RECT label, RECT box);
void GameScreen(HDC hdc, HWND hwnd, RECT RectView);

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
	WndMain.lpszClassName = _T("Window Class Name");	// _T는 유니코드로 변환시켜주는 매크로 앞에 써주는 게 안전하다. _T("str");
	RegisterClass(&WndMain);
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

	//rand 함수를 위한 시드 초기화
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
	static int x, y;
	static RECT rectView;
	static int sceneMode;
	static SIZE size;
	static int count;
	static TCHAR id_input[ID_MAX_SIZE];
	static RECT label;
	static RECT box;
	cGameManager Manager;
	
	
	switch (iMsg)
	{
	case WM_CREATE:

		Manager.GetInstance();

		GetClientRect(hwnd, &rectView);

		GetClientRect(hwnd, &label);
		label.left = label.right / 2 - 50;
		label.right = label.right / 2 + 50;
		label.top = label.bottom / 2 - 150;
		label.bottom = label.bottom / 2 - 130;


		box.left = label.left;
		box.top = label.bottom + 5;
		box.right = label.right;
		box.bottom = box.top + 30;

		CreateCaret(hwnd, NULL, 5, 15);
		sceneMode = scene_title;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (sceneMode == scene_title)
		{
			TitleScreen(hdc, hwnd, label, box);
			GetTextExtentPoint(hdc, id_input, _tcslen(id_input), &size);
			TextOut(hdc, box.left + 5, box.top + 5, id_input, _tcslen(id_input));
			ShowCaret(hwnd);
			SetCaretPos(box.left + 5 + size.cx, box.top + 5);
			break;
		}
		else if (sceneMode == scene_game)
		{
			GameScreen(hdc, hwnd, rectView);
			TextOut(hdc, 10, 10, _T("ID"), _tcslen(_T("ID")));
			
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		HideCaret(hwnd);
		DestroyCaret();
		break;
	case WM_CHAR:
		if (sceneMode == scene_title)
		{
			if (wParam == VK_RETURN)
			{
				Manager.setID(id_input);
				count = 0;
				id_input[count] = NULL;
				InvalidateRgn(hwnd, NULL, TRUE);
				HideCaret(hwnd);
				sceneMode = scene_game;
				break;
			}
			else if (wParam == VK_BACK && count > 0) count--;
			else
			{
				if (count < ID_MAX_SIZE - 1)
					id_input[count++] = wParam;

				id_input[count] = NULL;
			}

			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		}
		else if(sceneMode == scene_game)
		{
			InvalidateRgn(hwnd, NULL, TRUE);;
		}
		break;
	
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void TitleScreen(HDC hdc, HWND hwnd, RECT label, RECT box)
{
	
	//Rectangle(hdc, label.left, label.top, label.right, label.bottom);
	DrawText(hdc, TEXT("ID 입력"), lstrlen(TEXT("ID 입력")), &label, DT_CENTER | DT_VCENTER);
	Rectangle(hdc, box.left, box.top, box.right, box.bottom);
	SetCaretPos(box.left + 5, box.top + 5);

	label.top = box.bottom+30;
	label.bottom = box.bottom + 60;
	label.left -= 100;
	label.right += 100;

	DrawText(hdc, TEXT("입력 후 엔터를 치세요!"), lstrlen(TEXT("입력 후 엔터를 치세요!")), &label, DT_CENTER | DT_VCENTER);		
}

void GameScreen(HDC hdc, HWND hwnd, RECT RectView)
{
	static std::vector<Guard> guards;

	//방어 블럭 생성
	for (UINT i = 0; i < NUM_OF_GUARDS; i++)
	{
		TCHAR tmp[10];
		tmp[0] = L' ';
		Guard g;
		guards.push_back(g);
		guards[i].setHp(DEFAULT_GUARD_HP);
		guards[i].SetGuards(hdc, RectView, i);
		(HBRUSH)GetStockObject(BLACK_PEN);
		wsprintf(tmp, _T(" %d "), (UINT)guards[i].getHp());
		DrawText(hdc, tmp, lstrlen(tmp), &guards[i].getmyPos_Label(), DT_CENTER | DT_VCENTER);
	}
	InvalidateRgn(hwnd, NULL, TRUE);
}