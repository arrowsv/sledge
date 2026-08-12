#include "player.hpp"

#include <sol/sol.hpp>

namespace lua::events {
sol::table player_do_frame_event::to_table(sol::state_view& lua) const {
    auto table = lua.create_table();
    table["player"] = sol::make_reference(lua, player);
    return table;
}

sol::table alert_level_changed_event::to_table(sol::state_view& lua) const {
    auto table = lua.create_table();
    table["previous_alert_level"] = previous_alert_level;
    table["new_alert_level"] = new_alert_level;
    return table;
}
} // namespace lua::events
