#pragma once

#include <LinkedList.h>

class Assistant {
   public:
    Assistant();
    virtual ~Assistant();
    void setup();
    void loop();

   private:
    bool is_setup;
    virtual void _setup() = 0;
    virtual void _loop() = 0;

    static LinkedList<Assistant> List;
    static uint16_t AssistantCount;

   public:
    static void setupAll();
    static void loopAll();
    static uint16_t getAssistantCount();
};
