#include "xml.hpp"

#include <sol/sol.hpp>

namespace lua::events {
sol::table xml_parse_event::to_table(sol::state_view& lua) const {
    auto root_node = document->root();
    auto table = lua.create_table();
    table["name"] = name;
    table["document"] = &root_node;
    return table;
}
} // namespace lua::events
