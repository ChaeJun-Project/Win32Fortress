#include "Win32Fortress.h"

ObjectManager::ObjectManager()
{
	TRect rcClient = { 0, 0, static_cast<float>(GAME_WIDTH), static_cast<float>(GAME_HEIGHT) };
	TRect rcWorld = { 0, 0, static_cast<float>(WORLD_WIDTH), static_cast<float>(WORLD_HEIGHT) };

	//�÷��̾� 1���� ����
	turn_flag = 1;

	//���
	background = new BackGround(rcWorld.right, rcWorld.bottom);

	//ī�޶� �̱��� ����
	Camera<TPoint, TRect>::Create();
	Camera<TPoint, TRect>::GetInstance()->SetWorld(rcWorld);
	Camera<TPoint, TRect>::GetInstance()->SetClient(rcClient);

	//�÷��̾� 1 ��ü
	player1 = new Player("Player1", 100.f, static_cast<float>(WORLD_HEIGHT - 180), 140.f, 140.f, 1);
	//�÷��̾� 2 ��ü
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

	//�÷��̾�1 �Ѿ� ����Ʈ
	for (auto& obj : p1_Bullet_list)
	{
		if (obj)
		{
			obj->Release(); //������Ʈ ������ �޸� ����
			SAFE_DELETE(obj); //������Ʈ �޸� ����
		}
	}
	p1_Bullet_list.clear(); //����Ʈ �ʱ�ȭ

	//�÷��̾�2 �Ѿ� ����Ʈ
	for (auto& obj : p2_Bullet_list)
	{
		if (obj)
		{
			obj->Release(); //������Ʈ ������ �޸� ����
			SAFE_DELETE(obj); //������Ʈ �޸� ����
		}
	}
	p2_Bullet_list.clear(); //����Ʈ �ʱ�ȭ
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
			//�Ѿ˷� ī�޶� ����
			Camera<TPoint, TRect>::GetInstance()->SetTargetPos((*p1_BulletList_it)->GetPosPt());
			(*p1_BulletList_it)->Update();

			//�� �÷��̾�� �Ѿ��� �浹���� ���(�浹������ ����)
			if (CollisionTCircleAndTCircle(&player2->GetCircle(), &(*p1_BulletList_it)->GetCircle()))
			{
				//�÷��̾�2 ü�°���
				player2->SetPlayerHp(dynamic_cast<Bullet*>(*p1_BulletList_it)->GetBulletDamage());
				(*p1_BulletList_it)->SetDestroy(true);
			}

			//�Ѿ��� �������ΰ� true�� ��� ���� �ѱ�(���� �浹�ϰų� ȭ������� ���� ���)
			if ((*p1_BulletList_it)->GetDestroy())
			{
				turn_flag = 2;
				SAFE_DELETE(*p1_BulletList_it);
				p1_BulletList_it = p1_Bullet_list.erase(p1_BulletList_it); //�ش� ��ź ����
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
			//�Ѿ˷� ī�޶� ����
			Camera<TPoint, TRect>::GetInstance()->SetTargetPos((*p2_BulletList_it)->GetPosPt());
			(*p2_BulletList_it)->Update();

			//�� �÷��̾�� �Ѿ��� �浹���� ���(�浹������ ����)
			if (CollisionTCircleAndTCircle(&player1->GetCircle(), &(*p2_BulletList_it)->GetCircle()))
			{
				//�÷��̾�1 ü�°���
				player1->SetPlayerHp(dynamic_cast<Bullet*>(*p2_BulletList_it)->GetBulletDamage());
				(*p2_BulletList_it)->SetDestroy(true);
			}

			//�Ѿ��� �������ΰ� true�� ��� ���� �ѱ�(���� �浹�ϰų� ȭ������� ���� ���)
			if ((*p2_BulletList_it)->GetDestroy())
			{
				turn_flag = 1;
				SAFE_DELETE(*p2_BulletList_it);
				p2_BulletList_it = p2_Bullet_list.erase(p2_BulletList_it); //�ش� ��ź ����
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
	//��� ����
	background->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());

	//�÷��̾�1 ����
	player1->Render(hdc, Camera<TPoint, TRect>::GetInstance()->GetCameraPos());

	//�÷��̾�2 ����
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

	//�÷��̾�1 �Ѿ��� ���
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

