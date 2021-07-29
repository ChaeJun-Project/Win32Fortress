#pragma once

//����ü ���漱��
//�ش� ����ü���� ������ �Ű������� ����ϱ� ����
struct TRect;
struct TPoint;
struct TCircle;

//������Ʈ�� �浹�� Ž���ϱ� ���� �Լ���
//���� �簢�� �ȿ� ���ԵǾ� �ִ� ��
bool IsPtInTRect(const TRect* pRc, const float x, const float y);
bool IsPtInTRect(const TRect* pRc, const TPoint* pPt);

//�� �簢���� ���� ��ġ�� �κ��� �ִ� ��
bool CollisionTRectAndTRect(const TRect* pRc1, const TRect* pRc2);

//�� ���� ���� ��ġ�� �κ��� �ִ� ��
bool CollisionTCircleAndTCircle(const TCircle* pTC1, const TCircle* pTC2);

//�� �� ������ �Ÿ��� ����
float GetDistance(const float sX, const float sY, const float eX, const float eY);
