#pragma once

#include <sol/forward.hpp>

namespace rfg {
struct timestamp {
    int value;
};

struct timestamp_percent : timestamp {
    int set_milliseconds;
};

} // namespace rfg