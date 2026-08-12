#pragma once

#include <cstdint>

namespace utils::address {
struct offset {
    uintptr_t gog;
    uintptr_t steam;

    offset(uintptr_t gog, uintptr_t steam) : gog(gog), steam(steam) {}
};
// uintptr_t convert(utils::address::offset offset);
uintptr_t convert(uintptr_t offset);
} // namespace utils::address
