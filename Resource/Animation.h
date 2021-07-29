#pragma once

//클래스 전방선언
class Image;

/*인라인 함수
	  함수 호출 과정없이 빠른 속도로 함수를 사용할 수 있도록 해줌
	  호출된 시점의 주소 값과 해당 함수의 매개변수가 스텍에 저장되지 않음

	  장점
	  1. 실행 속도가 빨라진다. (코드 최적화)

	  단점
	  1. 불필요하게 사용시 컴파일 속도가 느려짐
	  2. 남용할 경우 실행파일의 크기가 커짐
	*/
class Animation
{
private:
	std::vector<POINT>	frame_list;		//Sprite Image에서 각각의 Frame Image의 위치를 저장
	std::vector<int>	play_list;		//Sprite Image에서 각각의 Frame Image의 실행 순서를 인덱스로 저장

	int			frame_num;		//각 Frame

	//Frame당 사이즈
	int			frame_width;
	int			frame_height;

	bool		loop;			//반복 여부
	bool		play;			//실행 여부

	float		frame_update_time;  //Frame 속도
	float		elapsed_time;		//경과 시간 

	int		current_play_index;	//현재 실행중인 Frame Image 인덱스

	int start;
	int end;

public:
	Animation();
	~Animation();

	//생성자 오버로딩
	//얕은 복사
	explicit Animation(const Animation& obj);

	//대입 연산자 오버로딩
	Animation& operator=(const Animation& obj);

	//함수 오버로딩
	bool Init(const int width, const int height, const int frameWidth, const int frameHeight, const int start, const int end, const bool reverse);
	bool Init(Image* image, const int start, const int end, const bool reverse);

	void Release();

	//함수 오버로딩
	void SetPlayFrame(const bool reverse = false, const bool loop = false);
	void SetPlayFrame(const int* playArr, int arraySize, const bool loop = false);
	void SetPlayFrame(const int start, const int end,
		const bool reverse = false, const bool loop = false);

	//프레임 설정
	void SetFPS(const int frameTime);

	//프레임 업데이트
	void FrameUpdate(const float _elapsedTime);

	void Start(); //애니메이션 시작
	void Stop();  //애니메이션 중지(호출과 동시에 애니메이션을 끝냄)
	void Pause(); //애니메이션 정지(진행되다가 정지되는 경우)
	void Resume();//애니메이션 계속 진행(정지되었다가 다시 진행되는 경우)

	//인라인 함수
	inline bool		isPlay() const { return play; }
	inline POINT	GetFramePos() const { return frame_list[play_list[current_play_index]]; }
	inline int		GetNowPlayIndex() const { return current_play_index; }
	inline int		GetFrameWidth() const { return frame_width; }
	inline int		GetFrameHeight() const { return frame_height; }
};

