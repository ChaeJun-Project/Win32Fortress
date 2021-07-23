#pragma once
#include "GameBase.h"

class GameMain : public GameBase
{
public:
	GameMain() = default;
	~GameMain();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};





