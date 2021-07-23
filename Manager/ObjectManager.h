#pragma once

#include "Utility/SingletonBase.h"

//Ŭ���� ���漱��
class BackGround;
class Player;
class ObjectBase;

//�÷��̾�1 �Ѿ� ����Ʈ
using P1_BulletList = std::list<ObjectBase*>;
using P1_BulletList_it = std::list<ObjectBase*>::iterator;

//�÷��̾�2 �Ѿ� ����Ʈ
using P2_BulletList = std::list<ObjectBase*>;
using P2_BulletList_it = std::list<ObjectBase*>::iterator;

class ObjectManager : public SingletonBase<ObjectManager>
{
private:
    
	//������ ������ �����ϴ� ����
	int turn_flag;

	//��� ��ü
	BackGround*  background;
	
	//�÷��̾�1 ��ü
	Player *player1;
	//�÷��̾�1 �Ѿ� ����Ʈ
	P1_BulletList p1_Bullet_list;

	//�÷��̾�2 ��ü
	Player *player2;
	//�÷��̾�2 �Ѿ� ����Ʈ
	P2_BulletList p2_Bullet_list;

public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& other);
	ObjectManager& operator=(const ObjectManager& other);

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

    bool AddObject(ObjectBase* obj, const int& flag);
};

