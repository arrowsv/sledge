#include "patch/rfg/player.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {
void bind_player(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto player =
        types.new_usertype<::rfg::player>("player", sol::no_constructor, sol::base_classes,
                                          sol::bases<::rfg::human, ::rfg::object>());
    player["aim_target"] = sol::readonly(&::rfg::player::aim_target);
    player["jetpack_fuel_percent"] = &::rfg::player::jetpack_fuel_percent;
    player["movement_velocity"] = &::rfg::player::movement_velocity;
    player["last_vehicle_driven"] = sol::readonly(&::rfg::player::last_vehicle_driven);
    player["radiation_damage"] = &::rfg::player::radiation_damage;
    player["salvage"] =
        sol::property([](::rfg::player& self) { return self.meta_data.salvage; },
                      [](::rfg::player& self, int value) { self.meta_data.salvage = value; });
    player["mining_count"] =
        sol::property([](::rfg::player& self) { return self.meta_data.mining_count; },
                      [](::rfg::player& self, int value) { self.meta_data.mining_count = value; });
    player["supply_crate_count"] = sol::property(
        [](::rfg::player& self) { return self.meta_data.supply_crate_count; },
        [](::rfg::player& self, int value) { self.meta_data.supply_crate_count = value; });
    player["play_time"] =
        sol::readonly_property([](::rfg::player& self) { return self.meta_data.play_time; });
}
} // namespace lua::bindings::rfg
