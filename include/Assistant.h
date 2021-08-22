#ifndef AA_Assistant
#define AA_Assistant

#include <LinkedList.h>

#define STATUS_ETH 0
#define STATUS_MQTT 1

#define ASSERT_ERR(condition, message) \
    if (!(condition)) printer->err(__FILE__ + (String) " at " + __LINE__ + ": " + message)
#define ASSERT_WARN(condition, message, execute)                               \
    if (!(condition)) {                                                        \
        printer->warn(__FILE__ + (String) " at " + __LINE__ + ": " + message); \
        execute;                                                               \
    }

#define MSG(message) printer->msg(message)
#define WARN(message) printer->warn(message)
#define ERR(message) printer->err(message)

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

class AssistantPrinter {
   public:
    virtual void msg(String mesage){};
    virtual void warn(String mesage) { msg(mesage); };
    virtual void err(String mesage) { msg(mesage); };
};

extern AssistantPrinter *printer;

#endif
