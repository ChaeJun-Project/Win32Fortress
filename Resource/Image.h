#pragma once

class Animation;

// �̹��� ������ �޸𸮿� Load�ؼ� ����ϱ� ���� Ŭ����
class Image
{
private:
	//� ������� �޸𸮷� Load�� ���̳Ŀ� ���� Ÿ��
	enum ImageLoadType
	{
		LOAD_RESOURCE,			// ������ ���ҽ����� �ε�
		LOAD_FILE,				// �ܺ� ���Ͽ��� �ε�
		LOAD_EMPTY,				// �� �̹��� ��ü�� ���� 
		LOAD_END,
	};

	//�ε��� �̹����� ������ �и��ؼ� �����ϱ� ���� ����ü
	struct ImageInfo
	{
		DWORD		resID;		// ���ҿ��� �ε����� ��� ����� ���ҽ�ID
		HDC			hMemDC;		// ��Ʈ�� �̹����� �ε�� �޸� DC
		HBITMAP		hBit;		// ��Ʈ�� �̹����� �ڵ�
		HBITMAP		hOldBit;	// ����� ��Ʈ�� �̹����� �ڵ�
		int			width;		// �̹��� ������ X
		int			height;		// �̹��� ������ Y
		float		x;			// �̹��� ������ ���� ��ġ	
		float		y;
		int			current_frameX; // �������̹������� ���� �������� ��ġ
		int			current_frameY;
		int			max_frameX;	// X�� �ִ� ������ ��
		int			max_frameY;	// Y�� �ִ� ������ ��
		int			frame_width;	// ������ �̹��� �ϳ��� ������
		int			frame_height;

		BYTE		load_type;	// �ε� Ÿ��	

		ImageInfo()
		{
			resID	= 0;
			hMemDC	= NULL;
			hBit	= NULL;
			hOldBit = NULL;
			width	= 0;
			height	= 0;
			x		= 0.f;
			y		= 0.f;
			current_frameX = 0;
			current_frameY = 0;
			max_frameX = 0;	//
			max_frameY = 0;	//
			frame_width = 0;	//
			frame_height = 0;

			load_type = LOAD_RESOURCE;
		}
	};

	ImageInfo*		image_info;
	TCHAR*			file_name;
	bool			trans;
	COLORREF		trans_color;

	//Alpha Blend��
	ImageInfo*		blend_info;
	BLENDFUNCTION	blend_func;

public:
	Image();
	~Image();

	//�� �̹��� ��ü �ʱ�ȭ
	bool Init(int _width, int _height);

	//���Ϸ� ���� �ʱ�ȭ
	bool Init(const TCHAR* _fileName, const int _width, const int _height,
		const bool _trans = false, const COLORREF _transColor = false);
	//���Ϸ� ���� �ʱ�ȭ
	bool Init(const TCHAR* _fileName, const float x, const float y, const int _width, const int _height,
		const bool _trans = false, const COLORREF _transColor = false);

	//���Ϸκ��� �ʱ�ȭ - ��������Ʈ �̹���
	bool Init(const TCHAR* _fileName, const int _width, const int _height,
		const int frameX, const int frameY, const bool _trans = false, const COLORREF _transColor = false);
	//���Ϸκ��� �ʱ�ȭ - ��������Ʈ �̹���
	bool Init(const TCHAR* _fileName, const float x, const float y, const int _width, const int _height,
		const int frameX, const int frameY, const bool _trans = false, const COLORREF _transColor = false);


	void Release();

	///////////////////////////////////////////////////////////
	//�⺻ ���� �Լ�
	void Render(const HDC hdc);
	void Render(const HDC hdc, const int destX, const int destY);
	void Render(const HDC hdc, const int destX, const int destY,
		const int srcX, const int srcY, const int srcWidth, const int srcHeight);

	//���� ���� �Լ�
	void LoopRender(const HDC hdc, const RECT* drawArea,
		int offSetX, int offSetY);

	//������ ���� �Լ�
	void FrameRender(const HDC hdc, const int destX, const int destY);
	void FrameRender(const HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	//�ִ� ���� �Լ�
	void AniRender(const HDC hdc, const int destX, const int destY, const Animation* ani);

	//���� ���� �Լ�
	void AlphaRender(const HDC hdc, BYTE alpha);
	void AlphaRender(const HDC hdc, const int destX, const int destY, BYTE alpha);
	void AlphaRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha);
	//////////////////////////////////////////////////////////////

	void SetTransColor(bool _trans, COLORREF _transColor);

	///////////////////////////////////////////////////////////////

	int GetSizeWidth() const { return image_info->width; }
	int GetSizeHeight() const { return image_info->height; }

	int GetMaxFrameX() const { return image_info->max_frameX; }
	int GetMaxFrameY() const { return image_info->max_frameY; }

	int GetCurrentFrameX() const { return image_info->current_frameX; }
	int GetCurrentFrameY() const { return image_info->current_frameY; }

	int GetFrameWidth() const { return image_info->frame_width; }
	int GetFrameHeight() const { return image_info->frame_height; }

	inline HDC GetMemDC() const { return image_info->hMemDC; }
};

