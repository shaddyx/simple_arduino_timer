#pragma once
#include <Arduino.h>

class SimpleMicroTimer {
    public:
        SimpleMicroTimer(){
        }
        
        SimpleMicroTimer(long ms){
            set(ms);
        }

        SimpleMicroTimer(long ms, bool immediately){
            if (immediately){
                set_immediately(ms);
            }
        }

        void set(long ms){
            start = micros();
            started = true;
            this->ms = ms;
        }
        unsigned long time_last(){
            if (!started){
                return 0;
            }
            return micros() - start;
        }
        bool poll(){
            auto res = started && (micros() - start >= ms);
            if (res){
                started = false;
            }
            return res;
        }
        
        void stop(){
            started = false;
        }

        bool is_started(){
            return started;
        }

        void set_immediately(long ms){
            set(ms);
            this -> start = micros() - ms;
        }

        bool interval(){
            auto res = poll();
            if (res){
                set(ms);
            }
            return res;
        }
    private:
        bool started = false;
        unsigned long start = 0;
        unsigned long ms = 0;
};