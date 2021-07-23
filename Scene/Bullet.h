#pragma once

#include "ObjectBase.h"

#define BULLET_ANIMATION_COUNT 2

//Ŭ���� ���漱��
class Image;
class Animation;
class AnimationManager;

class Bullet : public ObjectBase
{
private:
	Image*  image;
	
	Animation*	ani;
	AnimationManager * motion_list;

	//�÷��̾��� ��ź �̹����� �ĺ��ϱ� ���� Ű ��
	std::string bullet_tag; 

	//�߷�
	float gravity;

	//�߻�ü�� �̵� ��� �ð�
	float elapsed_time;

	//�Ѿ��� ���ݷ�
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

	//�Ѿ��� ���ݷ��� �Ѱ��ֱ� ���� �Լ�
	int GetBulletDamage() const { return damage; }
};

