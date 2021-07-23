#pragma once

#include "ObjectBase.h"

#define ANIMATION_COUNT 6

//클래스 전방선언
class Image;
class Animation;
class AnimationManager;
class HpBar;

class Player : public ObjectBase
{
private:
	enum LookAtSide
	{
		//왼쪽 방향을 바라볼 때
		LEFTSIDE,
		//오른쪽 방향을 바라볼 때
		RIGHTSIDE,
	};

	//오브젝트의 상태 변화
	enum State
	{
		IDLE_L = 0,
		WALK_L = 1,
		ATTACK_L = 2,

		IDLE_R = 3,
		WALK_R = 4,
		ATTACK_R = 5,
	};


	//어떤 플레이어인지 결정해주는 변수
	//1: 플레이어1 , 2: 플레이어2
	int player_flag;

	Image*  image;
	Animation*	ani[ANIMATION_COUNT];
	AnimationManager * motion_list;

	HpBar* hp_bar;

	//행동 상태 변수
	State	state;

	//랜더링 효과 변수
	BYTE	fade_in;

	//방향을 바꿨는지 체크하는 변수
	bool is_direction_change;

	//총알을 한번만 생성하기 위한 변수
	int bullet_flag;

	//플레이어의 체력
	int hp;

	//플레이어의 방향
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

	//플레이어의 체력을 관리하기 위한 함수
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

