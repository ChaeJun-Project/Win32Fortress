#include "Win32Fortress.h"

void GameBase::SetBackBuffer()
{
	backBuffer = new BackBuffer;
	bool bResult = backBuffer->Init(GAME_WIDTH, GAME_HEIGHT);
	assert(bResult == true);
}

GameBase::GameBase()
{

}

GameBase::~GameBase()
{
}

bool GameBase::Init()
{
	//Create BackBuffer
	SetBackBuffer();
	//Create Timer
	TimeManager::Create();
	TimeManager::GetInstance()->Init(60.f);
	//Create Input 
	Input::Create();

	return true;
}

void GameBase::Release()
{
	//Delete Timer
	TimeManager::GetInstance()->Delete();
	//Delete Input
	Input::GetInstance()->Delete();

	//Delete BackBuffer
	GetBackBuffer()->Release();
}

void GameBase::Update()
{
	InvalidateRect(g_hWnd, 0, false);
}

void GameBase::Render(HDC hdc)
{
}

LRESULT GameBase::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		Update();
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		Render(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
