#pragma once

//구조체 전방선언
//해당 구조체들을 포인터 매개변수로 사용하기 위함
struct TRect;
struct TPoint;
struct TCircle;

//오브젝트간 충돌을 탐지하기 위한 함수들
//점이 사각형 안에 포함되어 있는 지
bool IsPtInTRect(const TRect* pRc, const float x, const float y);
bool IsPtInTRect(const TRect* pRc, const TPoint* pPt);

//두 사각형이 서로 겹치는 부분이 있는 지
bool CollisionTRectAndTRect(const TRect* pRc1, const TRect* pRc2);

//두 원이 서로 겹치는 부분이 있는 지
bool CollisionTCircleAndTCircle(const TCircle* pTC1, const TCircle* pTC2);

//두 점 사이의 거리를 구함
float GetDistance(const float sX, const float sY, const float eX, const float eY);
