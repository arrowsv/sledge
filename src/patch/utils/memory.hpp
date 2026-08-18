#pragma once

#include "address.hpp"
#include <utility>

namespace utils::memory {
#define REF_VAR(name, type, offset)                                                                   \
    inline type* name() { return reinterpret_cast<type*>(::utils::address::convert(offset)); }

#define REF_FUNC(name, signature, offset)                                                             \
    template <typename... Args> inline auto name(Args&&... args) {                                 \
        using fn_type = signature;                                                                 \
        return reinterpret_cast<fn_type*>(::utils::address::convert(offset))(                 \
            std::forward<Args>(args)...);                                                          \
    }

void write_bytes(utils::address::offset offset, const void* data, uint32_t size);

template <typename T> void write_value(utils::address::offset offset, T value) {
    write_bytes(offset, reinterpret_cast<const void*>(&value), sizeof(T));
}
} // namespace utils::memory
