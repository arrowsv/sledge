#include "patch/rfg/xml.hpp"
#include "patch/lua/events/xml.hpp"
#include "patch/lua/manager.hpp"
#include "patch/rfg/memory.hpp"
#include "patch/rfg/os/file.hpp"
#include "patch/utils/hook.hpp"

#include <plog/Log.h>
#include <pugixml.hpp>
#include <string>

namespace hooks::xml {
HOOK_FUNC(0x005cd2f0, rfg::xml_element*, __cdecl, xml_parse, const char* file_name,
          rfg::mempool_base* dest) {
    if (!file_name)
        return xml_parse_original(file_name, dest);

    if (!lua::manager::get().has_event_subscriber(lua::events::event::parse_xml, file_name))
        return xml_parse_original(file_name, dest);

    rfg::cfile* file = rfg::open_table_file(file_name);

    if (!file) {
        PLOG_ERROR << "Failed to open table file '" << file_name << "'.";
        return xml_parse_original(file_name, dest);
    }

    size_t size = file->size;
    if (!size) {
        PLOG_ERROR << "Failed to get size of table file '" << file_name << "'.";
        rfg::cf_close(file);
        return xml_parse_original(file_name, dest);
    }

    std::vector<char> raw_buffer(size + 1, 0);
    rfg::cf_read(raw_buffer.data(), size, file, 0);
    rfg::cf_close(file);

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_buffer(raw_buffer.data(), size);
    if (!result) {
        PLOG_ERROR << "Failed to parse table file '" << file_name << "'.";
        return xml_parse_original(file_name, dest);
    }

    lua::manager::get().trigger_event(lua::events::event::parse_xml,
                                      lua::events::xml_parse_event(file_name, &document),
                                      file_name);

    std::stringstream stream;
    document.save(stream, "	", pugi::format_default | pugi::format_no_declaration);
    std::string modified_xml = stream.str();

    char* file_buffer = (char*)dest->alloc(modified_xml.size() + 1, 4);
    if (!file_buffer)
        return xml_parse_original(file_name, dest);

    std::memcpy(file_buffer, modified_xml.data(), modified_xml.size());
    file_buffer[modified_xml.size()] = '\0';

    rfg::xml_element* root = rfg::xml_parse_from_string(file_buffer, dest, file_name);
    if (root)
        return root;

    PLOG_ERROR << "Failed to parse modified table file '" << file_name << "'. Using default.";
    return xml_parse_original(file_name, dest);
}

void apply() { xml_parse_apply(); }
} // namespace hooks::xml
