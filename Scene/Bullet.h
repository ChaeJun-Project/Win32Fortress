#pragma once

#include "ObjectBase.h"

#define BULLET_ANIMATION_COUNT 2

//클래스 전방선언
class Image;
class Animation;
class AnimationManager;

class Bullet : public ObjectBase
{
private:
	Image*  image;
	
	Animation*	ani;
	AnimationManager * motion_list;

	//플레이어의 포탄 이미지를 식별하기 위한 키 값
	std::string bullet_tag; 

	//중력
	float gravity;

	//발사체의 이동 경과 시간
	float elapsed_time;

	//총알의 공격력
	int damage;

	float angle;
	float radius;

public:
	Bullet() = delete;
	Bullet(const std::string& tag, const float x, const float y, const float width, const float height, const int& flag);
	Bullet(const Bullet & other);

	~Bullet();

	Bullet& operator=(const Bullet& other);

	bool Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc, const TPoint* ptCam) override;

	float GetRadius() const { return radius; }
	void SetRadius(const float r) { radius = r; }

	float GetAngle() const { return angle; }
	void  SetAngle(const float a) { angle = a; }

	//총알의 공격력을 넘겨주기 위한 함수
	int GetBulletDamage() const { return damage; }
};

