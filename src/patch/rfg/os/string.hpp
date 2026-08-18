#pragma once

#include <sol/forward.hpp>

namespace rfg {
struct checksum_string {
    unsigned int checksum;
};

struct checksum_string_pair {
    const char* string;
    checksum_string string_checksum;
};
} // namespace rfg