#pragma once

//Ŭ���� ���漱��
class Image;

/*�ζ��� �Լ�
	  �Լ� ȣ�� �������� ���� �ӵ��� �Լ��� ����� �� �ֵ��� ����
	  ȣ��� ������ �ּ� ���� �ش� �Լ��� �Ű������� ���ؿ� ������� ����

	  ����
	  1. ���� �ӵ��� ��������. (�ڵ� ����ȭ)

	  ����
	  1. ���ʿ��ϰ� ���� ������ �ӵ��� ������
	  2. ������ ��� ���������� ũ�Ⱑ Ŀ��
	*/
class Animation
{
private:
	std::vector<POINT>	frame_list;		//Sprite Image���� ������ Frame Image�� ��ġ�� ����
	std::vector<int>	play_list;		//Sprite Image���� ������ Frame Image�� ���� ������ �ε����� ����

	int			frame_num;		//�� Frame

	//Frame�� ������
	int			frame_width;
	int			frame_height;

	bool		loop;			//�ݺ� ����
	bool		play;			//���� ����

	float		frame_update_time;  //Frame �ӵ�
	float		elapsed_time;		//��� �ð� 

	int		current_play_index;	//���� �������� Frame Image �ε���

	int start;
	int end;

public:
	Animation();
	~Animation();

	//������ �����ε�
	//���� ����
	explicit Animation(const Animation& obj);

	//���� ������ �����ε�
	Animation& operator=(const Animation& obj);

	//�Լ� �����ε�
	bool Init(const int width, const int height, const int frameWidth, const int frameHeight, const int start, const int end, const bool reverse);
	bool Init(Image* image, const int start, const int end, const bool reverse);

	void Release();

	//�Լ� �����ε�
	void SetPlayFrame(const bool reverse = false, const bool loop = false);
	void SetPlayFrame(const int* playArr, int arraySize, const bool loop = false);
	void SetPlayFrame(const int start, const int end,
		const bool reverse = false, const bool loop = false);

	//������ ����
	void SetFPS(const int frameTime);

	//������ ������Ʈ
	void FrameUpdate(const float _elapsedTime);

	void Start(); //�ִϸ��̼� ����
	void Stop();  //�ִϸ��̼� ����(ȣ��� ���ÿ� �ִϸ��̼��� ����)
	void Pause(); //�ִϸ��̼� ����(����Ǵٰ� �����Ǵ� ���)
	void Resume();//�ִϸ��̼� ��� ����(�����Ǿ��ٰ� �ٽ� ����Ǵ� ���)

	//�ζ��� �Լ�
	inline bool		isPlay() const { return play; }
	inline POINT	GetFramePos() const { return frame_list[play_list[current_play_index]]; }
	inline int		GetNowPlayIndex() const { return current_play_index; }
	inline int		GetFrameWidth() const { return frame_width; }
	inline int		GetFrameHeight() const { return frame_height; }
};

