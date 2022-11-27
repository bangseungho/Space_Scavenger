#pragma once
#include <ctime>

class Timer
{
public:
	Timer();
	~Timer();

public:
	bool CheckTimer();

public:
	float durationTime;	// 기다리는 시간

private:
	float startTime;	// 시작 시간
	float endTime;		// 마지막 시간
};

