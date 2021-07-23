#pragma once

struct TSize;

class ObjectBase
{
protected:

	std::string tag;

	//오브젝트의 이동속도
	float speed;

	TRect		rect;
	TSize		size;

	TPoint		position;

	TCircle     circle;

	bool		is_collision;
	bool		is_destroy;

public:
	ObjectBase() = delete;
	~ObjectBase() = default;

	//생성자 오버로딩
	ObjectBase(const float& width, const float& height);
	ObjectBase(const std::string& tag, const float width, const float height);
	ObjectBase(const std::string& tag, const float x, const float y, const float width, const float height);
	ObjectBase(const ObjectBase& obj);

	ObjectBase& operator=(const ObjectBase& obj);

	const std::string& GetTag() const { return tag; }

	//rect Set,Get 함수
	const TRect& GetRect() const { return rect; }
	void SetRect(const TRect& rc) { rect = rc; }

	//position Set,Get 함수
	const TPoint& GetPos() const { return position; }
	TPoint* GetPosPt() { return &position; }
	void SetPos(const TPoint& pt);
	void SetPos(const float x, const float y);

	//size Set,Get 함수
	void SetSize(const float width, const float height);
	TSize GetSize() const;

	//circle Set,Get 함수
	TCircle GetCircle() const { return circle; }
	void SetCircle(const TCircle& _circle) { circle = _circle; }

	bool GetCollision() const { return is_collision; }
	void SetCollision(bool flag) { is_collision = flag; }

	bool GetDestroy() const { return is_destroy; }
	void SetDestroy(bool flag) { is_destroy = flag; }

	bool IsCollision(const ObjectBase* target);


	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc, const TPoint* ptCam = nullptr) = 0;
};

