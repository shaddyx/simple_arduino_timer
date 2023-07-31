//#include <Arduino.h>
#include <ArduinoFake.h>
#include <timerlib/multi_factor_timer.h>
#include <unity.h>

using namespace fakeit;
MultiFactorTimer<2> multiFactorTimer;
void first_factor(){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10);
    multiFactorTimer.set_factor_timer(0, 100);
    multiFactorTimer.set_factor_timer(1, 200);
    multiFactorTimer.run(500);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_TRUE(multiFactorTimer.poll());
    TEST_ASSERT_EQUAL(0, multiFactorTimer.get_current_factor());
    TEST_ASSERT_TRUE(multiFactorTimer.factor_exceeded());
    TEST_ASSERT_FALSE(multiFactorTimer.overall_exceeded());
}


void second_factor(){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10);
    multiFactorTimer.set_factor_timer(0, 100);
    multiFactorTimer.set_factor_timer(1, 200);
    multiFactorTimer.run(500);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    multiFactorTimer.next_factor();
    TEST_ASSERT_EQUAL(1, multiFactorTimer.get_current_factor());
    multiFactorTimer.next_factor();
    TEST_ASSERT_EQUAL(1, multiFactorTimer.get_current_factor());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(300);
    TEST_ASSERT_TRUE(multiFactorTimer.poll());
    TEST_ASSERT_TRUE(multiFactorTimer.factor_exceeded());
    TEST_ASSERT_FALSE(multiFactorTimer.overall_exceeded());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1000);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    TEST_ASSERT_TRUE(multiFactorTimer.factor_exceeded());
    TEST_ASSERT_FALSE(multiFactorTimer.overall_exceeded());
}

void overall_factor(){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10);
    multiFactorTimer.set_factor_timer(0, 200);
    multiFactorTimer.set_factor_timer(1, 500);
    multiFactorTimer.run(500);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    multiFactorTimer.next_factor();
    When(Method(ArduinoFake(), millis)).AlwaysReturn(400);
    TEST_ASSERT_FALSE(multiFactorTimer.poll());
    TEST_ASSERT_FALSE(multiFactorTimer.factor_exceeded());
    TEST_ASSERT_FALSE(multiFactorTimer.overall_exceeded());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(520);
    TEST_ASSERT_TRUE(multiFactorTimer.poll());
    TEST_ASSERT_FALSE(multiFactorTimer.factor_exceeded());
    TEST_ASSERT_TRUE(multiFactorTimer.overall_exceeded());
}

void setUp(void)
{
    ArduinoFakeReset();
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(first_factor);
    RUN_TEST(second_factor);
    RUN_TEST(overall_factor);
    UNITY_END();
    return 0;
}