#pragma once

//더블 버퍼링을 위한 백 버퍼
//참고 사이트 https://alleysark.tistory.com/22
class BackBuffer
{
private:
	struct BackBufferInfo
	{
		HDC		hMemDC; // 비트맵 이미지가 로드될 메모리 DC
		HBITMAP hBit; // 비트맵 이미지의 핸들
		HBITMAP hOldBit; // 백업용 비트맵 이미지의 핸들

		int		width; // 이미지 사이즈 X
		int		height; // 이미지 사이즈 Y

		float	x; // 이미지 랜더링 시작 위치	
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

