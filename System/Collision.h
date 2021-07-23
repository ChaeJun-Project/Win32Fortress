#pragma once

struct TRect;
struct TPoint;
struct TCircle;

bool IsPtInTRect(const TRect* pRc, const float x, const float y);
bool IsPtInTRect(const TRect* pRc, const TPoint* pPt);

bool CollisionTRectAndTRect(const TRect* pRc1, const TRect* pRc2);

bool CollisionTCircleAndTCircle(const TCircle* pTC1, const TCircle* pTC2);

float GetDistance(const float sX, const float sY, const float eX, const float eY);
