#include "Win32Fortress.h"

Bullet::Bullet(const std::string & tag, const float x, const float y, const float width, const float height, const int& flag)
	: ObjectBase(tag, x, y, width, height)
{
	//애니메이션 리스트를 넣을 애니메이션 모션 리스트
	motion_list = new AnimationManager;

	//애니메이션의 정보를 저장할 애니메이션 객체
	//애니메이션 모션 리스트에 넣기 위함
	ani= new Animation;

	bullet_tag = tag;

	switch (flag)
	{
	case 1:
	{
		//플레이어1 총알을 이미지 매니저에 추가
		ImageManager::GetInstance()->AddFrameImage(
			bullet_tag, TEXT("../BITMAP/PLAYER/Player1BulletImage.bmp"), 80, 40, 2, 1, true, RGB(255, 0, 255));
	}
	break;

	case 2:
	{
		//플레이어2 이미지 매니저에 추가
		ImageManager::GetInstance()->AddFrameImage(
			bullet_tag, TEXT("../BITMAP/PLAYER/Player2BulletImage.bmp"), 80, 40, 2, 1, true, RGB(255, 0, 255));
	}
	break;

	default:
		break;
	}

	//애니메이션 모션리스트에 애니메이션 정보 추가
	image = ImageManager::GetInstance()->FindImage(bullet_tag);
	assert(image != nullptr);
	ani->Init(image, 0, 2, false);
	ani->SetFPS(50);
	motion_list->AddMotion(ani);

	motion_list->Play(0);
	
	//총알 스피드
	speed = 20.0f;

	//중력
	gravity = 30.0f;

	//발사체의 이동 경과 시간
	elapsed_time = 0.0f;

	//총알의 공격력
	damage = 20;

	angle = 0.f;
	radius = (width > height) ? width * 0.5f : height * 0.5f;

	//충돌처리를 위한 변수에 반지름값 저장
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

	//포물선 운동
	position.x = position.x + (cosf(angle) * speed);
	position.y = position.y + (-(sinf(angle)) * speed) + (0.5f* gravity * elapsed_time);

	circle.pt = GetPos();

	//화면밖으로 나갈 경우
	//Y축
	if ((static_cast<float>(WORLD_HEIGHT)<=position.y)||(position.y<=0.f))
	{
	    SetDestroy(true);
	}
	//X축
	else if((static_cast<float>(WORLD_WIDTH)<= position.x)|| (position.x <= 0.f))
	{
		SetDestroy(true);
	}

	motion_list->FindMotion(0)->FrameUpdate(TimeManager::GetInstance()->GetElapsedTime());
}

void Bullet::Render(HDC hdc, const TPoint* ptCam)
{
	//충돌박스를 그릴 위치
	TPoint pt;
	//총알 애니메이션을 그릴 위치
	TPoint pt_Ani;
	//카메라 위치
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
