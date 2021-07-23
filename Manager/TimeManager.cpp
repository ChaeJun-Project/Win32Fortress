#include "Win32Fortress.h"

TimeManager::TimeManager() : fps(0.0f)
{
}

TimeManager::~TimeManager()
{
	Release();
}

bool TimeManager::Init(const float _fps)
{
	timer = new Timer;
	timer->Init();
	fps = _fps;

	return true;
}

void TimeManager::Release()
{
	SAFE_DELETE(timer);
}

void TimeManager::Update()
{
	if (timer)
		timer->Tick(fps);
}

void TimeManager::Render(HDC hdc)
{
	// �������̳� Ÿ�̸� ���� ������ �ý�Ʈ�� ����ϴ� �κ��� �߰�
#if defined(DEBUG) || defined(_DEBUG)
	std::string str = "FPS : ";
	str += std::to_string(timer->GetFrameRate());
	TextOutA(hdc, 5, 5, str.c_str(), (int)str.size());
#endif // #if defined(DEBUG) || defined(_DEBUG)
}

float TimeManager::GetElapsedTime() const
{
	return timer->GetElapsedTime();
}

float TimeManager::GetWorldTime() const
{
	return timer->GetWorldTime();
}

int TimeManager::GetFrameRate() const
{
	return timer->GetFrameRate();
}
