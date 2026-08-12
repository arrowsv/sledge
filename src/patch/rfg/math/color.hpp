#pragma once

#include <cstdint>

namespace rfg {
struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct color_float // rl_color_float
{
    float red;
    float green;
    float blue;
    float alpha;
};

} // namespace rfg
