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
	float durationTime;	// ��ٸ��� �ð�

private:
	float startTime;	// ���� �ð�
	float endTime;		// ������ �ð�
};

