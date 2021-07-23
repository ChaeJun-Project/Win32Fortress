#pragma once
#include "ObjectBase.h"

class Image;

class BackGround : public ObjectBase
{
private:
	Image*	background;

public:
	BackGround(const float& width, const float& height);
   ~BackGround();

	bool Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc, const TPoint* ptCam) override;

};

