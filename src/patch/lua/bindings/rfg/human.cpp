
#include "human.hpp"
#include "patch/rfg/human.hpp"
#include "patch/lua/bindings/utils.hpp"
#include "patch/rfg/vehicle.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {

void bind_team(sol::state_view& lua) {
    auto defines = lua["defines"].get_or_create<sol::table>();

    auto team = defines.create_named("team");
    team["none"] = ::rfg::team::HUMAN_TEAM_NONE;
    team["guerrilla"] = ::rfg::team::HUMAN_TEAM_GUERILLA;
    team["edf"] = ::rfg::team::HUMAN_TEAM_EDF;
    team["civilian"] = ::rfg::team::HUMAN_TEAM_CIVILIAN;
    team["marauder"] = ::rfg::team::HUMAN_TEAM_MARAUDER;
}

void bind_human_info(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto human_info = types.new_usertype<::rfg::human_info>("human_info", sol::no_constructor);
    human_info["max_hit_points"] = &::rfg::human_info::max_hit_points;
    human_info["max_knockdown_hits"] = &::rfg::human_info::max_knockdown_hits;
    human_info["max_speed"] = &::rfg::human_info::max_speed;
    human_info["default_equip_item"] = &::rfg::human_info::default_equip_item;
    human_info["default_last_equip_item"] = &::rfg::human_info::default_last_equip_item;
    human_info["name"] = &::rfg::human_info::name;
    human_info["model_name"] = &::rfg::human_info::model_name;
    human_info["slot_id"] = &::rfg::human_info::slot_id;
    human_info["default_height_scale"] = &::rfg::human_info::default_height_scale;
    human_info["height_scale_variation"] = &::rfg::human_info::height_scale_variation;
    human_info["default_team"] = &::rfg::human_info::default_team;
    human_info["home_district"] = &::rfg::human_info::home_district;
    //"heads", &::rfg::human_info::heads,
    //"voice_personas", &::rfg::human_info::voice_personas,
    human_info["default_inventory"] = &::rfg::human_info::default_inventory;
    //"flags", &::rfg::human_info::flags
}

void bind_human_flags(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto human_flags = types.new_usertype<::rfg::human_flags>("human_flags", sol::no_constructor);
    // BIND_FLAG(human_flags, ::rfg::human_flags, locked_controller);
    BIND_FLAG(human_flags, ::rfg::human_flags, invulnerable);
    BIND_FLAG(human_flags, ::rfg::human_flags, no_damage);
    BIND_FLAG(human_flags, ::rfg::human_flags, ignored_by_ai);
    BIND_FLAG(human_flags, ::rfg::human_flags, disallow_vehicle_exit);
    BIND_FLAG(human_flags, ::rfg::human_flags, in_vehicle_invisible);
    BIND_FLAG(human_flags, ::rfg::human_flags, disallow_flinches_and_ragdolls);
}

void bind_human(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    bind_team(lua);
    bind_human_flags(lua);

    auto human = types.new_usertype<::rfg::human>("human", sol::no_constructor, sol::base_classes,
                                                  sol::bases<::rfg::object>());
    human["flags"] = &::rfg::human::flags;
    // human["info"] = &::rfg::human::info;
    human["hit_points"] = &::rfg::human::hit_points;
    // human["inventory"] = &::rfg::human::inventory;
    // human["vehicle_handle"] = &::rfg::human::vehicle_handle;
    human["team"] = &::rfg::human::current_team;
    human["undercover_team"] = &::rfg::human::undercover_team;

    human["teleport"] = [](::rfg::human& self, ::rfg::vector position) {
        ::rfg::vector pos = position;
        ::rfg::teleport_human(&self, &pos, &self.orient, 6.0f, 0);
    };
    // human["give_item"] = sol::overload(
    //     [](::rfg::human& self, const std::string& name, int count, int ammo_count, int slot,
    //        bool add_to_weapon_cabinet, bool show_inventory) {
    //         ::rfg::give_item_from_name(&self, name.c_str(), count, ammo_count, slot,
    //                                    add_to_weapon_cabinet, 0, show_inventory);
    //     },
    //     [](::rfg::human& self, uint32_t handle, int count, int ammo_count, int slot,
    //        bool add_to_weapon_cabinet, bool show_inventory) {
    //         ::rfg::give_item_from_inv_item_info(&self,
    //         ::rfg::get_inv_item_info_from_handle(handle),
    //                                             count, ammo_count, slot, add_to_weapon_cabinet,
    //                                             0, show_inventory);
    //     },
    //     [](::rfg::human& self, const std::string& name, int ammo_count) {
    //         ::rfg::give_item_from_name(&self, name.c_str(), 1, ammo_count, -1, 1, 0, 1);
    //     },
    //     [](::rfg::human& self, uint32_t handle, int ammo_count) {
    //         ::rfg::give_item_from_inv_item_info(&self,
    //         ::rfg::get_inv_item_info_from_handle(handle),
    //                                             1, ammo_count, -1, 1, 0, 1);
    //     });

    // human["enter_vehicle"] = [&lua](::rfg::human& self, ::rfg::vehicle& vehicle,
    //                                 sol::optional<sol::table> options) {
    //     sol::table options_table = options ? options.value() : lua.create_table();

    //     ::rfg::vehicle_enter_data enter_data{};

    //     enter_data.flags.teleport = options_table.get_or("teleport", false);
    //     enter_data.flags.teleport_to_door = options_table.get_or("teleport_to_door", false);
    //     enter_data.flags.walk = options_table.get_or("walk", false);

    //     enter_data.specified_seat =
    //         options_table.get_or("seat", ::rfg::vehicle_seat_index::VSI_DRIVER);
    //     enter_data.destination_seat = enter_data.specified_seat;

    //     // enter_data.specified_seat = ::rfg::VSI_DRIVER;
    //     enter_data.seat_selection_method = ::rfg::VI_SEAT_SELECTION_METHOD_SPECIFIED;
    //     // enter_data.destination_seat = ::rfg::VSI_DRIVER;
    //     // enter_data.flags.teleport = true;

    //     ::rfg::vehicle_request_enter(&self, &vehicle, &enter_data);
    // };

    // human["exit_vehicle"] = [&lua](::rfg::human& self, sol::optional<sol::table> options) {
    //     sol::table options_table = options ? options.value() : lua.create_table();

    //     ::rfg::vehicle_exit_data exit_data{};
    //     exit_data.flags.teleport = options_table.get_or("teleport", false);
    //     exit_data.flags.force_dive_exit = options_table.get_or("dive", false);

    //     ::rfg::vehicle_request_exit(&self, &exit_data);
    // };
}

} // namespace lua::bindings::rfg
