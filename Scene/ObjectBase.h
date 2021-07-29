#pragma once

//렌더링될 모든 오브젝트에 상속하여 사용
class ObjectBase
{
protected:

	std::string tag;

	//오브젝트의 이동속도
	float speed;

	//오브젝트가 그려질 사각형 범위
	TRect		rect;

	//오브젝트의 사이즈
	TSize		size;

	//오브젝트의 위치
	TPoint		position;

	//오브젝트 충돌처리 원
	TCircle     circle;

	bool		is_collision;
	bool		is_destroy;

public:
	ObjectBase() = delete;
	~ObjectBase() = default;

	//생성자 오버로딩
	explicit ObjectBase(const float& width, const float& height);
	explicit ObjectBase(const std::string& tag, const float width, const float height);
	explicit ObjectBase(const std::string& tag, const float x, const float y, const float width, const float height);
	explicit ObjectBase(const ObjectBase& obj);

	//연산자 오버로딩
	ObjectBase& operator=(const ObjectBase& obj);

	const std::string& GetTag() const { return tag; }

	const TRect& GetRect() const { return rect; }
	void SetRect(const TRect& rc) { rect = rc; }

	const TPoint& GetPos() const { return position; }
	TPoint* GetPosPt() { return &position; }
	void SetPos(const TPoint& pt);
	void SetPos(const float x, const float y);

	void SetSize(const float width, const float height);
	TSize GetSize() const;

	TCircle GetCircle() const { return circle; }
	void SetCircle(const TCircle& _circle) { circle = _circle; }

	//충돌 여부 확인
	bool IsCollision(const ObjectBase* target);

	bool GetCollision() const { return is_collision; }
	void SetCollision(bool flag) { is_collision = flag; }

	//오브젝트 파괴 관련
	bool GetDestroy() const { return is_destroy; }
	void SetDestroy(bool flag) { is_destroy = flag; }

	//순수 가상 함수
	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc, const TPoint* ptCam = nullptr) = 0;
};

