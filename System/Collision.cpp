#include "Win32Fortress.h"

//���� �簢�� �ȿ� ���ԵǾ� �ִ� ��
bool IsPtInTRect(const TRect* pRc, const float x, const float y)
{
	if ((x >= pRc->left && x <= pRc->right) &&
		(y >= pRc->top && y <= pRc->bottom))
		return true;

	return false;
}

bool IsPtInTRect(const TRect* pRc, const TPoint* pPt)
{
	return IsPtInTRect(pRc, pPt->x, pPt->y);
}

//�� �簢���� ���� ��ġ�� �κ��� �ִ� ��
bool CollisionTRectAndTRect(const TRect * pRc1, const TRect * pRc2)
{
	//���� 1: pRc1�� left ���� pRc2�� right �� ���� �۰ų� ����  
	//pRc1�� right ���� pRc2�� left �� ���� ũ�ų� ���� ���
	if (pRc1->left <= pRc2->right && pRc1->right >= pRc2->left)
	{
		//���� 2: pRc1�� top ���� pRc2�� bottom �� ���� �۰ų� ����  
		//pRc1�� bottom ���� pRc2�� top �� ���� ũ�ų� ���� ���
		if (pRc1->top <= pRc2->bottom && pRc1->bottom >= pRc2->top)
			return true; //���� 1�� 2�� ��� �����ؾ� �浹�ߴٰ� �Ǵ�
	}

	return false;
}

//�� ���� ���� ��ġ�� �κ��� �ִ� ��
bool CollisionTCircleAndTCircle(const TCircle * pTC1, const TCircle * pTC2)
{
	//�� ���� �������� ��ģ �� >= �� ���� �߽� ��ǥ�� �Ÿ� => �浹
	if ((pTC1->r + pTC2->r) >= GetDistance(pTC1->pt.x, pTC1->pt.y, pTC2->pt.x, pTC2->pt.y))
		return true;

	return false;
}

//�� �� ������ �Ÿ��� ����
float GetDistance(const float sX, const float sY, const float eX, const float eY)
{
	float x = eX - sX;
	float y = eY - sY;

	//������ ��ȯ
	return sqrtf((x*x) + (y*y));
}


