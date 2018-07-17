// hopscotch.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "hopscotch.h"
#include "API2D.h"
#include "Manager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
BOOL KeyBuffer[256];

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

API2D g_API2D;
Manager *MANAGER;

//사용자 함수 등록
void MovePlayer(HWND hWnd, WPARAM wParam);
void DrawLine(HWND hWnd, WPARAM wParam, SIZE size);
//


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
    LoadStringW(hInstance, IDC_HOPSCOTCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOPSCOTCH));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOPSCOTCH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOPSCOTCH);
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

    switch (message)
    {   
	case WM_CREATE:
		MANAGER->GetInstance();
		g_API2D.Init(hWnd);
		SetTimer(hWnd, 1, 15, NULL);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			
			g_API2D.Draw(hdc);

            EndPaint(hWnd, &ps);
			SetTimer(hWnd, 1, 10, NULL);
        }
        break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 800;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 800;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
		return false;
	case WM_TIMER:
		g_API2D.Update(hWnd);
		InvalidateRgn(hWnd, 0, false);
		break;
	case WM_KEYDOWN:
		SIZE tmp;
		tmp.cx = g_API2D.GetPosX();
		tmp.cy = g_API2D.GetPosY(); 
		KeyBuffer[wParam] = TRUE;
		
		MovePlayer(hWnd, wParam);
		DrawLine(hWnd, wParam, tmp);	//동작 안함?
		
		if (wParam == VK_RETURN)
		{
			HDC hdc = GetDC(hWnd);			
			g_API2D.subLife();
			InvalidateRgn(hWnd, 0, false);
		}

		if (wParam == VK_HOME)
			g_API2D.setPLAYER_SPEED(g_API2D.getPLAYER_SPEED() + 1);

		if (wParam == VK_END)
			g_API2D.setPLAYER_SPEED(g_API2D.getPLAYER_SPEED() -1);

		break;
	case WM_KEYUP:
		KeyBuffer[wParam] = FALSE;

		if (wParam == VK_SPACE)
			if (g_API2D.getPLAYER_STATUS() == DRAWING)
				g_API2D.setPLAYER_STATUS(RETURNING);
			else
				g_API2D.setPLAYER_STATUS(IDLE);
		else
			g_API2D.setPLAYER_STATUS(IDLE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawLine(HWND hWnd, WPARAM wParam, SIZE size)
{
	HDC hdc = GetDC(hWnd);


	if ((g_API2D.getPLAYER_STATUS() == DRAWING) && g_API2D.DrawingPosXY.size() != NULL)	// 그리기 상태 & 좌표 저장된 것이 1개 이상일 때
	{
		SIZE tmp;
		tmp.cx = g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].cx;
		tmp.cy = g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].cy;

		if (tmp.cx != size.cx)		//x 좌표가 다르면
			if (tmp.cy != size.cy)		// y좌표가 다르면
				g_API2D.DrawingPosXY.push_back(size);	//새로운 좌표로 보고 추가
			else
			{
				tmp.cx = size.cx;			// x는 다르지만 y는 같으므로
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].cx = tmp.cx;	// x좌표만 업데이트
			}
		else if (tmp.cy != size.cy)
		{
			tmp.cy = size.cy;		// y가 다르지만 x는 같으므로
			g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].cy = tmp.cy;		//y좌표만 업데이트
		}

		for (int i = 0; i < g_API2D.DrawingPosXY.size() - 1; i++)
		{
			MoveToEx(hdc, g_API2D.DrawingPosXY[i].cx, g_API2D.DrawingPosXY[i++].cy, NULL);
			LineTo(hdc, g_API2D.DrawingPosXY[i].cx, g_API2D.DrawingPosXY[i].cy);
		}

	}
}

void MovePlayer(HWND hWnd, WPARAM wParam)
{

	if (KeyBuffer[VK_DOWN])
	{
		g_API2D.setPLAYER_STATUS(MOVING);
		g_API2D.setDir(FACING_DOWN);
		g_API2D.AddFrame(1);
		g_API2D.SetPosY(g_API2D.GetPosY() + g_API2D.getPLAYER_SPEED());		
	}

	if (KeyBuffer[VK_UP])
	{
		g_API2D.setPLAYER_STATUS(MOVING);
		g_API2D.setDir(FACING_UP);
		g_API2D.AddFrame(1);
		g_API2D.SetPosY(g_API2D.GetPosY() - g_API2D.getPLAYER_SPEED());				
	}

	if (KeyBuffer[VK_LEFT])
	{
		g_API2D.setPLAYER_STATUS(MOVING);
		g_API2D.setDir(FACING_LEFT);
		g_API2D.AddFrame(1);
		g_API2D.SetPosX(g_API2D.GetPosX() - g_API2D.getPLAYER_SPEED());		
	}

	if (KeyBuffer[VK_RIGHT])
	{
		g_API2D.setPLAYER_STATUS(MOVING);
		g_API2D.setDir(FACING_RIGHT);
		g_API2D.AddFrame(1);
		g_API2D.SetPosX(g_API2D.GetPosX() + g_API2D.getPLAYER_SPEED());		
	}
	if (KeyBuffer[VK_SPACE])
	{
		g_API2D.setPLAYER_STATUS(DRAWING);		
	}

	


	
}
// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
