#pragma once

#include "Win32Fortress.h"

//Struct Define
struct TSize
{
	float width;
	float height;

	TSize() : width(0.0f), height(0.0f) {}
	TSize(float width, float height) : width(width), height(height) {}
};

struct TPoint
{
	float x;
	float y;

	TPoint() : x(0.0f), y(0.0f) {}
	TPoint(float x, float y) : x(x), y(y) {}
};

struct TRect
{
	float left;
	float top;
	float right;
	float bottom;

	TRect() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
	TRect(float l, float t, float r, float b)
		: left(l), top(t), right(r), bottom(b) {}
};

struct TCircle
{
	TPoint	pt;
	float	r;

	TCircle() : pt({ 0.0f, 0.0f }), r(0.0f) {}
	TCircle(const float x, const float y, const float r) : pt({ x, y }), r(r) {}
	TCircle(const TPoint& pt, const float r) : pt(pt), r(r) {}
};


inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline TRect TRectMakeCenter(float x, float y, float width, float height)
{
	TRect rc = { x - (width * 0.5f), y - (height * 0.5f), x + (width * 0.5f), y + (height * 0.5f) };
	return rc;
}

//Draw Function
inline void LineMake(HDC hdc, int sx, int sy, int ex, int ey)
{
	MoveToEx(hdc, sx, sy, NULL);
	LineTo(hdc, ex, ey);
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMake(HDC hdc, const RECT& rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

inline void RectangleMake(HDC hdc, const TRect& rect)
{
	Rectangle(hdc, static_cast<int>(rect.left), static_cast<int>(rect.top), static_cast<int>(rect.right), static_cast<int>(rect.bottom));
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void EllipseMake(HDC hdc, const RECT& rect)
{
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}