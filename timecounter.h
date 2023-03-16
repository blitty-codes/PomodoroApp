#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H


class TimeCounter
{
private:
    int hour;
    int min;
    bool is_break_time;

public:
    TimeCounter(int hour, int min, bool is_break_time);
    int getHour() const;
    int getMin() const;
    bool getIs_break_time() const;
};

#endif // TIMECOUNTER_H
