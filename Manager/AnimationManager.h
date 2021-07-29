#pragma once

//Ŭ���� ���漱��
class Animation;

class AnimationManager
{
private:
	std::vector<Animation*> motion_list; //���� �ִϸ��̼� ������ ���� ����Ʈ

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

