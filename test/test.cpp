#include <Arduino.h>
#include <Assistant.h>
#include <unity.h>

class TAssistant : public Assistant {
    void _setup() {
        state = 1;
    };
    void _loop() {
        state = 2;
    };

   public:
    int state = 0;
};

void test_Assistant_direct(void) {
    TEST_ASSERT_EQUAL(0, TAssistant::getAssistantCount());
    TAssistant A;
    TEST_ASSERT_EQUAL(1, TAssistant::getAssistantCount());
    TEST_ASSERT_EQUAL(0, A.state);

    A.loop();  // loop not possible before setup
    TEST_ASSERT_EQUAL(0, A.state);

    A.setup();
    TEST_ASSERT_EQUAL(1, A.state);
    A.loop();
    TEST_ASSERT_EQUAL(2, A.state);

    A.setup();  // setup only possible once
    TEST_ASSERT_EQUAL(2, A.state);
}

void test_Assistant_global(void) {
    TEST_ASSERT_EQUAL(0, TAssistant::getAssistantCount());
    TAssistant A;
    TEST_ASSERT_EQUAL(1, TAssistant::getAssistantCount());
    TEST_ASSERT_EQUAL(0, A.state);

    Assistant::loopAll();  // loop not possible before setup
    TEST_ASSERT_EQUAL(0, A.state);

    Assistant::setupAll();
    TEST_ASSERT_EQUAL(1, A.state);
    Assistant::loopAll();
    TEST_ASSERT_EQUAL(2, A.state);

    Assistant::setupAll();  // setup only possible once
    TEST_ASSERT_EQUAL(2, A.state);
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(test_Assistant_direct);
    RUN_TEST(test_Assistant_global);
    UNITY_END();
}

void setup() {
    delay(2000);

    process();
}

void loop() {
    delay(1000);
}
