#pragma once

#include <stdint.h>

#define IR_POINTS_RAW_SIZE 5

#define Y1_MSB_BITMASK 0b11000000
#define X1_MSB_BITMASK 0b00110000
#define Y2_MSB_BITMASK 0b00001100
#define X2_MSB_BITMASK 0b00000011

#define Y1_MSB_SHIFT (8 - 6)
#define X1_MSB_SHIFT (8 - 4) 
#define Y2_MSB_SHIFT (8 - 2) 
#define X2_MSB_SHIFT (8 - 0) 

/**
 * @brief the data received from the DFRobot IR camera regarding 2 points
 * @note the camera can detect up to 4 points, in this case it will send 10 bytes (2 points * 5 bytes)
 * @note described from bit 7 (left) to bit 0 (right)
 * @note - byte 0: x1 <7:0>
 * @note - byte 1: y1 <7:0>
 * @note - byte 2: y1<9:8> x1<9:8> y2<9:8> x2<9:8>
 * @note - byte 3: x2 <7:0>
 * @note - byte 4: y2 <7:0>
 */
struct ir_points_raw_t
{
    uint8_t data[IR_POINTS_RAW_SIZE];
};

struct point_t
{
    uint16_t x;
    uint16_t y;
};

struct ir_points_parsed_t
{
    point_t point1;
    point_t point2;
};

ir_points_parsed_t parse_ir_points(const ir_points_raw_t &raw_points);
