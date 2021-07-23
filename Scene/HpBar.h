#pragma once

#include "ObjectBase.h"

class HpBar :public ObjectBase
{
private:
	//�÷��̾��� ü���� ������ ����
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
	//�ǽð����� �÷��̾��� ü���� �޾ƿ��� ���� �Լ�
	void SetHp(const int PlayerHp) { hp = PlayerHp; }
};

