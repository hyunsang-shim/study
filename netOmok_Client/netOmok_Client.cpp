// netOmok_Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "netOmok_Client.h"
#include <vector>

//
//
// for Windows Socket Programming
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")



#define MAX_LOADSTRING 100
#define MSG_MAX_LENGTH 200
#define WM_ASYNC WM_USER + 2

#define GAME 1234
#define SYSTEM_OPPONENT_QUIT 1000
#define SYSTEM_CANNOT_JOIN 9999
#define SYSTEM_KEEP_ALIVE 7777
#define SYSTEM_NEW_ID 2000
#define SYSTEM_INVALID_ACTION 6666
#define SYSTEM_PROHIBITED 3333




#define SCREEN_SIZE 750
#define BOARD_SIZE 500
#define BOARD_LINES 19
#define SQUARE_WIDTH 23
#define SQUARE_HEIGHT 25
#define BOARD_MARGIN_HEIGHT 25
#define BOARD_MARGIN_WIDTH 40


//  �޽��� ����ü
typedef struct OMOK_MSG {
	int MsgType;
	int ThisTurn;
	int NewStoneX;
	int NewStoneY;
	short StoneColor;
	int NextTurn;
	int GameState;
}OMOK_MSG;


typedef struct omok_system_msg {
	int MsgType;
	char MSG1[80];
	char MSG2[80];
}OMOK_MSG_SYS;


// ���� ����:
HINSTANCE				hInst;                          // ���� �ν��Ͻ��Դϴ�.
WCHAR					szTitle[MAX_LOADSTRING];        // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR					szWindowClass[MAX_LOADSTRING];  // �⺻ â Ŭ���� �̸��Դϴ�.
OMOK_MSG				MyMessage, RecievedMessage;		// �޽��� ����/���ſ� ����ü
OMOK_MSG_SYS			SystemMessage;					// �ý��� �޽��� ��/���ſ� ����ü
RECT					RectClient;						// ȭ�� �׸���� Ŭ���̾�Ʈ ����
char					Board[19][19] = { 0 };			// �ٵ��� ����
int						MySocketID = -1;				// �濡 ���� ���� �� ���� �޴� ���� ID
int						MyStoneColor = 0;				// ���� ���� ���� �� ����
bool					isMyTurn = false;				// �� ���ΰ�?
TCHAR					ConnectionStatus[80];			// ���� ���� ǥ�ÿ�


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void				DrawGameScene(HDC FrontDC);
void				DrawBoard(HDC BackMemDC);
void				DrawStones(HDC BackMemDC);
void				ShowDebugInfo(HDC BackMemDC);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NETOMOK_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_CLIENT));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETOMOK_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	//wcex.hbrBackground = (HBRUSH)(RGB(255,100,255));
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, NULL, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WSADATA		wsadata;
	static SOCKET		s;	// ���� ����
	static SOCKADDR_IN	addr = { 0 };
	char				buffer[200];
	int					bufferLen;
	static HANDLE		hFile = CreateFile(_T("server.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
	static char		Filename[32];
	DWORD				fReadResult;

    switch (message)
    {
	case WM_CREATE:
	{
		SetRect(&RectClient, 0, 0, BOARD_SIZE + (GetSystemMetrics(SM_CXFRAME) << 1), BOARD_SIZE + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION));
		AdjustWindowRect(&RectClient, WS_OVERLAPPEDWINDOW, FALSE);

		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;

		if (ReadFile(hFile, Filename, sizeof(Filename), &fReadResult, NULL))
		{
			addr.sin_addr.S_un.S_addr = inet_addr(Filename);
			memset(ConnectionStatus, 0, sizeof(ConnectionStatus));

			TCHAR tmpStr[80];
			int tmplen = MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), tmpStr, tmplen);
			tmpStr[tmplen] = NULL;

			wsprintf(ConnectionStatus, _T("%s %s"), _T("���� IP : "), tmpStr);
			ConnectionStatus[lstrlen(ConnectionStatus)] = '\0';
		}
		else
		{
			MessageBox(NULL, _T("������ ã�� �� �����ϴ�. \n���� ������ �����մϴ�."), _T("���� ���� ����!!"), MB_OK);
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			memset(ConnectionStatus, 0, sizeof(ConnectionStatus));
			wsprintf(ConnectionStatus, _T("%s"), _T("���� IP : 127.0.0.1(����)"));
			ConnectionStatus[lstrlen(ConnectionStatus)] = '\0';
		}

		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) != -1)
		{
			MessageBox(NULL, _T("Connection Failed!"), _T("Error!!"), MB_OK);
		}

	}
		break;	
	case WM_ASYNC:
		switch (lParam)
		{
			case FD_READ:
			{
				memset(buffer, 0, 200);
				bufferLen = recv(s, buffer, 200, 0);
				buffer[bufferLen] = NULL;
				OMOK_MSG_SYS* tmpsys = (OMOK_MSG_SYS*)buffer;

				switch (tmpsys->MsgType)
				{
					case SYSTEM_INVALID_ACTION:						
					{
						TCHAR caption[100];
						int captionLen;
						TCHAR description[100];
						int descriptionLen;
#ifdef _UNICODE					
						captionLen = MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG1, sizeof(tmpsys->MSG1), NULL, NULL);
						MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG1, sizeof(tmpsys->MSG1), caption, captionLen);
						caption[captionLen] = NULL;
						descriptionLen = MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG2, sizeof(tmpsys->MSG2), NULL, NULL);
						MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG2, sizeof(tmpsys->MSG2), description, descriptionLen);
						description[descriptionLen] = NULL;
#else
						strcpy_s(caption, tmpsys->MSG1);
						strcpy_s(description, tmpsys->MSG2);
#endif
					
					return 0; 
					}
						break;
					case SYSTEM_NEW_ID:
						MySocketID = atoi(tmpsys->MSG1);
						MyStoneColor = atoi(tmpsys->MSG2);
						InvalidateRgn(hWnd, NULL, FALSE);
						break;
					case SYSTEM_PROHIBITED:
						// 3x3�̳� 4x3�� �Ϸ��� �ϸ� ����~!
						break;
					case SYSTEM_CANNOT_JOIN:
					{
						TCHAR caption[100];
						int captionLen;
						TCHAR description[100];
						int descriptionLen;
	#ifdef _UNICODE					
						captionLen = MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG1, sizeof(tmpsys->MSG1), NULL, NULL);
						MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG1, sizeof(tmpsys->MSG1), caption, captionLen);
						caption[captionLen] = NULL;
						descriptionLen = MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG2, sizeof(tmpsys->MSG2), NULL, NULL);
						MultiByteToWideChar(CP_ACP, 0, tmpsys->MSG2, sizeof(tmpsys->MSG2), description, descriptionLen);
						description[descriptionLen] = NULL;
	#else
						strcpy_s(caption, tmpsys->MSG1);
						strcpy_s(description, tmpsys->MSG2);

	#endif
						MessageBox(NULL, description, caption, MB_OK);
						PostQuitMessage(0);
					}
						break;
					case GAME:
					{
						OMOK_MSG* tmp = (OMOK_MSG*)buffer;


						// 2��° ������ ���� ���� ���̵� �Ҵ� ���� ���� ����.
						// ���� ���� ������ ���� ��� ���� �ϹǷ�
						// ���� ������ �ڿ��� ���� ��� �İ��� �ϰ� �ȴ�.
						if (MySocketID == -1)
						{
							MySocketID = tmp->NextTurn;
							MyStoneColor = tmp->StoneColor;
						}


						RecievedMessage.ThisTurn = tmp->ThisTurn;		// �̹� ��
						RecievedMessage.NewStoneX = tmp->NewStoneX;		// ������ ���� �� column ��
						RecievedMessage.NewStoneY = tmp->NewStoneY;		// ������ ���� �� row ��
						RecievedMessage.StoneColor = tmp->StoneColor;	// ������ �� ����
						RecievedMessage.NextTurn = tmp->NextTurn;		// ���� ��
						RecievedMessage.GameState = tmp->GameState;		// ���� ���� ���� ����

						if (RecievedMessage.ThisTurn == MySocketID)
							isMyTurn = true;
						else
							isMyTurn = false;
					
						if (RecievedMessage.NewStoneY != -1)
							Board[RecievedMessage.NewStoneY][RecievedMessage.NewStoneX] = RecievedMessage.StoneColor;
						InvalidateRgn(hWnd, NULL, TRUE);
					}
					break;
					case SYSTEM_KEEP_ALIVE:
						break;
				}
			}
			break;
			default:
				break;
			}		
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			
			DrawGameScene(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = RectClient.right + BOARD_SIZE/2;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = RectClient.bottom;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = RectClient.right + BOARD_SIZE/2;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = RectClient.bottom;
		return FALSE;
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		if (LOWORD(lParam) <= BOARD_SIZE-32 && LOWORD(lParam) >= 32)
		{
			if (HIWORD(lParam) <= BOARD_SIZE-16 && HIWORD(lParam) >= 8)
			{
				int tmp_row = (int)(HIWORD(lParam) - 12) / 25;
				int tmp_col = (int)(LOWORD(lParam) - 28) / 23;
				if (Board[tmp_row][tmp_col]== 0 && isMyTurn)
				{
					MyMessage.MsgType = GAME;
					MyMessage.NewStoneX = (int)(LOWORD(lParam) - 28) / 23;
					MyMessage.NewStoneY = (int)(HIWORD(lParam) - 12) / 25;
					MyMessage.StoneColor = MyStoneColor;
					MyMessage.ThisTurn = MySocketID;
					MyMessage.NextTurn = 0;

					send(s, (char*)&MyMessage, sizeof(MyMessage), 0);
					isMyTurn = false;
				}
				
			}			
		}				
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawGameScene(HDC FrontDC)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(GetDC(FindWindow(szWindowClass, szTitle)));
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(szWindowClass, szTitle));
	HBITMAP hBit = CreateCompatibleBitmap(FrontDC, SCREEN_SIZE, SCREEN_SIZE);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(FindWindow(szWindowClass, szTitle), tmpDC);
	DeleteObject(hBit);


	DrawBoard(BackMemDC);
	DrawStones(BackMemDC);
	ShowDebugInfo(BackMemDC);
	


	BitBlt(FrontDC, 0, 0, SCREEN_SIZE, SCREEN_SIZE, BackMemDC, 0, 0, SRCCOPY);


	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);
}

void DrawBoard(HDC BackMemDC)
{
	HBRUSH boardBG = CreateSolidBrush(RGB(248,200,120)), oldBrush;

	oldBrush = (HBRUSH)SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));
	Rectangle(BackMemDC, 0, 0, SCREEN_SIZE, SCREEN_SIZE);

	oldBrush = (HBRUSH)SelectObject(BackMemDC, boardBG);
	Rectangle(BackMemDC, 0, 0, BOARD_SIZE, BOARD_SIZE);

	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 18; j++)
		{
			Rectangle(BackMemDC, 40 + j * 23, 25 + i * 25, 41 + (j + 1) * 23, 26 + (i + 1) * 25);
		}
		
	DeleteObject(SelectObject(BackMemDC, oldBrush));



}

void DrawStones(HDC BackMemDC)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (Board[i][j] == 1)
			{
				SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));
				Ellipse(BackMemDC, 28 + j * 23, 13 + i * 25, 29 + (j + 1) * 23, 14 + (i + 1) * 25);
			}
			else if (Board[i][j] == -1)
			{
				SelectObject(BackMemDC, GetStockObject(BLACK_BRUSH));
				Ellipse(BackMemDC, 28 + j * 23, 13 + i * 25, 29 + (j + 1) * 23, 14 + (i + 1) * 25);
			}
		}
	}
}


void ShowDebugInfo(HDC BackMemDC)
{
	TextOut(BackMemDC, 515, 100, ConnectionStatus, lstrlen(ConnectionStatus));

	if (MySocketID != -1)
	{
		TCHAR tmp[100];
		wsprintf(tmp, _T("�� ����ID : %d"), MySocketID);
		TextOut(BackMemDC, 515, 1, tmp, lstrlen(tmp));
	}

	switch (RecievedMessage.GameState)
	{
	case 0:
		TextOut(BackMemDC, 515, 30, _T("���� ��븦 ��ٸ��� ���Դϴ�."), lstrlen(_T("���� ��븦 ��ٸ��� ���Դϴ�.")));
		break;
	case 1:
	{
		if (isMyTurn)
		{
			TextOut(BackMemDC, 530, 30, _T("����� �����Դϴ�."), lstrlen(_T("����� �����Դϴ�.")));
			if (MyStoneColor == -1)
				SelectObject(BackMemDC, GetStockObject(BLACK_BRUSH));
			else
				SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));

			Ellipse(BackMemDC, 580, 60, 610, 90);
		}
		else
		{
			TextOut(BackMemDC, 530, 30, _T("������ �����Դϴ�."), lstrlen(_T("������ �����Դϴ�.")));

			if (MyStoneColor == -1)
				SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));
			else
				SelectObject(BackMemDC, GetStockObject(BLACK_BRUSH));

			Ellipse(BackMemDC, 580, 60, 610, 90);
		}
	}
	break;
	}

}





/*#ifdef _UNICODE
MyMsgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), MyMsg, MyMsgLen);
MyMsg[MyMsgLen] = NULL;
#else
strcpy_s(msg, buffer);
#endif*/
//Log.push_back(MyMsg);