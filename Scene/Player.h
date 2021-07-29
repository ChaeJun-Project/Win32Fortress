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
		IDLE_L = 0,     //���� Ž��
		WALK_L = 1,	    //���� �������� �ȱ�
		ATTACK_L = 2,   //���� �������� ����

		IDLE_R = 3,		//������ Ž��
		WALK_R = 4,		//������ �������� �ȱ�
		ATTACK_R = 5,   //������ �������� ����
	};


	//� �÷��̾����� �������ִ� ����
	//1: �÷��̾�1 , 2: �÷��̾�2
	int player_flag;

	//�̹��� �������� ���
	Image*  image;

	//�ִϸ��̼� �迭
	Animation*	ani[ANIMATION_COUNT];

	//�ִϸ��̼��� ������ �ִϸ��̼� ����Ʈ
	AnimationManager * motion_list;

	//�÷��̾� ü�� ��
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

	float radius; //������
	float angle;  //�߻� ����
	float speed;  //�̵��ӵ�

	TPoint end;  //�߻� �˵��� ����

	float length;  //�߻� �˵��� ����

public:
	Player() = delete;
	~Player();

	explicit Player(const std::string& tag, const float x, const float y, const float width, const float height, const int& flag);

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
	void IncreaseAngle(); //��ź �߻簢�� �÷��� �� ����
	void DecreaseAngle(); //��ź �߻簢�� ������ �� ����
	void MoveRight();	  //ĳ���Ͱ� ���������� ������ ��
	void MoveLeft();	  //ĳ���Ͱ� �������� ������ ��
	void Attack();		  //ĳ���Ͱ� �������� ��
	void Idle();		  //�ƹ��� �̺�Ʈ ���� ������ ���� ��
};

