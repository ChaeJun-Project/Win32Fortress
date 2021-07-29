#pragma once

//�������� ��� ������Ʈ�� ����Ͽ� ���
class ObjectBase
{
protected:

	std::string tag;

	//������Ʈ�� �̵��ӵ�
	float speed;

	//������Ʈ�� �׷��� �簢�� ����
	TRect		rect;

	//������Ʈ�� ������
	TSize		size;

	//������Ʈ�� ��ġ
	TPoint		position;

	//������Ʈ �浹ó�� ��
	TCircle     circle;

	bool		is_collision;
	bool		is_destroy;

public:
	ObjectBase() = delete;
	~ObjectBase() = default;

	//������ �����ε�
	explicit ObjectBase(const float& width, const float& height);
	explicit ObjectBase(const std::string& tag, const float width, const float height);
	explicit ObjectBase(const std::string& tag, const float x, const float y, const float width, const float height);
	explicit ObjectBase(const ObjectBase& obj);

	//������ �����ε�
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

	//�浹 ���� Ȯ��
	bool IsCollision(const ObjectBase* target);

	bool GetCollision() const { return is_collision; }
	void SetCollision(bool flag) { is_collision = flag; }

	//������Ʈ �ı� ����
	bool GetDestroy() const { return is_destroy; }
	void SetDestroy(bool flag) { is_destroy = flag; }

	//���� ���� �Լ�
	virtual bool Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc, const TPoint* ptCam = nullptr) = 0;
};

