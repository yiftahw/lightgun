#include <stdint.h>
#include <array>
#include <string>

struct Point
{
    uint16_t x;
    uint16_t y;

    std::string to_string() const
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};

struct Snapshot
{
    std::array<Point, 4> points;

    std::string to_string() const
    {
        std::string str = "[";
        for (const auto &point : points)
        {
            str += point.to_string() + ",";
        }
        str.pop_back(); // remove the last comma
        str += "]";
        return str;
    }
};


/**
 * @brief a handler for the DFRobot IR Camera
 * 
 */
class IRCamera
{
public:
    IRCamera(uint8_t sda_pin, uint8_t scl_pin, uint8_t camera_address);
    ~IRCamera() = default;

    void setup();

    Snapshot snapshot();

private:
    void Write_2bytes(uint8_t data1, uint8_t data2);

    uint8_t sda_pin;
    uint8_t scl_pin;
    uint8_t camera_address;
};
