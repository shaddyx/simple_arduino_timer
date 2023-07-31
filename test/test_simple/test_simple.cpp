//#include <Arduino.h>
#include <ArduinoFake.h>
#include <timerlib/simple_timer.h>
#include <unity.h>

using namespace fakeit;

void first_factor(){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    SimpleTimer simpleTimer(100);
    TEST_ASSERT_FALSE(simpleTimer.poll());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_TRUE(simpleTimer.poll());
}

void simple_interval(){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    SimpleTimer simpleTimer(100);
    TEST_ASSERT_FALSE(simpleTimer.interval());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_TRUE(simpleTimer.interval());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(210);
    TEST_ASSERT_FALSE(simpleTimer.interval());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(300);
    TEST_ASSERT_TRUE(simpleTimer.interval());
}


void setUp(void)
{
    ArduinoFakeReset();
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(first_factor);
    RUN_TEST(simple_interval);
    UNITY_END();
    return 0;
}