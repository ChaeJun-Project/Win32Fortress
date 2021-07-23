#pragma once

//클래스 전방선언
class Image;

using FrameList = std::vector<POINT>;
using PlayList = std::vector<int>;

class Animation
{
private:
	FrameList	frame_list;		//Sprite Image에서 각각의 Frame Image의 위치를 저장
	PlayList	play_list;		//Sprite Image에서 각각의 Frame Image의 실행 순서를 인덱스로 저장

	int			frame_num;		//각 Frame
	int			frame_width;	//Frame당 사이즈
	int			frame_height;

	bool		loop;			//반복 여부
	bool		play;			//실행 여부

	float		frame_update_time;//Frame 속도
	float		elapsed_time;	//경과 시간 

	int		now_play_index;	//현재 실행중인 Frame Image 인덱스

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

