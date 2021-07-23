#include "Win32Fortress.h"

bool BackBuffer::Init(int width, int height)
{
	if (back_buffer_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd);
	back_buffer_info = new BackBufferInfo;
	back_buffer_info->hMemDC = CreateCompatibleDC(hdc);
	back_buffer_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	back_buffer_info->hOldBit = (HBITMAP)SelectObject(back_buffer_info->hMemDC, back_buffer_info->hBit);
	back_buffer_info->width = width;
	back_buffer_info->height = height;

	if (back_buffer_info->hBit == NULL)
	{
		Release();
		return false;
	}

	ReleaseDC(g_hWnd, hdc);

	return true;
}

void BackBuffer::Release()
{
	if (back_buffer_info)
	{
		SelectObject(back_buffer_info->hMemDC, back_buffer_info->hOldBit);
		DeleteObject(back_buffer_info->hBit);
		DeleteDC(back_buffer_info->hMemDC);

		delete back_buffer_info;
	}
}

void BackBuffer::Render(HDC hdc, int destX, int destY)
{
	BitBlt(hdc, destX, destY, back_buffer_info->width, back_buffer_info->height,
		back_buffer_info->hMemDC, 0, 0, SRCCOPY);
}
