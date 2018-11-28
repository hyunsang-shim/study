// Win32_Server.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "netOmok_Server.h"
#include <stdio.h>
#include <vector>
#include <string>


//
//
// for Windows Socket Programming
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
//>>


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



//  메시지 구조체
// int MsgType;
// int ThisTurn;
// int NewStoneX;
// int NewStoneY;
// short StoneColor;
// int NextTurn;
// int GameState;
typedef struct omok_message {
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
HINSTANCE			hInst;                           // 현재 인스턴스입니다.
WCHAR				szTitle[MAX_LOADSTRING];         // 제목 표시줄 텍스트입니다.
WCHAR				szWindowClass[MAX_LOADSTRING];   // 기본 창 클래스 이름입니다.
static OMOK_MSG		GameMessage, Recieved;		// 게임 진행 메시지 전송/수신용 구조체
static OMOK_MSG_SYS	SystemMessage;				// 시스템 메시지 전송.수신용 구조체

char				Board[19][19] = { 0 };

RECT RectClient;



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int					checkProhibitions(int x, int y);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//
	// just check that connected or not
	//return WinSockTest_Server();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NETOMOK_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_SERVER));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETOMOK_SERVER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NETOMOK_SERVER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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

	static WSADATA		wsadata;					// WSADATA 구조체
	static SOCKET		s;							// 서버의 소켓 구조체
	static std::vector<SOCKET> cs;					// 클라이언트 소켓 저장 공간(vector)		
	static SOCKADDR_IN	addr = { 0 }, c_addr;		// 소켓 주소. 
	int					size, MsgLen;				// 버퍼 사이즈, 소켓주소 크기 등을 저장하기 위한 변수
	char				buffer[MSG_MAX_LENGTH];		// 받은 메시지를 입시 저장하는 공간	
	static int			LastTurn = -1;				// 마지막으로 움직인 플레이어.
	static int			CurrentPlayer;				// 마지막으로 돌을 둔 유저의 Socket ID
	static int			NextPlayer;					// 다음 차례의 플레이어
	static bool			GameState = false;					// 게임 진행 상태
	static HANDLE		hFile = CreateFile(_T("server.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
	static char			Filename[32];
	DWORD				fReadResult;
	static TCHAR		ServerStatus[80];			// 서버 상태 표시


	switch (message)
	{
	case WM_CREATE:
		MoveWindow(hWnd, 0, 0, 800, 200, TRUE);
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		
		if (ReadFile(hFile, Filename, sizeof(Filename), &fReadResult, NULL))
		{
			Filename[strlen(Filename)] = NULL;
			addr.sin_addr.S_un.S_addr = inet_addr(Filename);
			memset(ServerStatus, 0, sizeof(ServerStatus));

			TCHAR tmpStr[80];
			int tmplen = MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), tmpStr, tmplen);
			tmpStr[tmplen] = NULL;

			wsprintf(ServerStatus, _T("%s %s"), _T("서버 IP : "), tmpStr);
			ServerStatus[lstrlen(ServerStatus)] = '\0';
		}
		else
		{
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			memset(ServerStatus, 0, sizeof(ServerStatus));
			wsprintf(ServerStatus, _T("%s"), _T("서버 IP : 127.0.0.1"));
			ServerStatus[lstrlen(ServerStatus)] = '\0';
			
		}
		//
		// check Binding
		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
		{
			MessageBox(NULL, _T("Binding Failed!"), _T("Error"), MB_OK);
			return 0;
		}

		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT | FD_CLOSE);
		//
		// Check Listening
		if (listen(s, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("Listening Failed!"), _T("Error"), MB_OK);
			return 0;
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
		{
			size = sizeof(c_addr);
			// 접속 시도가 있을 때마다 접속을 받는다. 2번째 이후부터는 접속을 거부한다.

			//
			// 2번째 플레이어가 들어왔으면 게임 시작을 위해 시작 정보를 넘겨준다.
			if (cs.size() == 1)
			{

				// 2번째 유저를 바로 대전 상대로 넣는다.
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));
				WSAAsyncSelect(cs[cs.size() - 1], hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

				// 첫번째 접속 유저에게 보낼 메시지 세팅
				GameMessage.MsgType = GAME;
				GameMessage.NewStoneX = -1;
				GameMessage.NewStoneY = -1;
				GameMessage.ThisTurn = cs[0];
				GameMessage.NextTurn = cs[1];
				GameMessage.StoneColor = 1;
				GameMessage.GameState = 1;
				CurrentPlayer = cs[0];
				send(cs[0], (char*)&GameMessage, sizeof(GameMessage) + 1, 0);


				
				// 두번째 접속 유저에게 보낼 메시지 세팅
				GameMessage.ThisTurn = cs[0];
				GameMessage.NextTurn = cs[1];
				GameMessage.StoneColor = -1;				
				NextPlayer = cs[1];
				send(cs[1], (char*)&GameMessage, sizeof(GameMessage) + 1, 0);

				GameState = true;
			}
			//접속자가 없으면 받아들인다.
			else if (cs.size() == 0)
			{
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));
				WSAAsyncSelect(cs[cs.size() - 1], hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
				SystemMessage.MsgType = SYSTEM_NEW_ID;
				sprintf(SystemMessage.MSG1, "%d", cs[cs.size() - 1]);
				
				if (cs.size() == 1)
					sprintf(SystemMessage.MSG2, "%d", 1);
				else
					sprintf(SystemMessage.MSG2, "%d", -1);


				send(cs[cs.size() - 1], (char*)&SystemMessage, sizeof(SystemMessage) + 1, 0);

			}
			else
			{
				SOCKET tmp = accept(s, (LPSOCKADDR)&c_addr, &size);
				WSAAsyncSelect(tmp, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
				SystemMessage.MsgType = SYSTEM_CANNOT_JOIN;
				sprintf_s(SystemMessage.MSG1, "접속 실패");
				sprintf_s(SystemMessage.MSG2, "인원 초과로 입장에 실패하였습니다.\n게임을 종료합니다.");
				send(tmp, (char*)&SystemMessage, sizeof(SystemMessage), 0);
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case FD_READ:
		{
			memset(buffer, 0, 200);
			MsgLen = recv(CurrentPlayer, buffer, 200, 0);
			buffer[MsgLen] = NULL;
			OMOK_MSG_SYS* tmpsys = (OMOK_MSG_SYS*)buffer;
			
			switch (tmpsys->MsgType)
			{
			case GAME:
				//받은 메시지를 가공
				OMOK_MSG* tmp = (OMOK_MSG*)buffer;
				Recieved.ThisTurn = tmp->ThisTurn;			// 방금 돌을 둔 유저
				Recieved.NewStoneX = tmp->NewStoneX;		// 방금 돌을 둔 유저의 돌 위치 column 값
				Recieved.NewStoneY = tmp->NewStoneY;		// 방금 돌을 둔 유저의 돌 위치 row 값
				Recieved.StoneColor = tmp->StoneColor;		// 방금 돌을 둔 유저의 돌 색깔
				Recieved.NextTurn = tmp->NextTurn;			// 다음 턴 정보 (무시)


				// 서버측 턴 정보 갱신
				// 이번 턴에 해야 하는 유저가 맞다면 OK
				// 아니면 ERROR (돌아가!)
				if (Recieved.ThisTurn == CurrentPlayer)
				{
					CurrentPlayer = NextPlayer;
					NextPlayer = Recieved.ThisTurn;
				}
				else
				{
					SystemMessage.MsgType = SYSTEM_INVALID_ACTION;
				}

				// 바둑판 정보 업데이트
				// 둬도 될까?
				if (checkProhibitions(Recieved.NewStoneX, Recieved.NewStoneY))
				{
					Board[Recieved.NewStoneY][Recieved.NewStoneX] = Recieved.StoneColor;
					GameMessage.MsgType = GAME;
					GameMessage.NewStoneX = Recieved.NewStoneX;
					GameMessage.NewStoneY = Recieved.NewStoneY;
					GameMessage.NextTurn = NextPlayer;
					GameMessage.ThisTurn = CurrentPlayer;
					GameMessage.StoneColor = Recieved.StoneColor;

					for (int i = 0; i < cs.size(); i++)
					{
						send(cs[i], (char*)&GameMessage, sizeof(GameMessage), 0);
					}
				}
				else
				{
					SystemMessage.MsgType = SYSTEM_INVALID_ACTION;
					sprintf(SystemMessage.MSG1, "잘못된 동작입니다.");
					sprintf(SystemMessage.MSG2, "그 곳에는 둘 수 없습니다.");
					
					
				}

				// 업데이트 된 정보를 준비
				
				
				
				break;
			}

			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
		case FD_CLOSE:
		{
			std::vector<SOCKET>::iterator iter;
			
				for (iter = cs.begin(); iter != cs.end(); )
				{
					if(*iter == (SOCKET)wParam)
					{
						iter = cs.erase(iter);
						break;
					}
					else
					{
						iter++;
					}
				}

				if (!cs.empty())
				{
					for (int i = 0; i < cs.size(); i++)
					{
						if (cs[i] != wParam)
						{
							//접종 메시지
						}
					}
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
		TextOut(hdc, 10, 10, ServerStatus, lstrlen(ServerStatus));
		TCHAR p1[32];
		TCHAR p2[32];
		if (cs.empty())
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s"), _T("선공(백) : 접속 대기중"), 0);
			wsprintf(p2, _T("%s"), _T("후공(흑) : 접속 대기중"), 0);
		}
		else if (cs.size() == 1)
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s%d"), _T("선공(백) : "), cs[0]);
			wsprintf(p2, _T("%s"), _T("후공(흑) : 접속 대기중"), 0);
		}
		else if (cs.size() == 2)
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s%d"), _T("선공(백) : "), cs[0]);
			wsprintf(p2, _T("%s%d"), _T("후공(흑) : "), cs[1]);
		}
		TextOut(hdc, 10, 30, p1, lstrlen(p1));
		TextOut(hdc, 10, 50, p2, lstrlen(p2));
		EndPaint(hWnd, &ps);
	}
	break;	
	case WM_DESTROY:
		closesocket(s);
		WSACleanup();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int checkProhibitions(int x, int y)
{
	char tmp[19][19];
	int cnt_open3;
	int cnt_open4;

	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
			tmp[row][col] = Board[row][col];

	tmp[y][x] = Recieved.StoneColor;

	//승리 검사. 5개가 일직선이면 승리
	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
		{
			if (tmp[row][col] == 0)
				break;
			else
			{
				for (int i = row; i < 19-row; i++)
				{
					//오른쪽


				}
			}

		}

	return true;
}
