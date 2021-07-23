#include "Win32Fortress.h"

//timeGetTime() 을 호출하기 위해 헤더와 라이브러리 추가
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


bool Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&period_frequency))
	{
		is_hardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
		time_scale = 1.f / period_frequency;
	}
	else
	{
		is_hardware = false;
		last_time = timeGetTime();
		time_scale = 0.001f;
	}

	frame_rate = 0;
	fps_frame_count = 0;
	fps_time_elapsed = 0.f;
	world_time = 0.f;

	return true;
}

void Timer::Tick(const float lockFPS)
{
	if (is_hardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);
	else
		cur_time = timeGetTime();

	time_elapsed = (cur_time - last_time) * time_scale;

	if (lockFPS > 0.f)
	{
		while (time_elapsed < 1.f / lockFPS)
		{
			if (is_hardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);
			else
				cur_time = timeGetTime();

			time_elapsed = (cur_time - last_time) * time_scale;
		}
	}

	last_time = cur_time;
	++fps_frame_count;
	fps_time_elapsed += time_elapsed;
	world_time += time_elapsed;

	if (fps_time_elapsed > 1.f)
	{
		frame_rate = fps_frame_count;
		fps_frame_count = 0;
		fps_time_elapsed = 0.f;
	}
}
