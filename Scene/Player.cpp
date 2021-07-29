#include "Win32Fortress.h"

Player::Player(const std::string& tag, const float x, const float y, const float width, const float height, const int& flag)
	: ObjectBase(tag, x, y, width, height)
{
	//플레이어 속성 초기화
	Init();

	//플레이어 1인지 2인지 플래그 값
	player_flag = flag;

	//플레이어의 체력
	hp = 100;

	switch (player_flag)
	{
	case 1:
	{
		//행동 상태 변수 초기화
		side = LookAtSide::RIGHTSIDE;
		state = State::IDLE_R;
		image = ImageManager::GetInstance()->FindImage("IDLE_R");
		angle = 1.0f;
		hp_bar = new HpBar("PLAYER1_HP", x, y, static_cast<float>(hp), 20.0f, RGB(255, 0, 0));
	}
	break;
	case 2:
	{
		//행동 상태 변수 초기화
		side = LookAtSide::LEFTSIDE;
		state = State::IDLE_L;
		image = ImageManager::GetInstance()->FindImage("IDLE_L");
		angle = PI - 1.0f;
		hp_bar = new HpBar("PLAYER2_HP", x, y, static_cast<float>(hp), 20.0f, RGB(0, 0, 255));
	}
	break;

	default:
		break;
	}

	//플레이어 스피드
	speed = 10.0f;

	//방향을 바꿨는지 체크하는 변수
	is_direction_change = false;

	//총알을 한번만 생성하기 위한 변수
	bullet_flag = 0;

	hp_bar->SetHp(hp);

	radius = (width > height) ? width * 0.5f : height * 0.5f;

	//충돌처리를 위한 변수에 반지름값 저장
	circle.r = radius - 20.0f;
	circle.pt = GetPos();

	length = 90.0f;

	end.x = position.x + (cosf(angle) * length);
	end.y = position.y + (-sinf(angle) * length);
}

Player::~Player()
{
	Release();
}

bool Player::Init()
{
	//애니메이션 리스트를 넣을 애니메이션 모션 리스트
	motion_list = new AnimationManager;

	//애니메이션의 정보를 저장할 애니메이션 객체
	//애니메이션 모션 리스트에 넣기 위함
	for (int i = 0; i < ANIMATION_COUNT; ++i)
	{
		ani[i] = new Animation;
	}

	//LEFTSIDE(0~2)
	//=================================================================================================================
	//왼쪽 IDLE
	ImageManager::GetInstance()->AddFrameImage(
		"IDLE_L", TEXT("../BITMAP/PLAYER/PLAYER_IDLE_LEFT.bmp"), 560, 140, 4, 1, true, RGB(255, 0, 255));

	//왼쪽 WALK
	ImageManager::GetInstance()->AddFrameImage(
		"WALK_L", TEXT("../BITMAP/PLAYER/PLAYER_WALK_LEFT.bmp"), 2240, 140, 16, 1, true, RGB(255, 0, 255));

	//왼쪽 ATTACK
	ImageManager::GetInstance()->AddFrameImage(
		"ATTACK_L", TEXT("../BITMAP/PLAYER/PLAYER_ATTACK_LEFT.bmp"), 960, 140, 4, 1, true, RGB(255, 0, 255));
	//=================================================================================================================

	//RIGHTSIDE(3~5)
	//=================================================================================================================
	//오른쪽 IDLE
	ImageManager::GetInstance()->AddFrameImage(
		"IDLE_R", TEXT("../BITMAP/PLAYER/PLAYER_IDLE_RIGHT.bmp"), 560, 140, 4, 1, true, RGB(255, 0, 255));

	//오른쪽 WALK
	ImageManager::GetInstance()->AddFrameImage(
		"WALK_R", TEXT("../BITMAP/PLAYER/PLAYER_WALK_RIGHT.bmp"), 2240, 140, 16, 1, true, RGB(255, 0, 255));

	//오른쪽 ATTACK
	ImageManager::GetInstance()->AddFrameImage(
		"ATTACK_R", TEXT("../BITMAP/PLAYER/PLAYER_ATTACK_RIGHT.bmp"), 960, 140, 4, 1, true, RGB(255, 0, 255));
	//=================================================================================================================

	//LEFTSIDE(0~2)
	//=================================================================================================================
	//왼쪽 IDLE
	image = ImageManager::GetInstance()->FindImage("IDLE_L");
	assert(image != nullptr);
	ani[0]->Init(image, 0, 4, true);
	ani[0]->SetFPS(200);
	motion_list->AddMotion(ani[0]);

	//왼쪽 WALK
	image = ImageManager::GetInstance()->FindImage("WALK_L");
	assert(image != nullptr);
	ani[1]->Init(image, 0, 16, false);
	ani[1]->SetFPS(50);
	motion_list->AddMotion(ani[1]);

	//왼쪽 ATTACK
	image = ImageManager::GetInstance()->FindImage("ATTACK_L");
	assert(image != nullptr);
	ani[2]->Init(image, 0, 4, false);
	ani[2]->SetFPS(50);
	motion_list->AddMotion(ani[2]);
	//=================================================================================================================


	//RIGHTSIDE(3~5)
	//=================================================================================================================
	//오른쪽 IDLE
	image = ImageManager::GetInstance()->FindImage("IDLE_R");
	assert(image != nullptr);
	ani[3]->Init(image, 0, 4, true);
	ani[3]->SetFPS(200);
	motion_list->AddMotion(ani[3]);

	//오른쪽 WALK
	image = ImageManager::GetInstance()->FindImage("WALK_R");
	assert(image != nullptr);
	ani[4]->Init(image, 0, 16, false);
	ani[4]->SetFPS(50);
	motion_list->AddMotion(ani[4]);

	//오른쪽 ATTACK
	image = ImageManager::GetInstance()->FindImage("ATTACK_R");
	assert(image != nullptr);
	ani[5]->Init(image, 0, 4, false);
	ani[5]->SetFPS(50);
	motion_list->AddMotion(ani[5]);
	//=================================================================================================================


	for (int i = 0; i < ANIMATION_COUNT; ++i)
	{
		motion_list->Play(i);
	}

	return true;
}

void Player::Release()
{
	for (int i = 0; i < ANIMATION_COUNT; ++i)
	{
		SAFE_DELETE(ani[i]);
	}

	SAFE_DELETE(motion_list);
}

void Player::IncreaseAngle()
{
	//왼쪽을 바라보는 경우
	if (side == LookAtSide::LEFTSIDE)
	{
		if ((PI*0.5f) <= angle && angle <= PI)
		{
			angle -= 0.03f;

		}

		else if ((PI*0.5f) > angle)
		{
			angle = PI - 1.0f;

		}
	}

	//오른쪽을 바라보는 경우
	else if (side == LookAtSide::RIGHTSIDE)
	{
		if (0.f <= angle && angle <= (PI*0.5f))
		{
			angle += 0.03f;

		}

		else if (angle > (PI*0.5f))
		{
			angle = 1.0f;

		}
	}
}

void Player::DecreaseAngle()
{
	//왼쪽을 바라보는 경우
	if (side == LookAtSide::LEFTSIDE)
	{
		if ((PI*0.5f) <= angle && angle <= PI)
		{
			angle += 0.03f;

		}

		else if (angle > PI)
		{
			angle = PI - 1.0f;

		}
	}

	//오른쪽을 바라보는 경우
	else if (side == LookAtSide::RIGHTSIDE)
	{
		if (0.f <= angle && angle <= (PI*0.5f))
		{
			angle -= 0.03f;
		}

		else if (angle < 0.f)
		{
			angle = 1.0f;
		}
	}
}

void Player::MoveRight()
{
	state = State::WALK_R;
	side = LookAtSide::RIGHTSIDE;
	is_direction_change = true;
	image = ImageManager::GetInstance()->FindImage("WALK_R");
	position.x += speed;
}

void Player::MoveLeft()
{
	state = State::WALK_L;
	side = LookAtSide::LEFTSIDE;
	is_direction_change = true;
	image = ImageManager::GetInstance()->FindImage("WALK_L");
	position.x -= speed;
}


void Player::Attack()
{
	if (side == LookAtSide::LEFTSIDE)
	{
		state = State::ATTACK_L;
		image = ImageManager::GetInstance()->FindImage("ATTACK_L");

	}

	else if (side == LookAtSide::RIGHTSIDE)
	{
		state = State::ATTACK_R;
		image = ImageManager::GetInstance()->FindImage("ATTACK_R");

	}
}

void Player::Idle()
{
	if (side == LookAtSide::LEFTSIDE)
	{
		state = State::IDLE_L;
		image = ImageManager::GetInstance()->FindImage("IDLE_L");
	}

	else if (side == LookAtSide::RIGHTSIDE)
	{
		state = State::IDLE_R;
		image = ImageManager::GetInstance()->FindImage("IDLE_R");
	}
}

void Player::Update()
{
	//해당 플레이어 Hp 갱신
	hp_bar->SetHp(hp);

	switch (player_flag)
	{
		//플레이어 1
	case 1:
	{
		//W(각도를 올림)
		if (KEYPRESS(0x57))
		{
			IncreaseAngle();
		}

		//S(각도를 내림)
		if (KEYPRESS(0x53))
		{
			DecreaseAngle();
		}

		//D(오른쪽 이동)
		if (KEYPRESS(0x44))
		{
			MoveRight();
		}

		//A(왼쪽 이동)
		else if (KEYPRESS(0x41))
		{
			MoveLeft();
		}

		//공격모션
		else if (KEYPRESS(VK_CONTROL))
		{
			Attack();
		}

		//대기모션
		else
		{
			Idle();
		}

	}
	break;

	//플레이어2
	case 2:
	{
		//각도를 올림
		if (KEYPRESS(VK_UP))
		{
			IncreaseAngle();
		}

		//각도를 내림
		if (KEYPRESS(VK_DOWN))
		{
			DecreaseAngle();
		}

		//오른쪽 이동
		if (KEYPRESS(VK_RIGHT))
		{
			MoveRight();
		}

		//왼쪽 이동
		else if (KEYPRESS(VK_LEFT))
		{
			MoveLeft();
		}

		//공격모션
		else if (KEYPRESS(VK_SPACE))
		{
			Attack();
		}

		//대기모션
		else
		{
			Idle();
		}

	}
	break;

	default:
		break;
	}


	//공격 애니메이션이 나올 경우 총알생성을 단 한번만 하도록 하는 부분
	if (state == State::ATTACK_R || state == State::ATTACK_L)
	{
		if (motion_list->FindMotion(state)->GetNowPlayIndex() == 0)
		{
			bullet_flag++;
			if (bullet_flag == 1)
			{
				CreateBullet();
			}
		}
	}

	else
	{
		bullet_flag = 0;
	}


	//오른쪽에서 왼쪽을 바라보는 경우
	if (is_direction_change && (side == LookAtSide::LEFTSIDE))
	{
		if ((0.0f < angle) && (angle < (PI*0.5f)))
		{
			angle = PI - angle;
			is_direction_change = false;
		}
	}

	//왼쪽에서 오른쪽을 바라보는 경우
	else if (is_direction_change && (side == LookAtSide::RIGHTSIDE))
	{
		if (((PI*0.5f) < angle) && (angle < PI))
		{
			angle = PI - angle;
			is_direction_change = false;
		}
	}

	circle.pt = GetPos();

	end.x = position.x + (cosf(angle) * length);
	end.y = position.y + (-sinf(angle) * length);


	//화면 밖으로 나가는 것을 방지
	//왼쪽
	if (position.x <= 100.0f)
	{
		position.x = 100.0f;
	}
	//오른쪽
	else if (position.x >= static_cast<float>(WORLD_WIDTH - 100))
	{
		position.x = static_cast<float>(WORLD_WIDTH - 100);
	}

	//Hp바의 위치를 계속해서 갱신
	hp_bar->SetPos(GetPos());

	motion_list->FindMotion(state)->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
}

void Player::Render(HDC hdc, const TPoint* ptCam)
{
	//충돌처리 원을 중심점
	TPoint pt = { 0.0f, 0.0f };
	//플레이어를 그릴 위치
	TPoint ptAni = { 0.0f, 0.0f };
	//카메라 위치
	TPoint pC = { 0.0f, 0.0f };

	//카메라의 좌표가 있는 경우
	//플레이어와의 카메라의 상대적인 위치에 플레이어를 그려야 함
	if (ptCam)
	{
		//왼쪽으로 걷는 모션일 때만 값 조정
		if (state == State::ATTACK_L)
		{
			//플레이어를 그릴 위치
			ptAni = { (GetPos().x - ptCam->x - radius - 100.0f),
				(GetPos().y - ptCam->y - GetSize().height*0.5f) };
		}

		//그 외의 모든 모션일 때 그릴 위치
		else
		{
			//플레이어를 그릴 위치
			ptAni = { (GetPos().x - ptCam->x - radius), (GetPos().y - ptCam->y - radius) };
		}

		//충돌처리 원의 중심점
		pt = { (GetPos().x - ptCam->x), (GetPos().y - ptCam->y) };
		//카메라의 위치
		pC = { ptCam->x, ptCam->y };
	}

	else
	{
		//플레이어를 그릴 위치
		ptAni = { (GetPos().x - radius), (GetPos().y - radius) };
		//카메라의 위치
		pt = { (GetPos().x), (GetPos().y) };
	}

	//충돌원
	EllipseMakeCenter(hdc, static_cast<int>(pt.x), static_cast<int>(pt.y), static_cast<int>(circle.r) * 2, static_cast<int>(circle.r) * 2);

	//궤도 선
	{
		HPEN pen = nullptr;
		HPEN old_pen = nullptr;

		switch (player_flag)
		{
		case 1:
		{
			//빨간 펜 생성
			pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
			//이전 펜의 속성을 저장할 펜 변수 선언 및 빨간 펜 속성 저장
			old_pen = (HPEN)SelectObject(hdc, pen);
		}
		break;
		case 2:
		{
			//파란 펜 생성
			pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
			//이전 펜의 속성을 저장할 펜 변수 선언 및 빨간 펜 속성 저장
			old_pen = (HPEN)SelectObject(hdc, pen);

		}
		break;
		default:
			break;
		}

		//발사 궤도
		LineMake(hdc, static_cast<int>(pt.x), static_cast<int>(pt.y),
			static_cast<int>(end.x - pC.x), static_cast<int>(end.y - pC.y));


		//빨간 펜 삭제
		DeleteObject(pen);


		//펜 속성 백업
		SelectObject(hdc, old_pen);
	}

	//플레이어 애니메이션
	image->AniRender(hdc, static_cast<int>(ptAni.x), static_cast<int>(ptAni.y), motion_list->FindMotion(state));

	//플레이어 체력 바
	hp_bar->Render(hdc, ptCam);
}

void Player::CreateBullet()
{
	//업 캐스팅
	ObjectBase* object = new Bullet("Player" + std::to_string(player_flag) + "_Bullet", end.x, end.y, 40.0f, 40.0f, player_flag);
	object->SetDestroy(false);

	//다운 캐스팅
	Bullet* bullet = dynamic_cast<Bullet*>(object);
	assert(bullet != nullptr);
	bullet->SetAngle(angle);

	//오브젝트 매니저에 추가
	ObjectManager::GetInstance()->AddObject(object, player_flag);
}
