#include "weapon.hpp"
#include "patch/rfg/player.hpp"

#include <sol/sol.hpp>

namespace lua::events {
sol::table weapon_fire_event::to_table(sol::state_view& lua) const {
    bool player_weapon = rfg::get_local_player()->handle == weapon->owner_handle;

    auto table = lua.create_table();
    table["weapon"] = sol::make_reference(lua, weapon);
    table["player_weapon"] = player_weapon;
    return table;
}
} // namespace lua::events
