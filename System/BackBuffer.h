#pragma once

//���� ���۸��� ���� �� ����
//���� ����Ʈ https://alleysark.tistory.com/22
class BackBuffer
{
private:
	struct BackBufferInfo
	{
		HDC		hMemDC; // ��Ʈ�� �̹����� �ε�� �޸� DC
		HBITMAP hBit; // ��Ʈ�� �̹����� �ڵ�
		HBITMAP hOldBit; // ����� ��Ʈ�� �̹����� �ڵ�

		int		width; // �̹��� ������ X
		int		height; // �̹��� ������ Y

		float	x; // �̹��� ������ ���� ��ġ	
		float	y;


		BackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			x = 0.f;
			y = 0.f;
		}
	};

	BackBufferInfo* back_buffer_info;

public:
	BackBuffer() : back_buffer_info(nullptr) {};
	~BackBuffer() = default;

	bool Init(int width, int height);
	void Release();
	void Render(HDC hdc, int destX, int destY);

	HDC GetMemDC() { return back_buffer_info->hMemDC; }
};

