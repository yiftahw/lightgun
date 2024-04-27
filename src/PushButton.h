#pragma once

#include <Arduino.h>

/**
 * @brief a simple push button handler that uses the internal pull-up resistor
 * 
 */
class PushButton
{
public:
    PushButton(uint8_t pin) : pin(pin) 
    {
        // empty
    }
    ~PushButton() = default;

    bool isPressed()
    {
        return digitalRead(pin) == LOW;
    }

    void setup()
    {
        pinMode(pin, INPUT_PULLUP);
    }

private:
    uint8_t pin;
};
