#include "Win32Fortress.h"

HpBar::HpBar(const std::string& tag, const float x, const float y, const float width, const float height, COLORREF color)
	: ObjectBase(tag, x, y, width, height)
{
	//�÷��̾��� ü���� ������ ���� �ʱ�ȭ
	hp = 0;
	//�ش� �÷��̾��� ü�¹� ����
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
	//���� �������� �׸� �簢���� ��ġ
	TPoint pt_back_gage;
	//ī�޶� ��ġ
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


	//���� �������� �׸� �簢���� ��ġ
	{
		HPEN white_pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		//���� ���� �Ӽ��� ������ �� ���� ���� �� ���� �� �Ӽ� ����
		HPEN old_pen = (HPEN)SelectObject(hdc, white_pen);

		RectangleMakeCenter(hdc, static_cast<int>(pt_back_gage.x), static_cast<int>(pt_back_gage.y), static_cast<int>(GetSize().width), static_cast<int>(GetSize().height));

		//���� �� ����
		DeleteObject(white_pen);
		//�� �Ӽ� ���
		SelectObject(hdc, old_pen);
	}

	//Hp ������ ��
	{
		//�÷��̾�1(������)
		//�÷��̾�2(�Ķ���)

		//�� ����
		HPEN pen = CreatePen(PS_SOLID, 1, bar_color);
		//���� ���� �Ӽ��� ������ �� ���� ���� �� �� �Ӽ� ����
		HPEN old_pen = (HPEN)SelectObject(hdc, pen);
		//�귯�� ����
		HBRUSH brush = CreateSolidBrush(bar_color);
		//���� �귯���� �Ӽ��� ������ �귯�� ����
		HBRUSH old_brush = (HBRUSH)SelectObject(hdc, brush);

		rect = TRectMakeCenter(pt_back_gage.x, pt_back_gage.y, GetSize().width, GetSize().height);

		rect.right = rect.left + hp;

		//�簢�� �׸���
		RectangleMake(hdc, rect);

		//�� ����
		DeleteObject(pen);
		//�귯�� ����
		DeleteObject(brush);

		//�� �Ӽ� ���
		SelectObject(hdc, old_pen);
		//�귯�� �Ӽ� ���
		SelectObject(hdc, old_brush);
	}
}