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

//���� ����
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

//���� ������ �����ε�
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
	int frameX = width / frameW;  // frameX = ���ι����� ������ ����, frameW = �������� ���ι��� ������

	frame_height = frameH;
	int frameY = height / frameH; // frameY = ���ι����� ������ ����, frameH = �������� ���ι��� ������


	frame_num = frameX * frameY;	  //Sprite Image�� ��ü Frame ��

	//���η� 1�پ� ����
	for (int i = 0; i < frameY; ++i)
	{
		//�� ĭ�� ���������� �̵��ϸ� ��������Ʈ �̹������� �� �������� ��ġ�� ����
		for (int j = 0; j < frameX; ++j)
		{
			POINT framePos;
			framePos.x = j * frameW;
			framePos.y = i * frameH;
			frame_list.push_back(framePos);
		}
	}

	//���� �ε���
	this->start = start;

	//�� �ε���
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

	//Frame ������ �ݴ�, reverse�� true�̸� �������� �ٽ� ���
	if (start > end)
	{
		for (int i = start; i >= end; --i)
			play_list.push_back(i);

		if (reverse) //���⼱ ������ ����
		{
			for (int i = end + 1; i < start; ++i)
				play_list.push_back(i);
		}
	}

	//�� �������� ���
	else
	{
		for (int i = start; i < end; ++i)
			play_list.push_back(i);

		if (reverse) //���⼱ ������ ����
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

//������ ������Ʈ
void Animation::FrameUpdate(const float _elapsed_time)
{
	if (play)
	{
		elapsed_time += _elapsed_time;

		//���� FPS���� ��� �ð��� ū ���(���� ���) 
		if (elapsed_time >= frame_update_time)
		{
			elapsed_time -= frame_update_time;

			++current_play_index; //���� �ε��� ����

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

//�ִϸ��̼� ����
void Animation::Start()
{
	play = true;
	current_play_index = 0;
}

//�ִϸ��̼� ����(ȣ��� ���ÿ� �ִϸ��̼��� ����)
void Animation::Stop()
{
	play = false;
	current_play_index = end - 1;
}

//�ִϸ��̼� ����(����Ǵٰ� �����Ǵ� ���)
void Animation::Pause()
{
	play = false;
}

//�ִϸ��̼� ��� ����(�����Ǿ��ٰ� �ٽ� ����Ǵ� ���)
void Animation::Resume()
{
	play = true;
}
