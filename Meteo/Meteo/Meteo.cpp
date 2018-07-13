#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <string>
#include <ctime>
#include "cGameManager.h"

LRESULT CALLBACK WinProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//Ÿ��Ʋ ȭ��� ����
void TitleScene(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam, RECT Screen, cGameManager *Manager);

//���� ȭ�� �غ�� -> ���� ����, ��ġ, HP ����
void Prepare_GameScene(HDC hdc, RECT *screen, std::vector<stGUARD> *vGuards, cGameManager *Manager);


//�Ѿ��� ��� �� �迭
std::vector<stBullet> vBullets;
//������ ��� �� �迭
std::vector<stENEMY> vEnemies;
//������� ��� �� �迭
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
				//���带 �׷��ش�. ��� �ִ� ��鸸
				if (vGuards[i].CurHP > 0)
				{
					TCHAR hp[4];
					_itoa_s(vGuards[i].CurHP, hp, 4, 10);					
					Rectangle(hdc, vGuards[i].MyPos.left, vGuards[i].MyPos.top, vGuards[i].MyPos.right, vGuards[i].MyPos.bottom);
					TextOut(hdc, vGuards[i].Label_HP.cx, vGuards[i].Label_HP.cy, hp, _tcslen(hp));
				}

				//���̵� ����Ѵ�.
				TCHAR tmp[100];
				wsprintf(tmp, "PLAYER\n%s", Manager.GetPLAYER_ID());
				DrawText(hdc, tmp, lstrlen(tmp), &Manager.GetPosDisplayLabel_ID(), DT_VCENTER | DT_CENTER);
				//DrawText(hdc, Manager.GetPLAYER_ID(), lstrlen(Manager.GetPLAYER_ID()), &Manager.GetPosDisplayLabel_ID(), DT_VCENTER | DT_BOTTOM | DT_CENTER);

				//������ ����Ѵ�.
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
				//Ÿ�̸Ӹ� ����
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
		//���� ���带 �����
		stGUARD g;
		//���� �Ѵ�.
		Manager->SetGuard(hdc, screen, &g, i);	//�ش� ������ �⺻ ���� �����Ѵ� �׸� �׸���.
		//���� �迭�� ���� �ִ´�.
		vGuards->push_back(g);
	}


	//���� ������ �����Ѵ�.
	Manager->SetPosDisplayLabel_ID(screen);
	Manager->SetPosDisplayLabel_Score(screen);
}
