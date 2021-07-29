#include "Win32Fortress.h"

#pragma comment(lib, "msimg32.lib")

Image::Image()
	: image_info(nullptr),
	trans(false), trans_color(RGB(0, 0, 0)), blend_info(nullptr)
{
}

Image::~Image()
{
	Release();
}

//�ش� �������� �� ��Ʈ�� ������ ������ �ִ� �̹����� �����ϱ� ���� �ʱ�ȭ 
bool Image::Init(const int _width, const int _height)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd); //�ش� �������� �ڵ� ������ HDC�� ���� �޾ƿ�

	image_info = new ImageInfo;
	image_info->load_type = LOAD_EMPTY;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	image_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height); //�޾ƿ� HDC�� ȣȯ�Ǵ� �ش� ũ���� ��Ʈ�� ��ü ����
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
	image_info->width = _width;
	image_info->height = _height;

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

//�ش� �������� �̹����� ���Ͽ��� �ε��ؼ� �����ϴ� �뵵�� �ʱ�ȭ
bool Image::Init(const TCHAR* _file_name, const int _width, const int _height,
	const bool _trans, const COLORREF _transColor)
{
	if (image_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);

	image_info = new ImageInfo;
	image_info->load_type = LOAD_FILE;
	image_info->resID = 0;
	image_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
	image_info->width = _width;
	image_info->height = _height;

	trans = _trans;
	trans_color = _transColor;

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
	image_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
	image_info->width = _width;
	image_info->height = _height;
	image_info->x = x;
	image_info->y = y;

	trans = _trans;
	trans_color = _transColor;

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
	image_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
	image_info->width = _width;
	image_info->height = _height;
	image_info->current_frameX = 0;
	image_info->current_frameY = 0;
	image_info->frame_width = _width / frameX; //�̹����� ��ü ����� ������ ���� ���� ���� ������ �ϳ��� ������
	image_info->frame_height = _height / frameY;
	image_info->max_frameX = frameX - 1; //�ش� ������ �ִ� ������ �ε����� �����Ӽ����� 1�� �� ��
	image_info->max_frameY = frameY - 1;

	trans = _trans;
	trans_color = _transColor;

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
	image_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	image_info->hBit = (HBITMAP)LoadImage(g_hInstance, _file_name,
		IMAGE_BITMAP, _width, _height, LR_LOADFROMFILE);
	image_info->hOldBit = (HBITMAP)SelectObject(image_info->hMemDC, image_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
	image_info->x = x;
	image_info->y = y;
	image_info->width = _width;
	image_info->height = _height;
	image_info->current_frameX = 0;
	image_info->current_frameY = 0;
	image_info->frame_width = _width / frameX; //�̹����� ��ü ����� ������ ���� ���� ���� ������ �ϳ��� ������
	image_info->frame_height = _height / frameY;
	image_info->max_frameX = frameX - 1; //�ش� ������ �ִ� ������ �ε����� �����Ӽ����� 1�� �� ��
	image_info->max_frameY = frameY - 1;

	trans = _trans;
	trans_color = _transColor;

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

		if (image_info)
			delete image_info;

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
}

void Image::Render(const HDC hdc, const int destX, const int destY, const int srcX, const int srcY,
	const int srcWidth, const int srcHeight)
{
	if (trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX, destY,			//�׷��� ������ ���� ��ġ
			srcWidth, srcHeight,	//�׷��� ������ ũ��
			image_info->hMemDC,
			srcX, srcY,				//�׸� �̹����� ���� ��ġ
			srcWidth, srcHeight,	//�׸� �̹����� ũ��	
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

void Image::SetTransColor(bool _trans, COLORREF _transColor)
{
	trans = _trans;
	trans_color = _transColor;
}
