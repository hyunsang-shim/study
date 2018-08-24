// WINAPI_2D.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "vld.h"
#include "cManager.h"
#include "SceneManager.h"

#pragma comment(lib, "msimg32.lib")

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

RECT RectView;
RECT RectClient;
//cManager *Mgr = new cManager();

DWORD dwStart, dwEnd;

//cTownScene *ScnTown = new cTownScene();



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void CALLBACK		TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void				initGameWindow(HWND hWnd);


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
    LoadStringW(hInstance, IDC_WINAPI2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2D));

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = _T("OneWay_Life");
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(_T("OneWay_Life"), szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 
	  SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME)>>1), SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME)<<1) + GetSystemMetrics(SM_CYCAPTION) ,
	  nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {	
	case WM_CREATE:
		initGameWindow(hWnd);
		GAME_MANAGER->ChangeScene(GAME_MANAGER->GetCurScene());
		SetTimer(hWnd, 1, 16, &TimerProc);
		break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME) >> 1);
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION);
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME) >> 1);
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION);
		return FALSE;
    case WM_PAINT:        
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
        break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;		
	case WM_MOVE:
		break;
	case WM_KEYDOWN:
		if (GAME_MANAGER->GetPC_State() == Moving)
			GAME_MANAGER->MoveCharacter();
		else
			GAME_MANAGER->key(wParam);
		break; 	
	case WM_SETFOCUS:
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void initGameWindow(HWND hWnd)
{	
	SetWindowText(hWnd, _T("외길인생 : 검투사의 길"));

	cManager::GetInstance();
	GAME_MANAGER->Init();	

	SetRect(&RectClient, 0, 0, SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME) >> 1), SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION));
	AdjustWindowRect(&RectClient, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow(hWnd,
		GetSystemMetrics(SM_CXSCREEN) / 2 - SCREEN_WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - SCREEN_HEIGHT / 2,
		RectClient.right - RectClient.left,
		RectClient.bottom - RectClient.top+60,
		TRUE);

	GetClientRect(hWnd, &RectView);

}


void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	TCHAR tmp[256] = { '\0' };
	TCHAR tmp2[256] = { '\0' };

	HDC tmpDC = GetDC(hWnd);

	wsprintf(tmp, _T("r%d, c%d"), GAME_MANAGER->GetStatus_PC().coord_y, GAME_MANAGER->GetStatus_PC().coord_x);
	wsprintf(tmp2, _T("EventId %d"), GAME_MANAGER->GetEventID());
	
	GAME_MANAGER->UpdateScene(tmpDC);
	//InvalidateRgn(hWnd, NULL, FALSE);			
	
	GAME_MANAGER->DrawScene(tmpDC);
	TextOut(tmpDC, GAME_MANAGER->GetStatus_PC().pos_x, GAME_MANAGER->GetStatus_PC().pos_y - CHARACTER_SIZE + 18, tmp2, lstrlen(tmp2));
	TextOut(tmpDC, GAME_MANAGER->GetStatus_PC().pos_x, GAME_MANAGER->GetStatus_PC().pos_y + CHARACTER_SIZE, tmp, lstrlen(tmp));
	
	ReleaseDC(hWnd, tmpDC);

}