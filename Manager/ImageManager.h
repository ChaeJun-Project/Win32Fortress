#pragma once

#include "Utility/SingletonBase.h"

//Ŭ���� ���漱��
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
	// Image ���
	//�� �̹���
	Image* AddImage(const std::string& key, const int width, const int height);
	//���� �ε尡 �ʿ��� �Ϲ� �̹���
	Image* AddImage(const std::string& key, const std::string& fileName,
		const int width, const int height, const bool trans, const COLORREF& transColor);
	Image* AddImage(const std::string& key, const std::string& fileName, const float x, const float y,
		const int width, const int height, const bool trans, const COLORREF& transColor);
	//���� �ε尡 �ʿ��� ��������Ʈ �̹��� 
	Image* AddFrameImage(const std::string& key, const std::string& fileName,
		const float x, const float y, const int width, const int height,
		const int frameX, const int frameY, const bool trans, const COLORREF& transColor);
	Image* AddFrameImage(const std::string& key, const std::string& fileName,
		const int width, const int height, const int frameX, const int frameY,
		const bool trans, const COLORREF& transColor);

	///////////////////////////////////////////////
	// Image �˻�
	Image* FindImage(const std::string& key);

	///////////////////////////////////////////////
	// Image ����
	bool DeleteImage(const std::string& key);
	void DeleteAll();

	///////////////////////////////////////////////
	// Image Render
	//�Ϲ� ���� �Լ�
	void Render(const std::string& key, const HDC hdc);
	void Render(const std::string& key, const HDC hdc, const int destX, const int destY);
	void Render(const std::string& key, const HDC hdc, const int destX, const int destY,
		const int srcX, const int srcY, const int srcWidth, const int srcHeight);
	//������ ���� �Լ�
	void FrameRender(const std::string& key, const HDC hdc, const int destX, const int destY);
	void FrameRender(const std::string& key, const HDC hdc, const int destX, const int destY,
		const int currentFrameX, const int currentFrameY);

};

