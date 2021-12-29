#include <Arduino.h>
#include <Assistant.h>

LinkedList<Assistant> Assistant::List;

Assistant::Assistant() : is_setup(false) {
    List << this;
    AssistantCount++;
}

Assistant::~Assistant() {
    List >> this;
    AssistantCount--;
}

// -------------------------------------------------------------------------------- setup
void Assistant::setup() {
    if (!is_setup) {
        is_setup = true;
        _setup();
    }
}

void Assistant::setupAll() {
    List.forEach([](int i, Assistant* A) {
        A->setup();
    });
}

// -------------------------------------------------------------------------------- loop
void Assistant::loop() {
    if (is_setup) _loop();
}

void Assistant::loopAll() {
    List.forEach([](int i, Assistant* A) {
        A->loop();
    });
}
// -------------------------------------------------------------------------------- AssistantCount
uint16_t Assistant::AssistantCount = 0;
uint16_t Assistant::getAssistantCount() {
    return AssistantCount;
}
