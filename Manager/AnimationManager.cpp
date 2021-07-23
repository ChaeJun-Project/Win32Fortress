#include "Win32Fortress.h"

AnimationManager::~AnimationManager()
{
	Release();
}

void AnimationManager::AddMotion(const Animation* ani)
{
	motion_list.push_back(const_cast<Animation*>(ani));
}

void AnimationManager::DeleteMotion(const int index)
{
	if (motion_list[index])
	{
		delete motion_list[index];
		motion_list[index] = nullptr;
	}
}

Animation* AnimationManager::FindMotion(const int index)
{
	if (motion_list[index])
		return motion_list[index];

	return nullptr;
}

void AnimationManager::Release()
{
	for (auto& animation : motion_list)
	{
		SAFE_DELETE(animation)
	}

	motion_list.clear();
	motion_list.shrink_to_fit();
}

void AnimationManager::Play(const int index)
{
	motion_list[index]->Start();
}

void AnimationManager::Stop(const int index)
{
	if (IsPlaying(index))
		motion_list[index]->Stop();
}

bool AnimationManager::IsPlaying(const int index)
{
	return motion_list[index]->isPlay();
}