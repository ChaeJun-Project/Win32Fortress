#pragma once

class Timer
{
private:
	bool			is_hardware;
	float			time_scale;
	float			time_elapsed;

	__int64			cur_time;
	__int64			last_time;
	__int64			period_frequency;

	unsigned long	frame_rate;
	unsigned long	fps_frame_count;

	float			fps_time_elapsed;
	float			world_time;

public:
	Timer() = default;
	~Timer() = default;

	bool Init();
	void Tick(const float lockFPS = 0.f);

	unsigned long GetFrameRate() const { return frame_rate; }

	inline float GetElapsedTime() const { return time_elapsed; }
	inline float GetWorldTime() const { return world_time; }
};

