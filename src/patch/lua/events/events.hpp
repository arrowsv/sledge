#pragma once

#include "common/mods.hpp"

#include <sol/sol.hpp>
#include <string>

namespace lua::events {
enum class event {
    game_do_frame,
    player_do_frame,
    alert_level_changed,
    save_loaded,
    key_down,
    key_up,
    mouse_wheel,
    parse_xml,
};

struct event_callback {
    std::string id;
    std::optional<std::string> filter;
    mods::mod_info mod_info;
    sol::protected_function function;
};

struct event_context {
    virtual ~event_context() = default;
    virtual sol::table to_table(sol::state_view& lua) const;
};
} // namespace lua::events
