#pragma once

//Ŭ���� ���漱��
class Image;

using FrameList = std::vector<POINT>;
using PlayList = std::vector<int>;

class Animation
{
private:
	FrameList	frame_list;		//Sprite Image���� ������ Frame Image�� ��ġ�� ����
	PlayList	play_list;		//Sprite Image���� ������ Frame Image�� ���� ������ �ε����� ����

	int			frame_num;		//�� Frame
	int			frame_width;	//Frame�� ������
	int			frame_height;

	bool		loop;			//�ݺ� ����
	bool		play;			//���� ����

	float		frame_update_time;//Frame �ӵ�
	float		elapsed_time;	//��� �ð� 

	int		now_play_index;	//���� �������� Frame Image �ε���

	int start;
	int end;

public:
	Animation();
	~Animation();

	Animation(const Animation& obj);
	Animation& operator=(const Animation& obj);

	bool Init(const int width, const int height, const int frameWidth, const int frameHeight, const int start, const int end, const bool reverse);
	bool Init(Image* image, const int start, const int end, const bool reverse);

	void Release();

	void SetPlayFrame(const bool reverse = false, const bool loop = false);
	void SetPlayFrame(const int* playArr, int arraySize, const bool loop = false);
	void SetPlayFrame(const int start, const int end,
		const bool reverse = false, const bool loop = false);

	void SetFPS(const int frameTime);

	void FrameUpdate(const float _elapsedTime);

	void Start();
	void Stop();
	void Pause();
	void Resume();

	inline bool		isPlay() const { return play; }
	inline POINT	GetFramePos() const { return frame_list[play_list[now_play_index]]; }
	inline int		GetNowPlayIndex() const { return now_play_index; }
	inline int		GetFrameWidth() const { return frame_width; }
	inline int		GetFrameHeight() const { return frame_height; }
};

