#include "DataAcquisition.h"
#include <cstdio>

ir_points_parsed_t parse_ir_points(const ir_points_raw_t &raw_points)
{
    ir_points_parsed_t parsed = {0};
    parsed.point1.x = (raw_points.data[0]) | ((raw_points.data[2] & X1_MSB_BITMASK) << X1_MSB_SHIFT);
    parsed.point1.y = (raw_points.data[1]) | ((raw_points.data[2] & Y1_MSB_BITMASK) << Y1_MSB_SHIFT);
    parsed.point2.x = (raw_points.data[3]) | ((raw_points.data[2] & X2_MSB_BITMASK) << X2_MSB_SHIFT);
    parsed.point2.y = (raw_points.data[4]) | ((raw_points.data[2] & Y2_MSB_BITMASK) << Y2_MSB_SHIFT);
    return parsed;
}
