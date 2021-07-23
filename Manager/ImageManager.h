#pragma once

#include "Utility/SingletonBase.h"

//클래스 전방선언
class Image;

using ImageMap = std::map<std::string, Image*>;

class ImageManager : public SingletonBase<ImageManager>
{
private:
	ImageMap				image_map;

	ImageManager(const ImageManager& obj) = delete;
	ImageManager& operator=(const ImageManager& obj) = delete;

public:
	ImageManager() = default;
	~ImageManager();

	void Release();

	///////////////////////////////////////////////
	// Image 등록
	//빈 이미지
	Image* AddImage(const std::string& key, const int width, const int height);
	//파일 로드가 필요한 일반 이미지
	Image* AddImage(const std::string& key, const std::string& fileName,
		const int width, const int height, const bool trans, const COLORREF& transColor);
	Image* AddImage(const std::string& key, const std::string& fileName, const float x, const float y,
		const int width, const int height, const bool trans, const COLORREF& transColor);
	//파일 로드가 필요한 스프라이트 이미지 
	Image* AddFrameImage(const std::string& key, const std::string& fileName,
		const float x, const float y, const int width, const int height,
		const int frameX, const int frameY, const bool trans, const COLORREF& transColor);
	Image* AddFrameImage(const std::string& key, const std::string& fileName,
		const int width, const int height, const int frameX, const int frameY,
		const bool trans, const COLORREF& transColor);

	///////////////////////////////////////////////
	// Image 검색
	Image* FindImage(const std::string& key);

	///////////////////////////////////////////////
	// Image 삭제
	bool DeleteImage(const std::string& key);
	void DeleteAll();

	///////////////////////////////////////////////
	// Image Render
	//일반 랜더 함수
	void Render(const std::string& key, const HDC hdc);
	void Render(const std::string& key, const HDC hdc, const int destX, const int destY);
	void Render(const std::string& key, const HDC hdc, const int destX, const int destY,
		const int srcX, const int srcY, const int srcWidth, const int srcHeight);
	//프레임 랜더 함수
	void FrameRender(const std::string& key, const HDC hdc, const int destX, const int destY);
	void FrameRender(const std::string& key, const HDC hdc, const int destX, const int destY,
		const int currentFrameX, const int currentFrameY);

};

