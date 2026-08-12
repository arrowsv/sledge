#pragma once

#include <sol/forward.hpp>

namespace rfg {
struct checksum_string {
    unsigned int checksum;
};
void bind_checksum_string(sol::state_view& lua);

struct checksum_string_pair {
    const char* string;
    checksum_string string_checksum;
};
void bind_checksum_string_pair(sol::state_view& lua);
} // namespace rfg