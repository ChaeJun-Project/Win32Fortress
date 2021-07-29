#include "Win32Fortress.h"

Player::Player(const std::string& tag, const float x, const float y, const float width, const float height, const int& flag)
	: ObjectBase(tag, x, y, width, height)
{
	//�÷��̾� �Ӽ� �ʱ�ȭ
	Init();

	//�÷��̾� 1���� 2���� �÷��� ��
	player_flag = flag;

	//�÷��̾��� ü��
	hp = 100;

	switch (player_flag)
	{
	case 1:
	{
		//�ൿ ���� ���� �ʱ�ȭ
		side = LookAtSide::RIGHTSIDE;
		state = State::IDLE_R;
		image = ImageManager::GetInstance()->FindImage("IDLE_R");
		angle = 1.0f;
		hp_bar = new HpBar("PLAYER1_HP", x, y, static_cast<float>(hp), 20.0f, RGB(255, 0, 0));
	}
	break;
	case 2:
	{
		//�ൿ ���� ���� �ʱ�ȭ
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

	//�÷��̾� ���ǵ�
	speed = 10.0f;

	//������ �ٲ���� üũ�ϴ� ����
	is_direction_change = false;

	//�Ѿ��� �ѹ��� �����ϱ� ���� ����
	bullet_flag = 0;

	hp_bar->SetHp(hp);

	radius = (width > height) ? width * 0.5f : height * 0.5f;

	//�浹ó���� ���� ������ �������� ����
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
	//�ִϸ��̼� ����Ʈ�� ���� �ִϸ��̼� ��� ����Ʈ
	motion_list = new AnimationManager;

	//�ִϸ��̼��� ������ ������ �ִϸ��̼� ��ü
	//�ִϸ��̼� ��� ����Ʈ�� �ֱ� ����
	for (int i = 0; i < ANIMATION_COUNT; ++i)
	{
		ani[i] = new Animation;
	}

	//LEFTSIDE(0~2)
	//=================================================================================================================
	//���� IDLE
	ImageManager::GetInstance()->AddFrameImage(
		"IDLE_L", TEXT("../BITMAP/PLAYER/PLAYER_IDLE_LEFT.bmp"), 560, 140, 4, 1, true, RGB(255, 0, 255));

	//���� WALK
	ImageManager::GetInstance()->AddFrameImage(
		"WALK_L", TEXT("../BITMAP/PLAYER/PLAYER_WALK_LEFT.bmp"), 2240, 140, 16, 1, true, RGB(255, 0, 255));

	//���� ATTACK
	ImageManager::GetInstance()->AddFrameImage(
		"ATTACK_L", TEXT("../BITMAP/PLAYER/PLAYER_ATTACK_LEFT.bmp"), 960, 140, 4, 1, true, RGB(255, 0, 255));
	//=================================================================================================================

	//RIGHTSIDE(3~5)
	//=================================================================================================================
	//������ IDLE
	ImageManager::GetInstance()->AddFrameImage(
		"IDLE_R", TEXT("../BITMAP/PLAYER/PLAYER_IDLE_RIGHT.bmp"), 560, 140, 4, 1, true, RGB(255, 0, 255));

	//������ WALK
	ImageManager::GetInstance()->AddFrameImage(
		"WALK_R", TEXT("../BITMAP/PLAYER/PLAYER_WALK_RIGHT.bmp"), 2240, 140, 16, 1, true, RGB(255, 0, 255));

	//������ ATTACK
	ImageManager::GetInstance()->AddFrameImage(
		"ATTACK_R", TEXT("../BITMAP/PLAYER/PLAYER_ATTACK_RIGHT.bmp"), 960, 140, 4, 1, true, RGB(255, 0, 255));
	//=================================================================================================================

	//LEFTSIDE(0~2)
	//=================================================================================================================
	//���� IDLE
	image = ImageManager::GetInstance()->FindImage("IDLE_L");
	assert(image != nullptr);
	ani[0]->Init(image, 0, 4, true);
	ani[0]->SetFPS(200);
	motion_list->AddMotion(ani[0]);

	//���� WALK
	image = ImageManager::GetInstance()->FindImage("WALK_L");
	assert(image != nullptr);
	ani[1]->Init(image, 0, 16, false);
	ani[1]->SetFPS(50);
	motion_list->AddMotion(ani[1]);

	//���� ATTACK
	image = ImageManager::GetInstance()->FindImage("ATTACK_L");
	assert(image != nullptr);
	ani[2]->Init(image, 0, 4, false);
	ani[2]->SetFPS(50);
	motion_list->AddMotion(ani[2]);
	//=================================================================================================================


	//RIGHTSIDE(3~5)
	//=================================================================================================================
	//������ IDLE
	image = ImageManager::GetInstance()->FindImage("IDLE_R");
	assert(image != nullptr);
	ani[3]->Init(image, 0, 4, true);
	ani[3]->SetFPS(200);
	motion_list->AddMotion(ani[3]);

	//������ WALK
	image = ImageManager::GetInstance()->FindImage("WALK_R");
	assert(image != nullptr);
	ani[4]->Init(image, 0, 16, false);
	ani[4]->SetFPS(50);
	motion_list->AddMotion(ani[4]);

	//������ ATTACK
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
	//������ �ٶ󺸴� ���
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

	//�������� �ٶ󺸴� ���
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
	//������ �ٶ󺸴� ���
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

	//�������� �ٶ󺸴� ���
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
	//�ش� �÷��̾� Hp ����
	hp_bar->SetHp(hp);

	switch (player_flag)
	{
		//�÷��̾� 1
	case 1:
	{
		//W(������ �ø�)
		if (KEYPRESS(0x57))
		{
			IncreaseAngle();
		}

		//S(������ ����)
		if (KEYPRESS(0x53))
		{
			DecreaseAngle();
		}

		//D(������ �̵�)
		if (KEYPRESS(0x44))
		{
			MoveRight();
		}

		//A(���� �̵�)
		else if (KEYPRESS(0x41))
		{
			MoveLeft();
		}

		//���ݸ��
		else if (KEYPRESS(VK_CONTROL))
		{
			Attack();
		}

		//�����
		else
		{
			Idle();
		}

	}
	break;

	//�÷��̾�2
	case 2:
	{
		//������ �ø�
		if (KEYPRESS(VK_UP))
		{
			IncreaseAngle();
		}

		//������ ����
		if (KEYPRESS(VK_DOWN))
		{
			DecreaseAngle();
		}

		//������ �̵�
		if (KEYPRESS(VK_RIGHT))
		{
			MoveRight();
		}

		//���� �̵�
		else if (KEYPRESS(VK_LEFT))
		{
			MoveLeft();
		}

		//���ݸ��
		else if (KEYPRESS(VK_SPACE))
		{
			Attack();
		}

		//�����
		else
		{
			Idle();
		}

	}
	break;

	default:
		break;
	}


	//���� �ִϸ��̼��� ���� ��� �Ѿ˻����� �� �ѹ��� �ϵ��� �ϴ� �κ�
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


	//�����ʿ��� ������ �ٶ󺸴� ���
	if (is_direction_change && (side == LookAtSide::LEFTSIDE))
	{
		if ((0.0f < angle) && (angle < (PI*0.5f)))
		{
			angle = PI - angle;
			is_direction_change = false;
		}
	}

	//���ʿ��� �������� �ٶ󺸴� ���
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


	//ȭ�� ������ ������ ���� ����
	//����
	if (position.x <= 100.0f)
	{
		position.x = 100.0f;
	}
	//������
	else if (position.x >= static_cast<float>(WORLD_WIDTH - 100))
	{
		position.x = static_cast<float>(WORLD_WIDTH - 100);
	}

	//Hp���� ��ġ�� ����ؼ� ����
	hp_bar->SetPos(GetPos());

	motion_list->FindMotion(state)->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
}

void Player::Render(HDC hdc, const TPoint* ptCam)
{
	//�浹ó�� ���� �߽���
	TPoint pt = { 0.0f, 0.0f };
	//�÷��̾ �׸� ��ġ
	TPoint ptAni = { 0.0f, 0.0f };
	//ī�޶� ��ġ
	TPoint pC = { 0.0f, 0.0f };

	//ī�޶��� ��ǥ�� �ִ� ���
	//�÷��̾���� ī�޶��� ������� ��ġ�� �÷��̾ �׷��� ��
	if (ptCam)
	{
		//�������� �ȴ� ����� ���� �� ����
		if (state == State::ATTACK_L)
		{
			//�÷��̾ �׸� ��ġ
			ptAni = { (GetPos().x - ptCam->x - radius - 100.0f),
				(GetPos().y - ptCam->y - GetSize().height*0.5f) };
		}

		//�� ���� ��� ����� �� �׸� ��ġ
		else
		{
			//�÷��̾ �׸� ��ġ
			ptAni = { (GetPos().x - ptCam->x - radius), (GetPos().y - ptCam->y - radius) };
		}

		//�浹ó�� ���� �߽���
		pt = { (GetPos().x - ptCam->x), (GetPos().y - ptCam->y) };
		//ī�޶��� ��ġ
		pC = { ptCam->x, ptCam->y };
	}

	else
	{
		//�÷��̾ �׸� ��ġ
		ptAni = { (GetPos().x - radius), (GetPos().y - radius) };
		//ī�޶��� ��ġ
		pt = { (GetPos().x), (GetPos().y) };
	}

	//�浹��
	EllipseMakeCenter(hdc, static_cast<int>(pt.x), static_cast<int>(pt.y), static_cast<int>(circle.r) * 2, static_cast<int>(circle.r) * 2);

	//�˵� ��
	{
		HPEN pen = nullptr;
		HPEN old_pen = nullptr;

		switch (player_flag)
		{
		case 1:
		{
			//���� �� ����
			pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
			//���� ���� �Ӽ��� ������ �� ���� ���� �� ���� �� �Ӽ� ����
			old_pen = (HPEN)SelectObject(hdc, pen);
		}
		break;
		case 2:
		{
			//�Ķ� �� ����
			pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
			//���� ���� �Ӽ��� ������ �� ���� ���� �� ���� �� �Ӽ� ����
			old_pen = (HPEN)SelectObject(hdc, pen);

		}
		break;
		default:
			break;
		}

		//�߻� �˵�
		LineMake(hdc, static_cast<int>(pt.x), static_cast<int>(pt.y),
			static_cast<int>(end.x - pC.x), static_cast<int>(end.y - pC.y));


		//���� �� ����
		DeleteObject(pen);


		//�� �Ӽ� ���
		SelectObject(hdc, old_pen);
	}

	//�÷��̾� �ִϸ��̼�
	image->AniRender(hdc, static_cast<int>(ptAni.x), static_cast<int>(ptAni.y), motion_list->FindMotion(state));

	//�÷��̾� ü�� ��
	hp_bar->Render(hdc, ptCam);
}

void Player::CreateBullet()
{
	//�� ĳ����
	ObjectBase* object = new Bullet("Player" + std::to_string(player_flag) + "_Bullet", end.x, end.y, 40.0f, 40.0f, player_flag);
	object->SetDestroy(false);

	//�ٿ� ĳ����
	Bullet* bullet = dynamic_cast<Bullet*>(object);
	assert(bullet != nullptr);
	bullet->SetAngle(angle);

	//������Ʈ �Ŵ����� �߰�
	ObjectManager::GetInstance()->AddObject(object, player_flag);
}
