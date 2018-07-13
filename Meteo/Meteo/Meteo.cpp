#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <string>
#include <ctime>
#include "cGameManager.h"

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//타이틀 화면용 구성
void TitleScene(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam, RECT Screen, cGameManager *Manager);

//게임 화면 준비용 -> 가드 생성, 배치, HP 세팅
void Prepare_GameScene(HDC hdc, RECT *screen, std::vector<stGUARD> *vGuards, cGameManager *Manager);


//총알을 담아 둘 배열
std::vector<stBullet> vBullets;
//적들을 담아 둘 배열
std::vector<stENEMY> vEnemies;
//가드들을 담아 둘 배열
std::vector<stGUARD> vGuards;

cGameManager Manager;


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
		_T("Meteo Defense v0.1"),						// 타이틀 이름
		WS_OVERLAPPEDWINDOW,							// 스타일
		0,											// 좌상단 x 좌표
		0,											// 좌상단 y 좌표
		800,											// 가로 크기
		600,											// 세로 크기
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
	static RECT Screen;
	static SIZE size;
	static int count = 0;
	static TCHAR input[ID_MAX_SIZE] = " ";


	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &Screen);
		Manager.GetInstance();
		CreateCaret(hwnd, NULL, 5, 15);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//Prepare_GameScene(hdc, &Screen, &vGuards, &Manager);

		if (Manager.getCurrentScene() == eSceneTitle)
		{
			TitleScene(hwnd, hdc, wParam, lParam, Screen, &Manager);
			GetTextExtentPoint(hdc, input, _tcslen(input), &size);
			TextOut(hdc, (Manager.GetInputBox()).left + FONT_SIZE, (Manager.GetInputBox()).top + FONT_SIZE, input, _tcslen(input));
			SetCaretPos((Manager.GetInputBox()).left + FONT_SIZE+ size.cx, (Manager.GetInputBox()).top + FONT_SIZE);
			ShowCaret(hwnd);
		}
		else if (Manager.getCurrentScene() == eSceneGame)
		{
			for (int i = 0; i < NUM_OF_GUARDS; i++)
			{
				//가드를 그려준다. 살아 있는 놈들만
				if (vGuards[i].CurHP > 0)
				{
					TCHAR hp[4];
					_itoa_s(vGuards[i].CurHP, hp, 4, 10);					
					Rectangle(hdc, vGuards[i].MyPos.left, vGuards[i].MyPos.top, vGuards[i].MyPos.right, vGuards[i].MyPos.bottom);
					TextOut(hdc, vGuards[i].Label_HP.cx, vGuards[i].Label_HP.cy, hp, _tcslen(hp));
				}

				//아이디를 출력한다.
				TCHAR tmp[100];
				wsprintf(tmp, "PLAYER\n%s", Manager.GetPLAYER_ID());
				DrawText(hdc, tmp, lstrlen(tmp), &Manager.GetPosDisplayLabel_ID(), DT_VCENTER | DT_CENTER);
				//DrawText(hdc, Manager.GetPLAYER_ID(), lstrlen(Manager.GetPLAYER_ID()), &Manager.GetPosDisplayLabel_ID(), DT_VCENTER | DT_BOTTOM | DT_CENTER);

				//점수를 출력한다.
				tmp[0] = '\0';
				wsprintf(tmp, "SCORE\n%d", Manager.GetPLAYER_SCORE());
				DrawText(hdc, tmp, lstrlen(tmp), &Manager.GetPosDisplayLabel_Score(), DT_VCENTER | DT_CENTER);
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		switch (Manager.getCurrentScene())
		{
		case eSceneTitle:			
			if (wParam == VK_RETURN)
			{
				hdc = GetDC(hwnd);
				Manager.SetPLAYER_ID(input);
				count = 0;
				input[count] = NULL;
				HideCaret(hwnd);
				Manager.SetCurrentScene(eSceneGame);
				Prepare_GameScene(hdc, &Screen, &vGuards, &Manager);
				ReleaseDC(hwnd, hdc);				
				//타이머를 생성
				//SetTimer(hwnd, 1, 1000, NULL);
				//break;
			}
			else if (wParam == VK_BACK && count > 0) count--;
			else
			{
				if (count < ID_MAX_SIZE)
					input[count++] = wParam;
				
				if (count < ID_MAX_SIZE)
					input[count] = NULL;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case eSceneGame:
			if (wParam == VK_SPACE)
			{
				Manager.AddScore(123);
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			else if (wParam == VK_BACK)
			{
				Manager.AddScore(-120);
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


void TitleScene(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam, RECT Screen, cGameManager *Manager)
{
	Manager->SetInputArea(hwnd);
		
	Rectangle(hdc, 
		Manager->GetInputBox().left, Manager->GetInputBox().top,
		Manager->GetInputBox().right, Manager->GetInputBox().bottom);
}

void Prepare_GameScene(HDC hdc, RECT *screen, std::vector<stGUARD> *vGuards, cGameManager *Manager)
{
	for (int i = 0; i < NUM_OF_GUARDS; i++)
	{
		//더미 가드를 만든다
		stGUARD g;
		//세팅 한다.
		Manager->SetGuard(hdc, screen, &g, i);	//해당 가드의 기본 값을 세팅한다 네모를 그린다.
		//벡터 배열에 집어 넣는다.
		vGuards->push_back(g);
	}


	//정보 영역을 설정한다.
	Manager->SetPosDisplayLabel_ID(screen);
	Manager->SetPosDisplayLabel_Score(screen);
}
