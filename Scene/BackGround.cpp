#include "Win32Fortress.h"

BackGround::BackGround(const float& width, const float& height)
	: ObjectBase(width, height)
{
	background = new Image;
	assert(background != nullptr);
}

BackGround::~BackGround()
{
	SAFE_DELETE(background)
}

bool BackGround::Init()
{
	bool result = false;
	result = background->Init(TEXT("../BITMAP/MainStage.bmp"),
		static_cast<int>(GetSize().width), static_cast<int>(GetSize().height),
		false, RGB(1, 1, 1));
	assert(result == true);

	return true;
}

void BackGround::Release()
{
	background->Release();
}

void BackGround::Update()
{

}

void BackGround::Render(HDC hdc, const TPoint* ptCam)
{
	assert(ptCam != nullptr);

	background->Render(hdc, 0, 0, static_cast<int>(ptCam->x), static_cast<int>(ptCam->y), GAME_WIDTH, GAME_HEIGHT);
}

