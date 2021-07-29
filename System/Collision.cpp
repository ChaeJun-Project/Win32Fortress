#include "Win32Fortress.h"

//점이 사각형 안에 포함되어 있는 지
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

//두 사각형이 서로 겹치는 부분이 있는 지
bool CollisionTRectAndTRect(const TRect * pRc1, const TRect * pRc2)
{
	//조건 1: pRc1의 left 값이 pRc2의 right 값 보다 작거나 같고  
	//pRc1의 right 값이 pRc2의 left 값 보다 크거나 같은 경우
	if (pRc1->left <= pRc2->right && pRc1->right >= pRc2->left)
	{
		//조건 2: pRc1의 top 값이 pRc2의 bottom 값 보다 작거나 같고  
		//pRc1의 bottom 값이 pRc2의 top 값 보다 크거나 같은 경우
		if (pRc1->top <= pRc2->bottom && pRc1->bottom >= pRc2->top)
			return true; //조건 1과 2가 모두 충족해야 충돌했다고 판단
	}

	return false;
}

//두 원이 서로 겹치는 부분이 있는 지
bool CollisionTCircleAndTCircle(const TCircle * pTC1, const TCircle * pTC2)
{
	//두 원의 반지름을 합친 값 >= 두 원의 중심 좌표의 거리 => 충돌
	if ((pTC1->r + pTC2->r) >= GetDistance(pTC1->pt.x, pTC1->pt.y, pTC2->pt.x, pTC2->pt.y))
		return true;

	return false;
}

//두 점 사이의 거리를 구함
float GetDistance(const float sX, const float sY, const float eX, const float eY)
{
	float x = eX - sX;
	float y = eY - sY;

	//제곱근 반환
	return sqrtf((x*x) + (y*y));
}


