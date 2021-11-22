#pragma once
#include <Arduino.h>

class SmallTimer {
    public:
        void set(long ms){
            start = millis();
            started = true;
            this->ms = ms;
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