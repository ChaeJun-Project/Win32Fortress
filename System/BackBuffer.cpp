#include "Win32Fortress.h"

bool BackBuffer::Init(int width, int height)
{
	if (back_buffer_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd); //해당 윈도우의 핸들 값으로 HDC의 값을 받아옴

	back_buffer_info = new BackBufferInfo;
	back_buffer_info->hMemDC = CreateCompatibleDC(hdc); //받아온 HDC와 호환되는 Memory DC를 생성
	back_buffer_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //받아온 HDC와 호환되는 해당 크기의 비트맵 객체 생성
	back_buffer_info->hOldBit = (HBITMAP)SelectObject(back_buffer_info->hMemDC, back_buffer_info->hBit); //Memory DC와 비트맵 객체 연결
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
	//back_buffer_info의 hMemDC에 그려진 내용을 hdc로 초고속 복사
	//여기서 더블 버퍼링 작업이 이루어짐
	BitBlt(hdc, destX, destY, back_buffer_info->width, back_buffer_info->height,
		back_buffer_info->hMemDC, 0, 0, SRCCOPY);
}
