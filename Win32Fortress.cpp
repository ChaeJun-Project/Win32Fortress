#include "Win32Fortress.h"
#include "Core/GameMain.h"

//Extern
HWND				g_hWnd;
POINT				g_ptMouse;
HINSTANCE			g_hInstance;

// 전역 변수:
HINSTANCE			hInst;
LPCTSTR				lpString = TEXT("Win32API FORTRESS");

//GameMain
GameMain			*main_game;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
void                MyRegisterWindowClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	main_game = new GameMain;
	if (!main_game->Init())
		return false;

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//임시로 인스턴스 핸들을 전역변수 저장
	g_hInstance = hInstance;

	//윈도우 클래스 등록
	MyRegisterWindowClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HDC hdc = GetDC(g_hWnd);
	assert(hdc != NULL);

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TimeManager::GetInstance()->Update();
			main_game->Update();
			main_game->Render(hdc);
		}
	}

	main_game->Release();

	return (int)msg.wParam;
}

//윈도우 클래스 등록
void MyRegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = lpString;
	wcex.hIconSm = wcex.hIcon;

	RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; //인스턴스 핸들을 전역 변수에 저장

	RECT client = { 0, 0, GAME_WIDTH, GAME_HEIGHT };

	AdjustWindowRect(&client, WS_OVERLAPPEDWINDOW, false);

	g_hWnd = CreateWindow(lpString, lpString, WS_OVERLAPPEDWINDOW,
		GAME_START_X, GAME_START_Y, client.right - client.left,
		client.bottom - client.top, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return main_game->MainProc(hWnd, message, wParam, lParam);
}

