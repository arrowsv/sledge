#include "memory.hpp"

#include <errhandlingapi.h>
#include <memoryapi.h>
#include <plog/Log.h>

namespace utils::memory {
void write_bytes(uintptr_t offset, const void* data, uint32_t size) {
    DWORD old_protect;
    uintptr_t address = utils::address::convert(offset);

    if (!VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE,
                        &old_protect)) {
        PLOG_WARNING << "VirtualProtect failed: " << GetLastError();
    }

    std::memcpy(reinterpret_cast<void*>(address), data, size);
    VirtualProtect(reinterpret_cast<void*>(address), size, old_protect, nullptr);
}
} // namespace utils::memory
