#pragma once

//클래스 전방선언
class Animation;

class AnimationManager
{
private:
	std::vector<Animation*> motion_list; //여러 애니메이션 정보를 담을 리스트

public:
	AnimationManager() = default;
	~AnimationManager();

	void AddMotion(const Animation* ani);
	void DeleteMotion(const int index);
	Animation* FindMotion(const int index);

	void Release();

	void Play(const int index);
	void Stop(const int index);

	bool IsPlaying(const int index);
};

