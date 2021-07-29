#include "Win32Fortress.h"

bool BackBuffer::Init(int width, int height)
{
	if (back_buffer_info != nullptr)
		Release();

	HDC hdc = GetDC(g_hWnd); //�ش� �������� �ڵ� ������ HDC�� ���� �޾ƿ�

	back_buffer_info = new BackBufferInfo;
	back_buffer_info->hMemDC = CreateCompatibleDC(hdc); //�޾ƿ� HDC�� ȣȯ�Ǵ� Memory DC�� ����
	back_buffer_info->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //�޾ƿ� HDC�� ȣȯ�Ǵ� �ش� ũ���� ��Ʈ�� ��ü ����
	back_buffer_info->hOldBit = (HBITMAP)SelectObject(back_buffer_info->hMemDC, back_buffer_info->hBit); //Memory DC�� ��Ʈ�� ��ü ����
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
	//back_buffer_info�� hMemDC�� �׷��� ������ hdc�� �ʰ�� ����
	//���⼭ ���� ���۸� �۾��� �̷����
	BitBlt(hdc, destX, destY, back_buffer_info->width, back_buffer_info->height,
		back_buffer_info->hMemDC, 0, 0, SRCCOPY);
}
