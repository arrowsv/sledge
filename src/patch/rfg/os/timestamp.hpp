#pragma once

#include <sol/forward.hpp>

namespace rfg {
struct timestamp {
    int value;
};
void bind_timestamp(sol::state_view& lua);

struct timestamp_percent : timestamp {
    int set_milliseconds;
};
void bind_timestamp_percent(sol::state_view& lua);

} // namespace rfg