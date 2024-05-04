#include "IRCamera.h"

#include <Arduino.h>
#include <Wire.h>

static inline constexpr uint8_t X_MSB_SHIFT = 4;
static inline constexpr uint8_t Y_MSB_SHIFT = 2;
static inline constexpr uint8_t X_MSB_MASK = 0x30;
static inline constexpr uint8_t Y_MSB_MASK = 0xC0;

IRCamera::IRCamera(uint8_t sda_pin, uint8_t scl_pin, uint8_t camera_address)
    : sda_pin(sda_pin), scl_pin(scl_pin), camera_address(camera_address)
{
    // empty
}

void IRCamera::setup()
{
    Wire.begin(sda_pin, scl_pin);
    // sequence of commands to initialize the camera
    // taken fom the DFRobot wiki
    Write_2bytes(0x30, 0x01);
    Write_2bytes(0x30, 0x08);
    Write_2bytes(0x06, 0x90);
    Write_2bytes(0x08, 0xC0);
    Write_2bytes(0x1A, 0x40);
    Write_2bytes(0x33, 0x33);
    delay(100);
}

void IRCamera::Write_2bytes(uint8_t data1, uint8_t data2)
{
    Wire.beginTransmission(camera_address);
    Wire.write(data1);
    Wire.write(data2);
    Wire.endTransmission();
    delay(10);
}

Snapshot IRCamera::snapshot()
{
    std::array<uint8_t, 16> data = {0};
    Snapshot result;
    
    // sequence of commands to take a snapshot
    // taken from the DFRobot wiki

    Wire.beginTransmission(camera_address);
    Wire.write(0x36);
    Wire.endTransmission();

    uint8_t num_bytes = 16;
    Wire.requestFrom(camera_address, num_bytes);

    for (uint8_t i = 0; i < 16; i++)
    {
        if (!Wire.available())
        {
            break;
        }
        data[i] = Wire.read();
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t x_idx = (i * 3) + 1;
        uint8_t y_idx = (i * 3) + 2;
        uint8_t msb_idx = (i * 3) + 3;

        result.points[i].x = (data[x_idx]) | ((data[msb_idx] & X_MSB_MASK) << X_MSB_SHIFT);
        result.points[i].y = (data[y_idx]) | ((data[msb_idx] & Y_MSB_MASK) << Y_MSB_SHIFT);
    }

    return result;
}
