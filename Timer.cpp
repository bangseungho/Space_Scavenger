#include "Timer.h"

Timer::Timer()
{
    startTime = clock();
    endTime = 0;
    durationTime = 0;
}

Timer::~Timer()
{
}

void Timer::OnTimer(double _Duration)
{
    startTime = clock();
    durationTime = _Duration;
}

bool Timer::CheckTimer()
{
    endTime = clock();

    if (endTime - startTime > durationTime * 1000)
    {
        startTime = clock();
        return true;
    }

    return false;
}
