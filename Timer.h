#pragma once
#include <ctime>

class Timer
{
public:
	Timer();
	~Timer();

public:
	void OnTimer(double _Duration);
	bool CheckTimer();

public:
	float durationTime;	// ��ٸ��� �ð�

private:
	float startTime;	// ���� �ð�
	float endTime;		// ������ �ð�
};

