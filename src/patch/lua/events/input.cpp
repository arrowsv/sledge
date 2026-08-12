#include "input.hpp"
#include "common/utils/os.hpp"

#include <sol/sol.hpp>

namespace lua::events {
sol::table key_up_event::to_table(sol::state_view& lua) const {
    auto table = lua.create_table();
    table["key"] = key;
    table["shift_down"] = shift_down;
    table["control_down"] = control_down;
    table["alt_down"] = alt_down;
    return table;
}

sol::table key_down_event::to_table(sol::state_view& lua) const {
    auto table = lua.create_table();
    table["key"] = key;
    table["shift_down"] = shift_down;
    table["control_down"] = control_down;
    table["alt_down"] = alt_down;
    return table;
}

sol::table mouse_wheel_event::to_table(sol::state_view& lua) const {
    auto table = lua.create_table();
    table["delta"] = delta;
    table["shift_down"] = shift_down;
    table["control_down"] = control_down;
    table["alt_down"] = alt_down;
    return table;
}

} // namespace lua::events
