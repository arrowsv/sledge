#pragma once

#include "patch/utils/memory.hpp"

namespace rfg {
REF_FUNC(get_crc32_from_string, uint32_t __cdecl(const char* p_string),
         OFFSET(0x00bef100, 0x00bef4c0));
REF_FUNC(get_crc32_from_buffer, uint32_t __cdecl(void const* p_buffer, uint32_t length),
         OFFSET(0x00bef130, 0x00bef4f0));
} // namespace rfg
