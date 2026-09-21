#pragma once

#include <cstdint>

#define OFFSET(gog, steam) ::utils::address::offset(gog, steam)

namespace utils::address {
    struct offset {
        uintptr_t gog;
        uintptr_t steam;

        offset(uintptr_t gog, uintptr_t steam) : gog(gog), steam(steam) {}
    };
    uintptr_t convert(utils::address::offset val);
}
