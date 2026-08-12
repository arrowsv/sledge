#pragma once

#include "events.hpp"
#include <pugixml.hpp>

namespace lua::events
{
struct xml_parse_event : public event_context
{
    std::string name;
    pugi::xml_document *document;

    xml_parse_event(const std::string &name, pugi::xml_document *document) : name(name), document(document) {}

    sol::table to_table(sol::state_view &lua) const override;
};
} // namespace lua::events
