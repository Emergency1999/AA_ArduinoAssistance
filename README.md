# Arduino Assisstance
The base library for all Assistances.
This system gives an easy way of setting up and looping multible different instances.

# USAGE
```c++
xAssistant A;
xAssistant B;
xAssistant C;

void setup() {
    A.setup(); // setup of A is called
    A.loop();  // loop of A is called
    B.loop();  // loop is not called as B is not yet set up
    Assistant::setupAll(); // setup of B and C is called, as A is already set up
}
void loop() {
    Assistant::loopAll(); // loop of all Assistances are called as they're all set up
}

```

# IMPLEMENTAITION
To create a new assistant simply override the _setup and _loop functions like this: 
```c++
class xAssistant: public Assistant {
    void _setup() override {
        // setup code
    };
    void _loop() override {
        // loop code
    };
}

```
