#pragma once

#include <cstdint>

namespace utils::address {
#define OFFSET(gog, steam) ::utils::address::offset(gog, steam)
struct offset {
    uintptr_t gog;
    uintptr_t steam;

    offset(uintptr_t gog, uintptr_t steam) : gog(gog), steam(steam) {}
};
uintptr_t convert(utils::address::offset val);
} // namespace utils::address
