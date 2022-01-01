#pragma once
#include <Arduino.h>

class SimpleTimer {
    public:
        SimpleTimer(){
        }
        
        SimpleTimer(long ms){
            set(ms);
        }

        SimpleTimer(long ms, bool immediately){
            if (immediately){
                set_immediately(ms);
            }
        }

        void set(long ms){
            start = millis();
            started = true;
            this->ms = ms;
        }
        int time_last(){
            if (!started){
                return 0;
            }
            return millis() - start;
        }
        bool poll(){
            auto res = started && (millis() - start >= ms);
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
            this -> start = millis() - ms;
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