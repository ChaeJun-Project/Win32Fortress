#include "Win32Fortress.h"

bool IsPtInTRect(const TRect* pRc, const float x, const float y)
{
	if ((x > pRc->left && x < pRc->right) &&
		(y > pRc->top && y < pRc->bottom))
		return true;

	return false;
}

bool IsPtInTRect(const TRect* pRc, const TPoint* pPt)
{
	return IsPtInTRect(pRc, pPt->x, pPt->y);
}

bool CollisionTRectAndTRect(const TRect * pRc1, const TRect * pRc2)
{
	if (pRc1->left <= pRc2->right && pRc1->right >= pRc2->left)
	{
		if (pRc1->top <= pRc2->bottom && pRc1->bottom >= pRc2->top)
			return true;
	}

	return false;
}

bool CollisionTCircleAndTCircle(const TCircle * pTC1, const TCircle * pTC2)
{
	if ((pTC1->r + pTC2->r) >= GetDistance(pTC1->pt.x, pTC1->pt.y, pTC2->pt.x, pTC2->pt.y))
		return true;

	return false;
}


float GetDistance(const float sX, const float sY, const float eX, const float eY)
{
	float x = eX - sX;
	float y = eY - sY;

	return sqrtf((x*x) + (y*y));
}


