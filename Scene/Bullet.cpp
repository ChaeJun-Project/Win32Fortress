#include "Win32Fortress.h"

Bullet::Bullet(const std::string & tag, const float x, const float y, const float width, const float height, const int& flag)
	: ObjectBase(tag, x, y, width, height)
{
	//�ִϸ��̼� ����Ʈ�� ���� �ִϸ��̼� ��� ����Ʈ
	motion_list = new AnimationManager;

	//�ִϸ��̼��� ������ ������ �ִϸ��̼� ��ü
	//�ִϸ��̼� ��� ����Ʈ�� �ֱ� ����
	ani= new Animation;

	bullet_tag = tag;

	switch (flag)
	{
	case 1:
	{
		//�÷��̾�1 �Ѿ��� �̹��� �Ŵ����� �߰�
		ImageManager::GetInstance()->AddFrameImage(
			bullet_tag, TEXT("../BITMAP/PLAYER/Player1BulletImage.bmp"), 80, 40, 2, 1, true, RGB(255, 0, 255));
	}
	break;

	case 2:
	{
		//�÷��̾�2 �̹��� �Ŵ����� �߰�
		ImageManager::GetInstance()->AddFrameImage(
			bullet_tag, TEXT("../BITMAP/PLAYER/Player2BulletImage.bmp"), 80, 40, 2, 1, true, RGB(255, 0, 255));
	}
	break;

	default:
		break;
	}

	//�ִϸ��̼� ��Ǹ���Ʈ�� �ִϸ��̼� ���� �߰�
	image = ImageManager::GetInstance()->FindImage(bullet_tag);
	assert(image != nullptr);
	ani->Init(image, 0, 2, false);
	ani->SetFPS(50);
	motion_list->AddMotion(ani);

	motion_list->Play(0);
	
	//�Ѿ� ���ǵ�
	speed = 20.0f;

	//�߷�
	gravity = 30.0f;

	//�߻�ü�� �̵� ��� �ð�
	elapsed_time = 0.0f;

	//�Ѿ��� ���ݷ�
	damage = 20;

	angle = 0.f;
	radius = (width > height) ? width * 0.5f : height * 0.5f;

	//�浹ó���� ���� ������ �������� ����
	circle.r = radius;
}

Bullet::Bullet(const Bullet & other)
	: ObjectBase(other)
{
	angle = other.angle;
	radius = other.radius;
	speed = other.speed;
}

Bullet::~Bullet()
{
	Release();
}

Bullet & Bullet::operator=(const Bullet & other)
{
	angle = other.angle;
	radius = other.radius;
	speed = other.speed;

	return *this;
}

bool Bullet::Init()
{
	return true;
}

void Bullet::Release()
{
	SAFE_DELETE(ani);
	SAFE_DELETE(motion_list);
}

void Bullet::Update()
{
	image = ImageManager::GetInstance()->FindImage(bullet_tag);

	elapsed_time += TimeManager::GetInstance()->GetElapsedTime();

	//������ �
	position.x = position.x + (cosf(angle) * speed);
	position.y = position.y + (-(sinf(angle)) * speed) + (0.5f* gravity * elapsed_time);

	circle.pt = GetPos();

	//ȭ������� ���� ���
	//Y��
	if ((static_cast<float>(WORLD_HEIGHT)<=position.y)||(position.y<=0.f))
	{
	    SetDestroy(true);
	}
	//X��
	else if((static_cast<float>(WORLD_WIDTH)<= position.x)|| (position.x <= 0.f))
	{
		SetDestroy(true);
	}

	motion_list->FindMotion(0)->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
}

void Bullet::Render(HDC hdc, const TPoint* ptCam)
{
	//�浹�ڽ��� �׸� ��ġ
	TPoint pt;
	//�Ѿ� �ִϸ��̼��� �׸� ��ġ
	TPoint pt_Ani;
	//ī�޶� ��ġ
	TPoint pC = { 0.f, 0.f };
	if (ptCam)
	{
		pt_Ani = { (GetPos().x - ptCam->x - radius), (GetPos().y - ptCam->y - radius) };
		pt = { (GetPos().x - ptCam->x), (GetPos().y - ptCam->y) };
		pC = { ptCam->x, ptCam->y };
	}
	else
	{
		pt_Ani = { (GetPos().x - radius), (GetPos().y - radius) };
		pt = { (GetPos().x), (GetPos().y) };
	}

	image->AniRender(hdc, static_cast<int>(pt_Ani.x), static_cast<int>(pt_Ani.y), motion_list->FindMotion(0));
}
