#pragma once

//클래스 전방선언
class Animation;

using AnimationList = std::vector<Animation*>;

class AnimationManager
{
private:
	AnimationList motion_list;

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

