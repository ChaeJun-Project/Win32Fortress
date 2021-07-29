#include "Win32Fortress.h"

ObjectBase::ObjectBase(const float & width, const float & height)
{
	rect = { 0, 0, width, height };
	position = { 0.0f, 0.0f };
	size = { width, height };
	speed = 0.f;
	circle.pt = position;
	circle.r = 0.f;
	is_destroy = false;
	is_collision = false;
}

ObjectBase::ObjectBase(const std::string& tag, const float width, const float height)
	: tag(tag), rect({ 0, 0, width, height }), position({ 0.0f, 0.0f }), size({ width, height })
{
	speed = 0.f;
	circle.pt = position;
	circle.r = 0.f;
	is_destroy = false;
	is_collision = false;
}

ObjectBase::ObjectBase(const std::string& tag, const float x, const float y, const float width, const float height)
	: tag(tag), position({ x, y }), size({ width, height })
{
	rect = TRectMakeCenter(x, y, width, height);
	speed = 0.f;
	circle.pt = position;
	circle.r = 0.f;
	is_destroy = false;
	is_collision = false;
}

ObjectBase::ObjectBase(const ObjectBase & obj)
{
	tag = obj.tag;
	rect = obj.rect;
	position = obj.position;
	size = obj.size;
	speed = obj.speed;
	circle = obj.circle;

	is_destroy = obj.is_destroy;
	is_collision = false;
}

ObjectBase & ObjectBase::operator=(const ObjectBase & obj)
{
	tag = obj.tag;
	rect = obj.rect;
	position = obj.position;
	size = obj.size;
	speed = obj.speed;
	circle = obj.circle;

	is_destroy = obj.is_destroy;
	is_collision = false;

	return *this;
}

void ObjectBase::SetPos(const TPoint& pt)
{
	position = pt;
}

void ObjectBase::SetPos(const float x, const float y)
{
	position = { x, y };
}

void ObjectBase::SetSize(const float width, const float height)
{
	size.width = width;
	size.height = height;
}

TSize ObjectBase::GetSize() const
{
	return size;
}

bool ObjectBase::IsCollision(const ObjectBase* target)
{
	RECT temp;

	RECT r = { static_cast<int>(rect.left), static_cast<int>(rect.top),
		static_cast<int>(rect.right), static_cast<int>(rect.bottom) };

	RECT t = { static_cast<int>(target->GetRect().left), static_cast<int>(target->GetRect().top),
		static_cast<int>(target->GetRect().right), static_cast<int>(target->GetRect().bottom) };

	//두 오브젝트가 서로 충돌했는 지 검사
	if (IntersectRect(&temp, &r, &t))
	{
		return true;
	}

	return false;
}