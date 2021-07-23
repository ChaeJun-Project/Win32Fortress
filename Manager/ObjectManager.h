#pragma once

#include "Utility/SingletonBase.h"

//클래스 전방선언
class BackGround;
class Player;
class ObjectBase;

//플레이어1 총알 리스트
using P1_BulletList = std::list<ObjectBase*>;
using P1_BulletList_it = std::list<ObjectBase*>::iterator;

//플레이어2 총알 리스트
using P2_BulletList = std::list<ObjectBase*>;
using P2_BulletList_it = std::list<ObjectBase*>::iterator;

class ObjectManager : public SingletonBase<ObjectManager>
{
private:
    
	//누구의 턴인지 결정하는 변수
	int turn_flag;

	//배경 객체
	BackGround*  background;
	
	//플레이어1 객체
	Player *player1;
	//플레이어1 총알 리스트
	P1_BulletList p1_Bullet_list;

	//플레이어2 객체
	Player *player2;
	//플레이어2 총알 리스트
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

