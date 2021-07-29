#include "Win32Fortress.h"

ObjectManager::ObjectManager()
{
	TRect rcClient = { 0, 0, static_cast<float>(GAME_WIDTH), static_cast<float>(GAME_HEIGHT) };
	TRect rcWorld = { 0, 0, static_cast<float>(WORLD_WIDTH), static_cast<float>(WORLD_HEIGHT) };

	//플레이어 1부터 시작
	turn_flag = 1;

	//배경
	background = new BackGround(rcWorld.right, rcWorld.bottom);

	//카메라 싱글톤 생성
	Camera<TPoint, TRect>::Create();
	Camera<TPoint, TRect>::GetInstance()->SetWorld(rcWorld);
	Camera<TPoint, TRect>::GetInstance()->SetClient(rcClient);

	//플레이어 1 객체
	player1 = new Player("Player1", 100.f, static_cast<float>(WORLD_HEIGHT - 180), 140.f, 140.f, 1);
	//플레이어 2 객체
	player2 = new Player("Player2", static_cast<float>(WORLD_WIDTH - 100), static_cast<float>(WORLD_HEIGHT - 180), 140.f, 140.f, 2);

	Init();
}

ObjectManager::~ObjectManager()
{
	Release();
}

ObjectManager::ObjectManager(const ObjectManager& other)
{
	background = other.background;
	player1 = other.player1;
	player2 = other.player2;

	for (auto& obj : other.p1_Bullet_list)
	{
		p1_Bullet_list.push_back(obj);
	}

	for (auto& obj : other.p2_Bullet_list)
	{
		p2_Bullet_list.push_back(obj);
	}
}

ObjectManager& ObjectManager::operator=(const ObjectManager& other)
{
	background = other.background;
	player1 = other.player1;
	player2 = other.player2;

	for (auto& obj : other.p1_Bullet_list)
	{
		p1_Bullet_list.push_back(obj);
	}

	for (auto& obj : other.p2_Bullet_list)
	{
		p2_Bullet_list.push_back(obj);
	}

	return *this;
}

bool ObjectManager::Init()
{
	background->Init();
	background->SetPos(static_cast<float>(WORLD_WIDTH), static_cast<float>(WORLD_HEIGHT));

	Camera<TPoint, TRect>::GetInstance()->SetTargetPos(player1->GetPosPt());

	return true;
}

void ObjectManager::Release()
{
	SAFE_DELETE(background);
	Camera<TPoint, TRect>::GetInstance()->Delete();
	SAFE_DELETE(player1);
	SAFE_DELETE(player2);

	//플레이어1 총알 리스트
	for (auto& obj : p1_Bullet_list)
	{
		if (obj)
		{
			obj->Release(); //오브젝트 내부의 메모리 해제
			SAFE_DELETE(obj); //오브젝트 메모리 해제
		}
	}
	p1_Bullet_list.clear(); //리스트 초기화

	//플레이어2 총알 리스트
	for (auto& obj : p2_Bullet_list)
	{
		if (obj)
		{
			obj->Release(); //오브젝트 내부의 메모리 해제
			SAFE_DELETE(obj); //오브젝트 메모리 해제
		}
	}
	p2_Bullet_list.clear(); //리스트 초기화
}

void ObjectManager::Update()
{
	Camera<TPoint, TRect>::GetInstance()->Update();

	switch (turn_flag)
	{
	case 1:
	{
		Camera<TPoint, TRect>::GetInstance()->SetTargetPos(player1->GetPosPt());
		player1->Update();

		std::list<ObjectBase*>::iterator p1_BulletList_it;
		p1_BulletList_it = p1_Bullet_list.begin();

		for (; p1_BulletList_it != p1_Bullet_list.end(); ++p1_BulletList_it)
		{
			//총알로 카메라값 고정
			Camera<TPoint, TRect>::GetInstance()->SetTargetPos((*p1_BulletList_it)->GetPosPt());
			(*p1_BulletList_it)->Update();

			//적 플레이어와 총알이 충돌했을 경우(충돌원으로 구현)
			if (CollisionTCircleAndTCircle(&player2->GetCircle(), &(*p1_BulletList_it)->GetCircle()))
			{
				//플레이어2 체력감소
				player2->SetPlayerHp(dynamic_cast<Bullet*>(*p1_BulletList_it)->GetBulletDamage());
				(*p1_BulletList_it)->SetDestroy(true);
			}

			//총알의 삭제여부가 true일 경우 턴을 넘김(적과 충돌하거나 화면밖으로 나갈 경우)
			if ((*p1_BulletList_it)->GetDestroy())
			{
				turn_flag = 2;
				SAFE_DELETE(*p1_BulletList_it);
				p1_BulletList_it = p1_Bullet_list.erase(p1_BulletList_it); //해당 포탄 삭제
				if (p1_BulletList_it == p1_Bullet_list.end())
				{
					break;
				}
			}
		}
	}
	break;

	case 2:
	{
		Camera<TPoint, TRect>::GetInstance()->SetTargetPos(player2->GetPosPt());
		player2->Update();

		std::list<ObjectBase*>::iterator p2_BulletList_it;
		p2_BulletList_it = p2_Bullet_list.begin();

		for (; p2_BulletList_it != p2_Bullet_list.end(); ++p2_BulletList_it)
		{
			//총알로 카메라값 고정
			Camera<TPoint, TRect>::GetInstance()->SetTargetPos((*p2_BulletList_it)->GetPosPt());
			(*p2_BulletList_it)->Update();

			//적 플레이어와 총알이 충돌했을 경우(충돌원으로 구현)
			if (CollisionTCircleAndTCircle(&player1->GetCircle(), &(*p2_BulletList_it)->GetCircle()))
			{
				//플레이어1 체력감소
				player1->SetPlayerHp(dynamic_cast<Bullet*>(*p2_BulletList_it)->GetBulletDamage());
				(*p2_BulletList_it)->SetDestroy(true);
			}

			//총알의 삭제여부가 true일 경우 턴을 넘김(적과 충돌하거나 화면밖으로 나갈 경우)
			if ((*p2_BulletList_it)->GetDestroy())
			{
				turn_flag = 1;
				SAFE_DELETE(*p2_BulletList_it);
				p2_BulletList_it = p2_Bullet_list.erase(p2_BulletList_it); //해당 포탄 삭제
				if (p2_BulletList_it == p2_Bullet_list.end())
				{
					break;
				}
			}
		}
	}
	break;
	}
}

void ObjectManager::Render(HDC hdc)
{
	//배경 렌더
	background->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());

	//플레이어1 렌더
	player1->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());

	//플레이어2 렌더
	player2->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());


	for (auto& obj : p1_Bullet_list)
	{
		if (obj->GetCollision())
			continue;

		obj->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());
	}

	for (auto& obj : p2_Bullet_list)
	{
		if (obj->GetCollision())
			continue;

		obj->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());
	}
}

bool ObjectManager::AddObject(ObjectBase* obj, const int& flag)
{
	if (obj == nullptr)
		return false;

	//플레이어1 총알일 경우
	switch (flag)
	{
	case 1:
	{
		p1_Bullet_list.push_back(obj);
	}
	break;

	case 2:
	{
		p2_Bullet_list.push_back(obj);
	}
	break;
	}
	return true;
}

