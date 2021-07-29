#include "Win32Fortress.h"

Animation::Animation() : frame_num(0), frame_width(0), frame_height(0),
loop(false), play(false), frame_update_time(0.f), elapsed_time(0.f),
current_play_index(0), start(0), end(0)
{
}

Animation::~Animation()
{
	Release();
}

//얕은 복사
Animation::Animation(const Animation & obj)
{
	for (auto a : obj.frame_list)
		frame_list.push_back(a);
	for (auto a : obj.play_list)
		play_list.push_back(a);

	frame_num = obj.frame_num;
	frame_width = obj.frame_width;
	frame_height = obj.frame_height;
	frame_update_time = obj.frame_update_time;

	loop = obj.loop;
	elapsed_time = 0.f;
	current_play_index = 0;
	play = false;
}

//대입 연산자 오버로딩
Animation & Animation::operator=(const Animation & obj)
{
	for (auto a : obj.frame_list)
		frame_list.push_back(a);
	for (auto a : obj.play_list)
		play_list.push_back(a);


	frame_num = obj.frame_num;
	frame_width = obj.frame_width;
	frame_height = obj.frame_height;
	frame_update_time = obj.frame_update_time;

	loop = obj.loop;
	elapsed_time = 0.f;
	current_play_index = 0;
	play = false;

	return *this;
}

bool Animation::Init(const int width, const int height, const int frameW, const int frameH, const int start, const int end, const bool reverse)
{
	frame_width = frameW;
	int frameX = width / frameW;  // frameX = 가로방향의 프레임 갯수, frameW = 프레임의 가로방향 사이즈

	frame_height = frameH;
	int frameY = height / frameH; // frameY = 세로방향의 프레임 갯수, frameH = 프레임의 세로방향 사이즈


	frame_num = frameX * frameY;	  //Sprite Image의 전체 Frame 수

	//가로로 1줄씩 수행
	for (int i = 0; i < frameY; ++i)
	{
		//한 칸씩 오른쪽으로 이동하며 스프라이트 이미지에서 각 프레임의 위치를 저장
		for (int j = 0; j < frameX; ++j)
		{
			POINT framePos;
			framePos.x = j * frameW;
			framePos.y = i * frameH;
			frame_list.push_back(framePos);
		}
	}

	//시작 인덱스
	this->start = start;

	//끝 인덱스
	this->end = end;

	SetPlayFrame(start, end, reverse, true);

	return true;
}

bool Animation::Init(Image * image, const int start, const int end, const bool reverse)
{
	Init(image->GetSizeWidth(), image->GetSizeHeight(),
		image->GetFrameWidth(), image->GetFrameHeight(), start, end, reverse);

	return true;
}

void Animation::Release()
{
	frame_list.clear();
	frame_list.shrink_to_fit();

	play_list.clear();
	play_list.shrink_to_fit();
}

void Animation::SetPlayFrame(const bool reverse, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	for (int i = 0; i < frame_num; ++i)
		play_list.push_back(i);

	if (reverse)
	{
		for (int i = frame_num - 1; i >= 0; --i)
			play_list.push_back(i);
	}
}

void Animation::SetPlayFrame(const int * playArr, int arraySize, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	for (int i = 0; i < arraySize; ++i)
		play_list.push_back(playArr[i]);
}

void Animation::SetPlayFrame(const int start, const int end, const bool reverse, const bool loop)
{
	this->loop = loop;

	play_list.clear();

	if (start == end)
	{
		Stop();
		return;
	}

	//Frame 순서가 반대, reverse가 true이면 역순으로 다시 재생
	if (start > end)
	{
		for (int i = start; i >= end; --i)
			play_list.push_back(i);

		if (reverse) //여기선 정방향 진행
		{
			for (int i = end + 1; i < start; ++i)
				play_list.push_back(i);
		}
	}

	//정 방향으로 재생
	else
	{
		for (int i = start; i < end; ++i)
			play_list.push_back(i);

		if (reverse) //여기선 역방향 진행
		{
			for (int i = end - 1; i > start; --i)
				play_list.push_back(i);
		}
	}
}

void Animation::SetFPS(const int frameTime)
{
	frame_update_time = static_cast<float>(frameTime) * 0.001f;
}

//프레임 업데이트
void Animation::FrameUpdate(const float _elapsed_time)
{
	if (play)
	{
		elapsed_time += _elapsed_time;

		//기준 FPS보다 경과 시간이 큰 경우(지난 경우) 
		if (elapsed_time >= frame_update_time)
		{
			elapsed_time -= frame_update_time;

			++current_play_index; //현재 인덱스 증가

			if (current_play_index == play_list.size())
			{
				if (loop)
					current_play_index = 0;
				else
				{
					--current_play_index;
					play = false;
				}
			}
		}
	}
}

//애니메이션 시작
void Animation::Start()
{
	play = true;
	current_play_index = 0;
}

//애니메이션 중지(호출과 동시에 애니메이션을 끝냄)
void Animation::Stop()
{
	play = false;
	current_play_index = end - 1;
}

//애니메이션 정지(진행되다가 정지되는 경우)
void Animation::Pause()
{
	play = false;
}

//애니메이션 계속 진행(정지되었다가 다시 진행되는 경우)
void Animation::Resume()
{
	play = true;
}
