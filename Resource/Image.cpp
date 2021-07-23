#include "Win32Fortress.h"

#pragma comment(lib, "msimg32.lib")

Image::Image()
	: image_info(nullptr), file_name(nullptr),
	trans(false), trans_color(RGB(0, 0, 0)), blend_info(nullptr)
{
}

Image::~Image()
{
}

//해당 사이즈의 빈 비트맵 정보를 가지고 있는 이미지를 생성하기 위한 초기화 
bool Image::Init(const int _width, const int _height)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_EMPTY;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc);
	image_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit);
	image_info->width = _width;
	image_info->height = _height;

	file_name = nullptr;

	trans = false;
	trans_color = RGB(0, 0, 0);

	if (image_info->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

//해당 사이즈의 이미지를 파일에서 로드해서 관리하는 용도의 초기화
bool Image::Init(const TCHAR* _file_name, const int _width, const int _height,
	const bool _trans, const COLORREF _transColor)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_FILE;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc);
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit);
	image_info->width = _width;
	image_info->height = _height;

	size_t size = _tcslen(_file_name);
	file_name = new TCHAR[size + 1];
	//memset(file_name, 0x00, sizeof(TCHAR)*(size+1));
	_tcscpy_s(file_name, size + 1, _file_name);
	file_name[size] = NULL;

	trans = _trans;
	trans_color = _transColor;

	//Alpha Blend용
	blend_func.BlendFlags = 0;
	blend_func.AlphaFormat = 0;
	blend_func.BlendOp = AC_SRC_OVER;

	blend_info = new ImageInfo;
	blend_info->load_type = LOAD_EMPTY;
	blend_info->resID = 0;
	blend_info->hMemDC = CreateCompatibleDC(hdc);
	blend_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blend_info->hOldBit = (HBITMAP)SelectObject(blend_info->hMemDC, blend_info->hBit);
	blend_info->width = GAME_WIDTH;
	blend_info->height = GAME_HEIGHT;

	if (image_info->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * _file_name, const float x, const float y,
	const int _width, const int _height, const bool _trans, const COLORREF _transColor)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_FILE;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc);
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit);
	image_info->width = _width;
	image_info->height = _height;
	image_info->x = x;
	image_info->y = y;

	size_t size = _tcslen(_file_name);
	file_name = new TCHAR[size + 1];
	//memset(file_name, 0x00, sizeof(TCHAR)*(size+1));
	_tcscpy_s(file_name, size + 1, _file_name);
	file_name[size] = NULL;

	trans = _trans;
	trans_color = _transColor;

	//Alpha Blend용
	blend_func.BlendFlags = 0;
	blend_func.AlphaFormat = 0;
	blend_func.BlendOp = AC_SRC_OVER;

	blend_info = new ImageInfo;
	blend_info->load_type = LOAD_EMPTY;
	blend_info->resID = 0;
	blend_info->hMemDC = CreateCompatibleDC(hdc);
	blend_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blend_info->hOldBit = (HBITMAP)SelectObject(blend_info->hMemDC, blend_info->hBit);
	blend_info->width = GAME_WIDTH;
	blend_info->height = GAME_HEIGHT;

	if (image_info->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * _file_name, const int _width, const int _height,
	const int frameX, const int frameY, const bool _trans, const COLORREF _transColor)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_FILE;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc);
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit);
	image_info->width = _width;
	image_info->height = _height;
	image_info->current_frameX = 0;
	image_info->current_frameY = 0;
	image_info->frame_width = _width / frameX; //이미지의 전체 사이즈를 프레임 수로 나눈 것이 프레임 하나의 사이즈
	image_info->frame_height = _height / frameY;
	image_info->max_frameX = frameX - 1; //해당 방향의 최대 프레임 인덱스는 프레임수에서 1을 뺀 값(Zeor Base)
	image_info->max_frameY = frameY - 1;

	size_t size = _tcslen(_file_name);
	file_name = new TCHAR[size + 1];
	//memset(file_name, 0x00, sizeof(TCHAR)*(size+1));
	_tcscpy_s(file_name, size + 1, _file_name);
	file_name[size] = NULL;

	trans = _trans;
	trans_color = _transColor;

	//Alpha Blend용
	blend_func.BlendFlags = 0;
	blend_func.AlphaFormat = 0;
	blend_func.BlendOp = AC_SRC_OVER;

	blend_info = new ImageInfo;
	blend_info->load_type = LOAD_EMPTY;
	blend_info->resID = 0;
	blend_info->hMemDC = CreateCompatibleDC(hdc);
	blend_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blend_info->hOldBit = (HBITMAP)SelectObject(blend_info->hMemDC, blend_info->hBit);
	blend_info->width = GAME_WIDTH;
	blend_info->height = GAME_HEIGHT;

	if (image_info->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

bool Image::Init(const TCHAR * _file_name, const float x, const float y, const int _width,
	const int _height, const int frameX, const int frameY, const bool _trans, const COLORREF _transColor)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_FILE;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc);
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit);
	image_info->x = x;
	image_info->y = y;
	image_info->width = _width;
	image_info->height = _height;
	image_info->current_frameX = 0;
	image_info->current_frameY = 0;
	image_info->frame_width = _width / frameX; //이미지의 전체 사이즈를 프레임 수로 나눈 것이 프레임 하나의 사이즈
	image_info->frame_height = _height / frameY;
	image_info->max_frameX = frameX - 1; //해당 방향의 최대 프레임 인덱스는 프레임수에서 1을 뺀 값(Zeor Base)
	image_info->max_frameY = frameY - 1;

	size_t size = _tcslen(_file_name);
	file_name = new TCHAR[size + 1];
	//memset(file_name, 0x00, sizeof(TCHAR)*(size+1));
	_tcscpy_s(file_name, size + 1, _file_name);
	file_name[size] = NULL;

	trans = _trans;
	trans_color = _transColor;

	//Alpha Blend용
	blend_func.BlendFlags = 0;
	blend_func.AlphaFormat = 0;
	blend_func.BlendOp = AC_SRC_OVER;

	blend_info = new ImageInfo;
	blend_info->load_type = LOAD_EMPTY;
	blend_info->resID = 0;
	blend_info->hMemDC = CreateCompatibleDC(hdc);
	blend_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, GAME_WIDTH, GAME_HEIGHT);
	blend_info->hOldBit = (HBITMAP)SelectObject(blend_info->hMemDC, blend_info->hBit);
	blend_info->width = GAME_WIDTH;
	blend_info->height = GAME_HEIGHT;

	if (image_info->hBit == nullptr)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

void Image::Release()
{
	if (image_info)
	{
		SelectObject(image_info->hMemDC, image_info->hOldBit);
		DeleteObject(image_info->hBit);
		DeleteDC(image_info->hMemDC);

		if (image_info)
			delete image_info;
		if (file_name)
			delete file_name;

		trans = false;
		trans_color = RGB(0, 0, 0);
	}

	if (blend_info)
	{
		SelectObject(blend_info->hMemDC, blend_info->hOldBit);
		DeleteObject(blend_info->hBit);
		DeleteDC(blend_info->hMemDC);

		if (blend_info)
			delete blend_info;
	}
}

void Image::Render(const HDC hdc)
{
	BitBlt(hdc, 0, 0,
		image_info->width,
		image_info->height,
		image_info->hMemDC,
		0, 0, SRCCOPY);
}

void Image::Render(const HDC hdc, const int destX, const int destY)
{
	if (trans)
	{
		GdiTransparentBlt
		(
			hdc, destX, destY,
			image_info->width,
			image_info->height,
			image_info->hMemDC,
			0, 0,
			image_info->width,
			image_info->height,
			trans_color);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			image_info->width,
			image_info->height,
			image_info->hMemDC,
			0, 0, SRCCOPY);
	}

	//StretchBlt
}

void Image::Render(const HDC hdc, const int destX, const int destY, const int srcX, const int srcY,
	const int srcWidth, const int srcHeight)
{
	if (trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX, destY,			//그려질 영역의 시작 위치
			srcWidth, srcHeight,	//그려질 영역의 크기
			image_info->hMemDC,
			srcX, srcY,				//그릴 이미지의 시작 위치
			srcWidth, srcHeight,	//그릴 이미지의 크기	
			trans_color);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			srcWidth, srcHeight,
			image_info->hMemDC,
			srcX, srcY, SRCCOPY);
	}
}

void Image::LoopRender(const HDC hdc, const RECT * drawArea,
	int offSetX, int offSetY)
{
	static int nLoopCount = 0;
	static int nRenderCount = 1;
	TCHAR szTemp[100] = { 0, };

	//화면 밖으로 나가면 보정해준다
	if (offSetX < 0)
	{
		offSetX = image_info->width + (offSetX % image_info->width);
	}
	if (offSetY < 0)
	{
		offSetY = image_info->height + (offSetY % image_info->height);
	}
	//오프셋 영역을 받아올 변수
	int sourWidth;
	int sourHeight;
	//그려주는 영역
	RECT rcDest;
	RECT rcSour;

	//그려주는 영역을 잡아준다.
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;  //너비
	int drawAreaH = drawArea->bottom - drawAreaY; //높이

												  //Y축부터
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % image_info->height;
		rcSour.bottom = image_info->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//그려주는 영역의 높이보다 y축이 크면
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		//화면 밖으로 나간 영역만큼 뿌려줄 위치에 산정한다.
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//x축
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % image_info->width;
			rcSour.right = image_info->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			Render(hdc, rcDest.left, rcDest.top, //뿌려줄 위치 x y
				rcSour.left, rcSour.top,		 //뿌려올 위치
				rcSour.right - rcSour.left,		 //가로크기
				rcSour.bottom - rcSour.top);	 //세로크기
			nRenderCount++;
#if defined(DEBUG) || defined(_DEBUG)
#ifdef _LOOPRENDERTEST
			_stprintf_s(szTemp, sizeof(szTemp), TEXT("RCount : %d, DL = %d, DT = %d, DR = %d, DB = %d, SL = %d, ST = %d, SR = %d, SB = %d")
				, nRenderCount
				, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom
				, rcSour.left, rcSour.top, rcSour.right, rcSour.bottom);
			TextOut(image_info->hMemDC, 10, 10, szTemp, _tcslen(szTemp));
#endif // _LOOPRENDERTEST
#endif //#if defined(DEBUG) || defined(_DEBUG)
		}
	}

	nLoopCount++;
}

void Image::FrameRender(const HDC hdc, const int destX, const int destY)
{
	if (trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			image_info->current_frameX * image_info->frame_width,
			image_info->current_frameY * image_info->frame_height,
			image_info->frame_width,
			image_info->frame_height,
			trans_color);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			image_info->current_frameX * image_info->frame_width,
			image_info->current_frameY * image_info->frame_height,
			SRCCOPY);
	}
}

void Image::FrameRender(const HDC hdc, const int destX, const int destY,
	const int current_frameX, const int current_frameY)
{
	image_info->current_frameX = current_frameX;
	image_info->current_frameY = current_frameY;

	if (trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			current_frameX * image_info->frame_width,
			current_frameY * image_info->frame_height,
			image_info->frame_width,
			image_info->frame_height,
			trans_color);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			current_frameX * image_info->frame_width,
			current_frameY * image_info->frame_height,
			SRCCOPY);
	}
}

void Image::AniRender(const HDC hdc, const int destX, const int destY, const Animation * ani)
{
	Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y,
		ani->GetFrameWidth(), ani->GetFrameHeight());
}

void Image::AlphaRender(const HDC hdc, BYTE alpha)
{
	blend_func.SourceConstantAlpha = alpha;

	if (trans)
	{
		BitBlt(blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			hdc,
			(int)image_info->x, (int)image_info->y,
			SRCCOPY);

		GdiTransparentBlt(blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			image_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			trans_color);

		AlphaBlend(hdc,
			(int)image_info->x, (int)image_info->y,
			image_info->width, image_info->height,
			blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			blend_func);
	}
	else
	{
		AlphaBlend(hdc,
			(int)image_info->x, (int)image_info->y,
			image_info->width, image_info->height,
			image_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			blend_func);
	}
}

void Image::AlphaRender(const HDC hdc, const int destX, const int destY, BYTE alpha)
{
	blend_func.SourceConstantAlpha = alpha;

	if (trans)
	{
		BitBlt(blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			hdc,
			destX, destY,
			SRCCOPY);

		GdiTransparentBlt(blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			image_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			trans_color);

		AlphaBlend(hdc,
			destX, destY,
			image_info->width, image_info->height,
			blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			blend_func);
	}
	else
	{
		AlphaBlend(hdc,
			destX, destY,
			image_info->width, image_info->height,
			image_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			blend_func);
	}
}

void Image::AlphaRender(const HDC hdc, const int destX, const int destY,
	const int current_frameX, const int current_frameY, BYTE alpha)
{
	blend_func.SourceConstantAlpha = alpha;

	if (trans)
	{
		BitBlt(blend_info->hMemDC,
			0, 0,
			image_info->width, image_info->height,
			hdc,
			destX, destY,
			SRCCOPY);

		GdiTransparentBlt(blend_info->hMemDC,
			0, 0,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			current_frameX * image_info->frame_width,
			current_frameY * image_info->frame_height,
			image_info->frame_width,
			image_info->frame_height,
			trans_color);

		GdiAlphaBlend(hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			blend_info->hMemDC,
			0, 0,
			image_info->frame_width,
			image_info->frame_height,
			blend_func);
	}
	else
	{
		GdiAlphaBlend(hdc,
			destX, destY,
			image_info->frame_width,
			image_info->frame_height,
			image_info->hMemDC,
			current_frameX * image_info->frame_width,
			current_frameY * image_info->frame_height,
			image_info->frame_width,
			image_info->frame_height,
			blend_func);
	}
}

void Image::SetTransColor(bool _trans, COLORREF _transColor)
{
	trans = _trans;
	trans_color = _transColor;
}
