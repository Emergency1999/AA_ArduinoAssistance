#ifndef AA_Assistant
#define AA_Assistant

#include <LinkedList.h>

#define STATUS_ETH 0
#define STATUS_MQTT 1

class Assistant {
   public:
    Assistant();
    virtual ~Assistant();
    void setup();
    void loop();

   private:
    bool is_setup;
    virtual void _loop() = 0;
    virtual void _setup() = 0;

    static LinkedList<Assistant> List;
    static uint16_t AssistantKeys;
    static uint16_t AssistantCount;

   public:
    static void setupAll();
    static void loopAll();
    static void setAssistantKey(uint16_t key, bool value);
    static bool getAssistantKey(uint16_t key);
    static uint16_t getAssistantCount();
};

#endif
