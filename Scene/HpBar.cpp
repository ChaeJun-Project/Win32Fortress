#include "Win32Fortress.h"

HpBar::HpBar(const std::string& tag, const float x, const float y, const float width, const float height, COLORREF color)
	: ObjectBase(tag, x, y, width, height)
{
	//플레이어의 체력을 저장할 변수 초기화
	hp = 0;
	//해당 플레이어의 체력바 색상
	bar_color = color;
}

HpBar::~HpBar()
{
}

bool HpBar::Init()
{
	return false;
}

void HpBar::Release()
{
}

void HpBar::Update()
{

}

void HpBar::Render(HDC hdc, const TPoint * ptCam)
{
	//뒤의 게이지를 그릴 사각형의 위치
	TPoint pt_back_gage;
	//카메라 위치
	TPoint pC = { 0.0f, 0.0f };

	if (ptCam)
	{
		pt_back_gage = { (GetPos().x - ptCam->x), (GetPos().y - ptCam->y - 100.0f) };
		pC = { ptCam->x, ptCam->y };
	}
	else
	{
		pt_back_gage = { (GetPos().x), (GetPos().y) };
		pt_back_gage = { (GetPos().x), (GetPos().y) };
	}


	//뒤의 게이지를 그릴 사각형의 위치
	{
		HPEN white_pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		//이전 펜의 속성을 저장할 펜 변수 선언 및 빨간 펜 속성 저장
		HPEN old_pen = (HPEN)SelectObject(hdc, white_pen);

		RectangleMakeCenter(hdc, static_cast<int>(pt_back_gage.x), static_cast<int>(pt_back_gage.y), static_cast<int>(GetSize().width), static_cast<int>(GetSize().height));

		//빨간 펜 삭제
		DeleteObject(white_pen);
		//펜 속성 백업
		SelectObject(hdc, old_pen);
	}

	//Hp 게이지 바
	{
		//플레이어1(빨간색)
		//플레이어2(파란색)

		//펜 생성
		HPEN pen = CreatePen(PS_SOLID, 1, bar_color);
		//이전 펜의 속성을 저장할 펜 변수 선언 및 펜 속성 저장
		HPEN old_pen = (HPEN)SelectObject(hdc, pen);
		//브러쉬 생성
		HBRUSH brush = CreateSolidBrush(bar_color);
		//이전 브러쉬의 속성을 저장할 브러쉬 변수
		HBRUSH old_brush = (HBRUSH)SelectObject(hdc, brush);

		rect = TRectMakeCenter(pt_back_gage.x, pt_back_gage.y, GetSize().width, GetSize().height);

		rect.right = rect.left + hp;

		//사각형 그리기
		RectangleMake(hdc, rect);

		//펜 삭제
		DeleteObject(pen);
		//브러쉬 삭제
		DeleteObject(brush);

		//펜 속성 백업
		SelectObject(hdc, old_pen);
		//브러쉬 속성 백업
		SelectObject(hdc, old_brush);
	}
}