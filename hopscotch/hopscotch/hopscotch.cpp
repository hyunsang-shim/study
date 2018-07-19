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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOPSCOTCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

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
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//제자리일 경우, 애니메이션을 하기 위한 프레임 스킵용 임시 카운터
	static int idle_cnt = 0;

    switch (message)
    {   
	case WM_CREATE:
		MANAGER->GetInstance();
		g_API2D.Init(hWnd);
		//((MINMAXINFO*)lParam)->ptMaxTrackSize.x = g_API2D.getWidthMax();
		//((MINMAXINFO*)lParam)->ptMaxTrackSize.y = g_API2D.getHeightMax();
		//((MINMAXINFO*)lParam)->ptMinTrackSize.x = g_API2D.getWidthMax();
		//((MINMAXINFO*)lParam)->ptMinTrackSize.y = g_API2D.getHeightMax();
		SetTimer(hWnd, 1, 15, NULL);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);          
			
			g_API2D.Draw(hdc);
			TextOut(hdc, 10, 10, _T("LIFE"), lstrlen(_T("LIFE")));
            EndPaint(hWnd, &ps);
			SetTimer(hWnd, 1, 10, NULL);
        }
        break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
	case WM_GETMINMAXINFO:
		//윈도우 창 크기 변화 방지, 
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = g_API2D.getWidthMax();
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = g_API2D.getHeightMax();
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = g_API2D.getWidthMax();
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = g_API2D.getHeightMax();
		return false;
	case WM_TIMER:
		idle_cnt++;
		if (g_API2D.getPLAYER_STATUS() == IDLE && idle_cnt % 11 >= 10)
			g_API2D.AddFrame(1);

		if (idle_cnt > 10000)
			idle_cnt = 0;

		g_API2D.Update(hWnd);
		InvalidateRgn(hWnd, 0, false);
		break;
	case WM_KEYDOWN:
		POINT tmp;
		tmp.x = g_API2D.GetPosX();
		tmp.y = g_API2D.GetPosY(); 
		KeyBuffer[wParam] = TRUE;
		
		if (wParam == VK_SPACE && g_API2D.getPLAYER_STATUS() != DRAWING)
			g_API2D.SetDrawStart(tmp);
		
		MovePlayer(hWnd, wParam);

		if (wParam == VK_RETURN)
		{
			HDC hdc = GetDC(hWnd);			
			g_API2D.subLife();
			InvalidateRgn(hWnd, 0, TRUE);
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
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void MovePlayer(HWND hWnd, WPARAM wParam)
{
	RECT tmpRect;
	GetClientRect(hWnd, &tmpRect);
	HDC hdc = GetDC(hWnd);
	
	//스페이스 바 = 그리기 시작 / 끝 확인을 위한 다중 키보드 입력 처리
	if (KeyBuffer[VK_SPACE])
		g_API2D.setPLAYER_STATUS(DRAWING);

	//현재 좌표를 구하고, 이전 좌표와 비교하여 추가/갱신 여부를 결정하기 위한 좌표
	POINT newPoint;
	newPoint.x = g_API2D.GetPosX();
	newPoint.y = g_API2D.GetPosY();

	//키 입력에 따라 캐릭터를 이동시키고,
	//현재 그리는 중이면 그리기 좌표점을 업데이트 한다.
	//방향이 바뀌면 새로운 좌표로 인식하고 추가한다.
	if (g_API2D.getPLAYER_STATUS() == DRAWING)
	{
		switch (wParam)
		{
		case VK_UP:

			if (g_API2D.getFacingDir() != FACING_UP)
			{
				//방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);
				//방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_UP);
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosY(g_API2D.GetPosY() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() <= tmpRect.top)
					g_API2D.SetPosY(tmpRect.top);
				//바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.y = g_API2D.GetPosY();
				//새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_UP)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosY(g_API2D.GetPosY() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() <= tmpRect.top)
					g_API2D.SetPosY(tmpRect.top);
				// 마지막 좌표 vector의 y값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].y = g_API2D.GetPosY();
			}
			break;
		case VK_RIGHT:
			if (g_API2D.getFacingDir() != FACING_RIGHT)
			{
				// 방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);
				// 방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_RIGHT);
				// 프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() + g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() >= g_API2D.getWidthMax())
					g_API2D.SetPosX(g_API2D.getWidthMax());
				// 바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.x = g_API2D.GetPosX();
				// 새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_RIGHT)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() + g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() >= g_API2D.getWidthMax())
					g_API2D.SetPosX(g_API2D.getWidthMax());
				// 마지막 좌표 vector의 x값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].x = g_API2D.GetPosX();
			}
			break;
		case VK_DOWN:
			if (g_API2D.getFacingDir() != FACING_DOWN)
			{
				//방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);
				//방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_DOWN);
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosY(g_API2D.GetPosY() + g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() >= tmpRect.bottom)
					g_API2D.SetPosY(tmpRect.bottom);
				//바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.y = g_API2D.GetPosY();
				//새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_DOWN)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosY(g_API2D.GetPosY() + g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() >= tmpRect.bottom)
					g_API2D.SetPosY(tmpRect.bottom);
				// 마지막 좌표 vector의 y값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].y = g_API2D.GetPosY();
			}
			break;
		case VK_LEFT:
			if (g_API2D.getFacingDir() != FACING_LEFT)
			{
				// 방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);
				// 방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_LEFT);
				// 프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() <= 150)
					g_API2D.SetPosX(150);
				// 바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.x = g_API2D.GetPosX();
				// 새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_LEFT)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() <= 150)
					g_API2D.SetPosX(150);
				// 마지막 좌표 vector의 x값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].x = g_API2D.GetPosX();
			}
			break;
		}
	}
	else
	{
		switch (wParam)
		{
		case VK_LEFT:
			if (g_API2D.getFacingDir() != FACING_LEFT)
			{
				// 방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);

				// 방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_LEFT);

				// 프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);

				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() - g_API2D.getPLAYER_SPEED());

				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() <= 150)
					g_API2D.SetPosX(150);

				// 바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.x = g_API2D.GetPosX();

				// 새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_LEFT)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);

				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosY() == 0 || g_API2D.GetPosY() == g_API2D.getHeightMax())
					g_API2D.SetPosX(g_API2D.GetPosX() - g_API2D.getPLAYER_SPEED());

				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() <= 150)
					g_API2D.SetPosX(150);

				// 마지막 좌표 vector의 x값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].x = g_API2D.GetPosX();

			}break;
		case VK_DOWN:
			if (g_API2D.getFacingDir() != FACING_DOWN)
			{
				//방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);

				//방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_DOWN);

				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);

				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosX() == 150 || g_API2D.GetPosX() == g_API2D.getWidthMax())
					g_API2D.SetPosY(g_API2D.GetPosY() + g_API2D.getPLAYER_SPEED());

				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() >= tmpRect.bottom)
					g_API2D.SetPosY(tmpRect.bottom);

				//바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.y = g_API2D.GetPosY();

				//새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_DOWN)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);

				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosX() == 150 || g_API2D.GetPosX() == g_API2D.getWidthMax())
					g_API2D.SetPosY(g_API2D.GetPosY() + g_API2D.getPLAYER_SPEED());

				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() >= tmpRect.bottom)
					g_API2D.SetPosY(tmpRect.bottom);

				// 마지막 좌표 vector의 y값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].y = g_API2D.GetPosY();
			}
			break;
		case VK_RIGHT:
			if (g_API2D.getFacingDir() != FACING_RIGHT)
			{
				// 방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);

				// 방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_RIGHT);

				// 프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);

				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosY() == 0 || g_API2D.GetPosY() == g_API2D.getHeightMax())
					g_API2D.SetPosX(g_API2D.GetPosX() + g_API2D.getPLAYER_SPEED());

				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() >= g_API2D.getWidthMax())
					g_API2D.SetPosX(g_API2D.getWidthMax());

				// 바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.x = g_API2D.GetPosX();

				// 새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_RIGHT)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				g_API2D.SetPosX(g_API2D.GetPosX() + g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosX() >= g_API2D.getWidthMax())
					g_API2D.SetPosX(g_API2D.getWidthMax());
				// 마지막 좌표 vector의 x값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].x = g_API2D.GetPosX();
			}
			break;
		case VK_UP:
			if (g_API2D.getFacingDir() != FACING_UP)
			{
				//방향 바꾸기 직전 좌표를 넣어주고
				g_API2D.DrawingPosXY.push_back(newPoint);
				//방향을 변경한다. 스프라이트 읽기 offset용
				g_API2D.setFacingDir(FACING_UP);
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosX() == 150 || g_API2D.GetPosX() == g_API2D.getWidthMax())
					g_API2D.SetPosY(g_API2D.GetPosY() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() <= tmpRect.top)
					g_API2D.SetPosY(tmpRect.top);
				//바뀐 좌표를 임시 좌표에 갱신하고
				newPoint.y = g_API2D.GetPosY();
				//새로운 좌표로 등록한다.
				g_API2D.DrawingPosXY.push_back(newPoint);
			}
			else if (g_API2D.getFacingDir() == FACING_UP)
			{
				//프레임을 1 프레임 이동시킨다.
				g_API2D.AddFrame(1);
				// 캐릭터를 이동시킨다.
				if (g_API2D.GetPosX() == 150 || g_API2D.GetPosX() == g_API2D.getWidthMax())
					g_API2D.SetPosY(g_API2D.GetPosY() - g_API2D.getPLAYER_SPEED());
				// 캐릭터 위치 보정
				if (g_API2D.GetPosY() <= tmpRect.top)
					g_API2D.SetPosY(tmpRect.top);
				// 마지막 좌표 vector의 y값을 갱신한다.
				g_API2D.DrawingPosXY[g_API2D.DrawingPosXY.size() - 1].y = g_API2D.GetPosY();
			}
			break;
		}
	}




}
