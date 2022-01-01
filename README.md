## Small header only timer library for arduino

Usage (interval):
```cpp

#include "timerlib/simple_timer.h"

SmallTimer updateTimer;

void setup(){
    updateTimer.set(10);    // blink every 10 ms
}

void loop(){
    if (updateTimer.interval()){
        //... blink code
    }
}

```


Usage (once):
```cpp

#include "timerlib/simple_timer.h"

SmallTimer updateTimer;

void setup(){
    updateTimer.set(10);    // blink once in 10 ms
}

void loop(){
    if (updateTimer.poll()){
        //... blink code
    }
}

```