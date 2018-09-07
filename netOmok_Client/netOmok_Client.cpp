// netOmok_Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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


//  메시지 구조체
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


// 전역 변수:
HINSTANCE				hInst;                          // 현재 인스턴스입니다.
WCHAR					szTitle[MAX_LOADSTRING];        // 제목 표시줄 텍스트입니다.
WCHAR					szWindowClass[MAX_LOADSTRING];  // 기본 창 클래스 이름입니다.
OMOK_MSG				MyMessage, RecievedMessage;		// 메시지 전송/수신용 구조체
OMOK_MSG_SYS			SystemMessage;					// 시스템 메시지 송/수신용 구조체
RECT					RectClient;						// 화면 그리기용 클라이언트 영역
char					Board[19][19] = { 0 };			// 바둑판 정보
int						MySocketID = -1;				// 방에 접속 했을 때 배정 받는 소켓 ID
int						MyStoneColor = 0;				// 내가 배정 받은 돌 색깔
bool					isMyTurn = false;				// 내 턴인가?
TCHAR					ConnectionStatus[80];			// 접속 상태 표시용


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NETOMOK_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WSADATA		wsadata;
	static SOCKET		s;	// 서버 소켓
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

			wsprintf(ConnectionStatus, _T("%s %s"), _T("서버 IP : "), tmpStr);
			ConnectionStatus[lstrlen(ConnectionStatus)] = '\0';
		}
		else
		{
			MessageBox(NULL, _T("서버를 찾을 수 없습니다. \n로컬 서버로 접속합니다."), _T("서버 접속 에러!!"), MB_OK);
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			memset(ConnectionStatus, 0, sizeof(ConnectionStatus));
			wsprintf(ConnectionStatus, _T("%s"), _T("서버 IP : 127.0.0.1(로컬)"));
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
						// 3x3이나 4x3을 하려고 하면 에러~!
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


						// 2번째 유저는 아직 소켓 아이디를 할당 받지 못한 상태.
						// 먼저 들어온 유저가 백을 잡고 선공 하므로
						// 나중 유저는 자연히 흑을 잡고 후공을 하게 된다.
						if (MySocketID == -1)
						{
							MySocketID = tmp->NextTurn;
							MyStoneColor = tmp->StoneColor;
						}


						RecievedMessage.ThisTurn = tmp->ThisTurn;		// 이번 턴
						RecievedMessage.NewStoneX = tmp->NewStoneX;		// 상대방이 놓은 돌 column 값
						RecievedMessage.NewStoneY = tmp->NewStoneY;		// 상대방이 놓은 돌 row 값
						RecievedMessage.StoneColor = tmp->StoneColor;	// 상대방의 돌 색깔
						RecievedMessage.NextTurn = tmp->NextTurn;		// 다음 턴
						RecievedMessage.GameState = tmp->GameState;		// 현재 게임 진행 상태

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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			
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
		wsprintf(tmp, _T("내 소켓ID : %d"), MySocketID);
		TextOut(BackMemDC, 515, 1, tmp, lstrlen(tmp));
	}

	switch (RecievedMessage.GameState)
	{
	case 0:
		TextOut(BackMemDC, 515, 30, _T("대전 상대를 기다리는 중입니다."), lstrlen(_T("대전 상대를 기다리는 중입니다.")));
		break;
	case 1:
	{
		if (isMyTurn)
		{
			TextOut(BackMemDC, 530, 30, _T("당신의 차례입니다."), lstrlen(_T("당신의 차례입니다.")));
			if (MyStoneColor == -1)
				SelectObject(BackMemDC, GetStockObject(BLACK_BRUSH));
			else
				SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));

			Ellipse(BackMemDC, 580, 60, 610, 90);
		}
		else
		{
			TextOut(BackMemDC, 530, 30, _T("상대방의 차례입니다."), lstrlen(_T("상대방의 차례입니다.")));

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