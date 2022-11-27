#include "Timer.h"

Timer::Timer()
{
    startTime = 0;
    endTime = 0;
    durationTime = 0;
}

Timer::~Timer()
{
}

bool Timer::CheckTimer()
{
    endTime = clock();

    if (endTime - startTime > durationTime)
    {
        startTime = clock();
        return true;
    }

    return false;
}
