#include "Win32Fortress.h"

ImageManager::~ImageManager()
{
	Release();
}

void ImageManager::Release()
{
	DeleteAll();
}

Image * ImageManager::AddImage(const std::string & key, const int width, const int height)
{
	//인자로 넘어온 키값으로 검색
	Image* img = FindImage(key);
	if (img)
		return img;

	//없으면 생성
	img = new Image;
	if (img->Init(width, height) == false)
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵에 인서트하고 리턴
	image_map.insert({ key, img });

	return img;
}

Image * ImageManager::AddImage(const std::string & key, const std::string & fileName, const int width, const int height, const bool trans, const COLORREF & transColor)
{
	//인자로 넘어온 키값으로 검색
	Image* img = FindImage(key);
	if (img)
		return img;

	//없으면 생성
	img = new Image;
	if (img->Init(fileName.c_str(), width, height, trans, transColor) == false)
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵에 인서트하고 리턴
	image_map.insert({ key, img });

	return img;
}

Image * ImageManager::AddImage(const std::string & key, const std::string & fileName, const float x, const float y, const int width, const int height, const bool trans, const COLORREF & transColor)
{
	//인자로 넘어온 키값으로 검색
	Image* img = FindImage(key);
	if (img)
		return img;

	//없으면 생성
	img = new Image;
	if (img->Init(fileName.c_str(), x, y, width, height, trans, transColor) == false)
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵에 인서트하고 리턴
	image_map.insert({ key, img });

	return img;
}

Image * ImageManager::AddFrameImage(const std::string & key, const std::string & fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, const bool trans, const COLORREF & transColor)
{
	//인자로 넘어온 키값으로 검색
	Image* img = FindImage(key);
	if (img)
		return img;

	//없으면 생성
	img = new Image;
	if (img->Init(fileName.c_str(), x, y, width, height, frameX, frameY, trans, transColor) == false)
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵에 인서트하고 리턴
	image_map.insert({ key, img });

	return img;
}

Image * ImageManager::AddFrameImage(const std::string & key, const std::string & fileName, const int width, const int height, const int frameX, const int frameY, const bool trans, const COLORREF & transColor)
{
	//인자로 넘어온 키값으로 검색
	Image* img = FindImage(key);
	if (img)
		return img;

	//없으면 생성
	img = new Image;
	if (img->Init(fileName.c_str(), width, height, frameX, frameY, trans, transColor) == false)
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵에 인서트하고 리턴
	image_map.insert({ key, img });

	return img;
}

Image* ImageManager::FindImage(const std::string & key)
{
	std::map<std::string, Image*>::iterator it = image_map.find(key);
	if (it != image_map.end())
		return it->second;

	return nullptr;
}

bool ImageManager::DeleteImage(const std::string & key)
{
	std::map<std::string, Image*>::iterator it = image_map.find(key);
	if (it != image_map.end())
	{
		if ((it->second))
		{
			(it->second)->Release();
			SAFE_DELETE(it->second);
		}
		image_map.erase(it);
		return true;
	}

	return false;
}

void ImageManager::DeleteAll()
{
	for (auto& img : image_map)
	{
		if ((img.second))
		{
			(img.second)->Release();
			SAFE_DELETE((img.second));
		}
	}

	image_map.clear();
}

void ImageManager::Render(const std::string & key, const HDC hdc)
{
	Image* img = FindImage(key);
	if (img)
		img->Render(hdc);
}

void ImageManager::Render(const std::string & key, const HDC hdc, const int destX, const int destY)
{
	Image* img = FindImage(key);
	if (img)
		img->Render(hdc, destX, destY);
}

void ImageManager::Render(const std::string & key, const HDC hdc, const int destX, const int destY, const int srcX, const int srcY, const int srcWidth, const int srcHeight)
{
	Image* img = FindImage(key);
	if (img)
		img->Render(hdc, destX, destY, srcX, srcY, srcWidth, srcHeight);
}

void ImageManager::FrameRender(const std::string & key, const HDC hdc, const int destX, const int destY)
{
	Image* img = FindImage(key);
	if (img)
		img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(const std::string& key, const HDC hdc, const int destX, const int destY,
	const int currentFrameX, const int currentFrameY)
{
	Image* img = FindImage(key);
	if (img)
		img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}


