// Game_PushBrick.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Game_PushBrick.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//나의 전역 선언
//=========================================================================

POINT user = { RECT_SIZE / 2, RECT_SIZE / 2};
RECT userBox;
MOVE_DIR user_dir;

using std::vector;
vector<RECT> Bricks;
vector<RECT> goalPoint;


//==========================================================================

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDC_GAMEPUSHBRICK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEPUSHBRICK));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEPUSHBRICK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //화면 해상도 받기
   int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
   int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

   //창 화면 중앙 위치 계산(좌측 상단점)
   int nWinPosX = nResolutionX / 2 - WINSIZE_X / 2;
   int nWinPosY = nResolutionY / 2 - WINSIZE_Y / 2;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      nWinPosX, nWinPosY, WINSIZE_X, WINSIZE_Y, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //윈도우 사이즈 조정(타이틀 바 및 메뉴 사이즈를 실 사이즈에서 제외)
   {
       //원하는 작업 영역
       RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZE_X, nWinPosY + WINSIZE_Y };

       //원하는 작업 영역 크기, 스타일 값, 메뉴의 여부를 넘기면
       //원하는 작업 영역에 맞는 윈도우 크기를 계산해 rt에 넣어줌
       AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

       //윈도우의 위치, 크기 변경 함수
       MoveWindow(
           hWnd,
           nWinPosX,			//x
           nWinPosY,			//y
           rt.right - rt.left,	//너비
           rt.bottom - rt.top,	//높이
           TRUE				//창을 새로 그릴것인가 ?
       );
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 10, NULL);

        srand((unsigned)time(NULL));

        Bricks.push_back(makeBrick(15, 10));
        Bricks.push_back(makeBrick(10, 10));
        Bricks.push_back(makeBrick(15, 13));

        goalPoint.push_back(makeBrick(31, 15));
        goalPoint.push_back(makeBrick(31, 16));
        goalPoint.push_back(makeBrick(31, 17));
    }
    break;

    case WM_TIMER:
    {
        InvalidateRect(hWnd, NULL, true);

        userBox = RECT_MAKE(user.x, user.y, RECT_REALSIZE);

        int goalCount = 0;

        RECT rt;
        for (auto iter = Bricks.begin(); iter != Bricks.end(); iter++)
        {
            RECT& rtIter = *iter;
            if (IntersectRect(&rt, &rtIter, &userBox))
            {
                pushBrick(rtIter, user_dir);
            }
        }

        for (auto iter = goalPoint.begin(); iter != goalPoint.end(); iter++)
        {
            RECT& goalIter = *iter;
            for (auto iter = Bricks.begin(); iter != Bricks.end(); iter++)
            {
                RECT& rtIter = *iter;
                if (IntersectRect(&rt, &goalIter, &rtIter))
                {
                    goalCount++;
                }
            }
        }

        if (goalCount == Bricks.size())
            exit(1);

    }
    break;

    case WM_KEYDOWN:
    {
        moveCharacter(wParam, user, user_dir);
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            drawMap(hdc, HORIZEN, VERTICAL);

            RECT_DRAW(userBox);

            for (const auto& rect : Bricks)
                RECT_DRAW(rect);

            for (const auto& rect : goalPoint)
                RECT_DRAW(rect);
            
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:
    {

    }
    break;

    case WM_MOUSEMOVE:
    {
        
    }
    break;

    case WM_LBUTTONUP:
    {

    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
