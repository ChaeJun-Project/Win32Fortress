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
		IDLE_L = 0,     //왼쪽 탐색
		WALK_L = 1,	    //왼쪽 방향으로 걷기
		ATTACK_L = 2,   //왼쪽 방향으로 공격

		IDLE_R = 3,		//오른쪽 탐색
		WALK_R = 4,		//오른쪽 방향으로 걷기
		ATTACK_R = 5,   //오른쪽 방향으로 공격
	};


	//어떤 플레이어인지 결정해주는 변수
	//1: 플레이어1 , 2: 플레이어2
	int player_flag;

	//이미지 렌더링에 사용
	Image*  image;

	//애니메이션 배열
	Animation*	ani[ANIMATION_COUNT];

	//애니메이션을 관리할 애니메이션 리스트
	AnimationManager * motion_list;

	//플레이어 체력 바
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

	float radius; //반지름
	float angle;  //발사 각도
	float speed;  //이동속도

	TPoint end;  //발사 궤도의 끝점

	float length;  //발사 궤도의 길이

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

	//플레이어의 체력을 관리하기 위한 함수
	int GetPlayerHp() const { return hp; }
	void SetPlayerHp(const int bullet_damage) { hp -= bullet_damage; }

private:
	void IncreaseAngle(); //포탄 발사각을 올렸을 때 로직
	void DecreaseAngle(); //포탄 발사각을 내렸을 때 로직
	void MoveRight();	  //캐릭터가 오른쪽으로 움직일 때
	void MoveLeft();	  //캐릭터가 왼쪽으로 움직일 때
	void Attack();		  //캐릭터가 공격했을 때
	void Idle();		  //아무런 이벤트 없이 가만히 있을 때
};

