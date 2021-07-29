#include "Win32Fortress.h"

GameMain::~GameMain()
{
	ImageManager::GetInstance()->Delete();
	ObjectManager::GetInstance()->Delete();
}

bool GameMain::Init()
{
	__super::Init();

	ObjectManager::Create();

	return true;
}

void GameMain::Release()
{
	ImageManager::GetInstance()->Release();
	ObjectManager::GetInstance()->Release();

	__super::Release();
}

void GameMain::Update()
{
	__super::Update();

	ObjectManager::GetInstance()->Update();
}

void GameMain::Render(HDC hdc)
{
	HDC backDC = GetBackBuffer()->GetMemDC();
	PatBlt(backDC, 0, 0, GAME_WIDTH, GAME_HEIGHT, WHITENESS);
	//=======================================================================

	ObjectManager::GetInstance()->Render(backDC);

	//=======================================================================
	GetBackBuffer()->Render(hdc, 0, 0);
}

