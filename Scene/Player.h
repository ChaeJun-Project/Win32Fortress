#pragma once

#include "ObjectBase.h"

#define ANIMATION_COUNT 6

//Ŭ���� ���漱��
class Image;
class Animation;
class AnimationManager;
class HpBar;

class Player : public ObjectBase
{
private:
	enum LookAtSide
	{
		//���� ������ �ٶ� ��
		LEFTSIDE,
		//������ ������ �ٶ� ��
		RIGHTSIDE,
	};

	//������Ʈ�� ���� ��ȭ
	enum State
	{
		IDLE_L = 0,
		WALK_L = 1,
		ATTACK_L = 2,

		IDLE_R = 3,
		WALK_R = 4,
		ATTACK_R = 5,
	};


	//� �÷��̾����� �������ִ� ����
	//1: �÷��̾�1 , 2: �÷��̾�2
	int player_flag;

	Image*  image;
	Animation*	ani[ANIMATION_COUNT];
	AnimationManager * motion_list;

	HpBar* hp_bar;

	//�ൿ ���� ����
	State	state;

	//������ ȿ�� ����
	BYTE	fade_in;

	//������ �ٲ���� üũ�ϴ� ����
	bool is_direction_change;

	//�Ѿ��� �ѹ��� �����ϱ� ���� ����
	int bullet_flag;

	//�÷��̾��� ü��
	int hp;

	//�÷��̾��� ����
	LookAtSide side;

	TPoint end;

	float radius;
	float angle;
	float speed;

	float length;

public:
	Player() = delete;
	~Player();

	Player(const std::string& tag, const float x, const float y, const float width, const float height, const int& flag);
	
	bool Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc, const TPoint* ptCam) override;

public:
	void CreateBullet();

	float GetRadius() const { return radius; }
	void SetRadius(const float r) { radius = r; }

	float GetAngle() const { return angle; }
	void  SetAngle(const float a) { angle = a; }

	//�÷��̾��� ü���� �����ϱ� ���� �Լ�
	int GetPlayerHp() const { return hp; }
	void SetPlayerHp(const int bullet_damage) { hp -= bullet_damage; }

private:
    void IncreaseAngle();
	void DecreaseAngle();
	void MoveRight();
	void MoveLeft();
	void Attack();
	void Idle();
};

