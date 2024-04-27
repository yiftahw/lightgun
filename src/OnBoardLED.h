#pragma once

#include <Arduino.h>

class OnBoardLED
{
public:
    OnBoardLED() = default;
    ~OnBoardLED() = default;

    void setup()
    {
        pinMode(LED_PIN, OUTPUT);
    }

    void on()
    {
        state = true;
        update();
    }

    void off()
    {
        state = false;
        update();
    }

    void toggle()
    {
        state = !state;
        update();
    }

private:
    bool state = false;
    void update()
    {
        digitalWrite(LED_PIN, state ? HIGH : LOW);
    }
    static inline constexpr uint8_t LED_PIN = 2; // GPIO2
};
