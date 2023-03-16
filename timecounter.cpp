#include "timecounter.h"

int TimeCounter::getHour() const
{
    return hour;
}

int TimeCounter::getMin() const
{
    return min;
}

bool TimeCounter::getIs_break_time() const
{
    return is_break_time;
}

TimeCounter::TimeCounter(int hour, int min, bool is_break_time)
{
    this->hour = hour;
    this->min = min;
    this->is_break_time = is_break_time;
}
