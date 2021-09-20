#include <Arduino.h>
#include <Assistant.h>

LinkedList<Assistant> Assistant::List;

AssistantPrinter _DefaultPrinter;
AssistantPrinter* printer = &_DefaultPrinter;

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

// -------------------------------------------------------------------------------- AssistantKeys
uint16_t Assistant::AssistantKeys = 0;
void Assistant::setAssistantKey(uint16_t key, bool value) {
    if (bitRead(AssistantKeys, key) != value) {
        bitWrite(AssistantKeys, key, value);
        Serial.print("KEYCHANGE: ");
        for (uint8_t i = 0; i < 4; i++)
            Serial.print(Assistant::getAssistantKey(i));
        Serial.print("\n");
    }
}

bool Assistant::getAssistantKey(uint16_t key) {
    return bitRead(AssistantKeys, key);
}