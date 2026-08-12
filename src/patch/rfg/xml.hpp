#pragma once

#include "patch/rfg/memory.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {
struct xml_element {
    const char* name;
    struct xml_element* next;
    struct xml_element* elements;
    char* text;
};

REF_FUNC(xml_parse_from_string,
         xml_element* __cdecl(char* buffer, void* dest, const char* file_name_original),
         0x005bf870);
REF_VAR(g_xml_mempool, rfg::mempool_base*, 0x01ce77dc);

} // namespace rfg
