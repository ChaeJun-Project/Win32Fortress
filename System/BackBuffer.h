#pragma once

class BackBuffer
{
private:
	struct BackBufferInfo
	{
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOldBit;
		float	x;
		float	y;

		int		width;
		int		height;

		BackBufferInfo()
		{
			hMemDC	= NULL;
			hBit	= NULL;
			hOldBit = NULL;
			x		= 0.f;
			y		= 0.f;
			width	= 0;
			height	= 0;
		}
	};

	BackBufferInfo* back_buffer_info;

	BackBuffer(const BackBuffer& obj) {};
	BackBuffer& operator=(const BackBuffer& obj) {};

public:
	BackBuffer() : back_buffer_info(nullptr) {};
	~BackBuffer() = default;

	bool Init(int width, int height);
	void Release();
	void Render(HDC hdc, int destX, int destY);

	inline HDC GetMemDC() { return back_buffer_info->hMemDC; }
};

