#include <Arduino.h>
#include <Wire.h>

#include <string>

#include "PushButton.h"
#include "OnBoardLED.h"
#include "IRCamera.h"

void print(std::array<Point, 4> data)
{
    for (uint32_t i = 0; i < 4; i++)
    {
        Serial.print("Point ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(data[i].to_string().c_str());
    }
    Serial.flush();
}

// globals
const uint8_t BUTTON_PIN = 13; // GPIO13
const uint8_t I2C_DATA_PIN = 21; // GPIO21
const uint8_t I2C_CLOCK_PIN = 22; // GPIO22
const uint8_t CAMERA_I2C_ADDRESS = 0x58;

PushButton button(BUTTON_PIN);
IRCamera camera(I2C_DATA_PIN, I2C_CLOCK_PIN, CAMERA_I2C_ADDRESS);

void discover_i2c()
{
    // discover any i2c devices
    Wire.begin(I2C_DATA_PIN, I2C_CLOCK_PIN);
    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
}

void setup() 
{
    Serial.begin(115200); // initialize serial communication
    button.setup();
    camera.setup();
}

void loop() 
{
    if (button.isPressed())
    {
        Serial.println("Button is pressed");
        auto result = camera.snapshot();
        print(result);
        delay(1000); // 1s delay
    }
    delay(100); // 100ms delay

}
