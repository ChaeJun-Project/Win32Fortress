#pragma once

class Animation;

// 이미지 정보를 메모리에 Load해서 사용하기 위한 클래스
class Image
{
private:
	//어떤 방식으로 메모리로 Load할 것이냐에 대한 타입
	enum ImageLoadType
	{
		LOAD_RESOURCE,			// 윈도우 리소스에서 로드
		LOAD_FILE,				// 외부 파일에서 로드
		LOAD_EMPTY,				// 빈 이미지 객체로 생성 
		LOAD_END,
	};

	//로드한 이미지의 정보를 분리해서 관리하기 위한 구조체
	struct ImageInfo
	{
		DWORD		resID;		// 리소에서 로드했을 경우 사용할 리소스ID
		HDC			hMemDC;		// 비트맵 이미지가 로드될 메모리 DC
		HBITMAP		hBit;		// 비트맵 이미지의 핸들
		HBITMAP		hOldBit;	// 백업용 비트맵 이미지의 핸들
		int			width;		// 이미지 사이즈 X
		int			height;		// 이미지 사이즈 Y
		float		x;			// 이미지 랜더링 시작 위치	
		float		y;
		int			current_frameX; // 프레임이미지에서 현재 프레임의 위치
		int			current_frameY;
		int			max_frameX;	// X쪽 최대 프레임 수
		int			max_frameY;	// Y쪽 최대 프레임 수
		int			frame_width;	// 프레임 이미지 하나의 사이즈
		int			frame_height;

		BYTE		load_type;	// 로드 타입	

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

	//Alpha Blend용
	ImageInfo*		blend_info;
	BLENDFUNCTION	blend_func;

public:
	Image();
	~Image();

	//빈 이미지 객체 초기화
	bool Init(int _width, int _height);

	//파일로 부터 초기화
	bool Init(const TCHAR* _fileName, const int _width, const int _height,
		const bool _trans = false, const COLORREF _transColor = false);
	//파일로 부터 초기화
	bool Init(const TCHAR* _fileName, const float x, const float y, const int _width, const int _height,
		const bool _trans = false, const COLORREF _transColor = false);

	//파일로부터 초기화 - 스프라이트 이미지
	bool Init(const TCHAR* _fileName, const int _width, const int _height,
		const int frameX, const int frameY, const bool _trans = false, const COLORREF _transColor = false);
	//파일로부터 초기화 - 스프라이트 이미지
	bool Init(const TCHAR* _fileName, const float x, const float y, const int _width, const int _height,
		const int frameX, const int frameY, const bool _trans = false, const COLORREF _transColor = false);


	void Release();

	///////////////////////////////////////////////////////////
	//기본 랜더 함수
	void Render(const HDC hdc);
	void Render(const HDC hdc, const int destX, const int destY);
	void Render(const HDC hdc, const int destX, const int destY,
		const int srcX, const int srcY, const int srcWidth, const int srcHeight);

	//루프 랜더 함수
	void LoopRender(const HDC hdc, const RECT* drawArea,
		int offSetX, int offSetY);

	//프레임 랜더 함수
	void FrameRender(const HDC hdc, const int destX, const int destY);
	void FrameRender(const HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	//애니 랜더 함수
	void AniRender(const HDC hdc, const int destX, const int destY, const Animation* ani);

	//알파 랜더 함수
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

