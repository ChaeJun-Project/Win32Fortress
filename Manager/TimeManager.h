#pragma once

#include "Utility/SingletonBase.h"

//Ŭ���� ���漱��
class Timer;

class TimeManager: public SingletonBase<TimeManager>
{ 
private:
	Timer*		timer;
	float		fps;

public:
	TimeManager();
	~TimeManager();

	bool Init(const float _fps);
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime() const;
	float GetWorldTime() const;
	int	  GetFrameRate() const;
};

