#pragma once

#include "ObjectBase.h"

class HpBar :public ObjectBase
{
private:
	//플레이어의 체력을 저장할 변수
	int hp;
	
	COLORREF bar_color;

public:
	HpBar(const std::string& tag, const float x, const float y, const float width, const float height, COLORREF color);
	~HpBar();

	bool Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc, const TPoint* ptCam) override;

public:
	//실시간으로 플레이어의 체력을 받아오기 위한 함수
	void SetHp(const int PlayerHp) { hp = PlayerHp; }
};

