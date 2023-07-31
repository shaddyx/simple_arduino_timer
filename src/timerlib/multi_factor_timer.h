#pragma once
#include "simple_timer.h"
template <unsigned int N>
class MultiFactorTimer
{
private:
    unsigned long factor_timers[N];
    SimpleTimer overall_timer;
    SimpleTimer current_factor_timer;
    bool overall_timer_exceeded;
    bool factor_timer_exceeded;
    int current_factor;

public:
    void set_factor_timer(int factor, unsigned long timer)
    {
        if (factor > N - 1)
        {
            return;
        }
        factor_timers[factor] = timer;
    }

    void run(int overall_time)
    {
        current_factor = 0;
        overall_timer_exceeded = false;
        factor_timer_exceeded = false;
        overall_timer.set(overall_time);
        start_current_factor();
    }
    void start_current_factor()
    {
        current_factor_timer.set(factor_timers[current_factor]);
    }

    void next_factor()
    {
        current_factor++;
        if (current_factor > N - 1)
        {
            current_factor = N - 1;
            return;
        }
        start_current_factor();
    }

    bool overall_exceeded()
    {
        return overall_timer_exceeded;
    }

    bool factor_exceeded()
    {
        return factor_timer_exceeded;
    }

    int get_current_factor()
    {
        return current_factor;
    }
    bool is_started()
    {
        return overall_timer.is_started() && current_factor_timer.is_started();
    }
    
    unsigned long current_factor_time_last(){
        return current_factor_timer.time_last();
    }
    
    unsigned long overall_time_last(){
        return overall_timer.time_last();
    }

    unsigned long factor_time_last(int factor){
        if (factor < current_factor){
            return 0;
        }
        if (factor == current_factor){
            return current_factor_time_last();
        }
        if (factor > N - 1)
        {
            factor = N - 1;
        }
        return factor_timers[factor];
    }

    bool poll()
    {
        if (!is_started())
        {
            return false;
        }
        bool res = false;
        if (overall_timer.poll())
        {
            overall_timer_exceeded = true;
            res = true;
        }

        if (current_factor_timer.poll())
        {
            factor_timer_exceeded = true;
            res = true;
        }
        if (res){
            current_factor_timer.stop();
            overall_timer.stop();
        }
        return res;
    }
    void stop()
    {
        overall_timer.stop();
        current_factor_timer.stop();
    }
};