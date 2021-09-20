#ifndef AA_Assistant
#define AA_Assistant

#include <LinkedList.h>

#define BUFFER_MAX_LEN 512

#define STATUS_ETH 0
#define STATUS_MQTT 1

#define ASSERT_ERR(condition, message) \
    if (!(condition)) printer->err(__BASE_FILE__ + (String) " at " + __LINE__ + ": " + message)
#define ASSERT_WARN(condition, message, execute)                                    \
    if (!(condition)) {                                                             \
        printer->warn(__BASE_FILE__ + (String) " at " + __LINE__ + ": " + message); \
        execute;                                                                    \
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
    String buffer = "";
    virtual void msg(String message) {
        if (buffer.length() < BUFFER_MAX_LEN)
            buffer += message + "\n";
    };
    virtual void warn(String message) { msg(message); };
    virtual void err(String message) { msg(message); };
};

extern AssistantPrinter *printer;

class SerialAssistantPrinter : public AssistantPrinter, public Assistant {
   public:
    SerialAssistantPrinter() {
        buffer = printer->buffer;
#if defined(ESP8266) || defined(ESP32)
        printer->buffer.clear();
#else
        printer->buffer = "";
#endif
        printer = this;
    }
    void _setup() {
        _loop();
    }
    void _loop() {
        if (buffer && Serial) {
            Serial.print(buffer);
            buffer = "";
        }
    }
};

#endif
