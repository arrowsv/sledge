#include "patch/rfg/world.hpp"

#include <sol/sol.hpp>

namespace rfg {
void bind_world_functions(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table["get_world"] = []() { return rfg::g_world(); };
}

void bind_world_deserialize_state(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("world_deserialize_state", "idle", rfg::world_deserialize_state::DS_IDLE,
                   "pending", rfg::world_deserialize_state::DS_PENDING, "collect",
                   rfg::world_deserialize_state::DS_COLLECT, "compress",
                   rfg::world_deserialize_state::DS_COMPRESS, "save_finalize",
                   rfg::world_deserialize_state::DS_SAVE_FINALIZE);
}

void bind_world_state_mode(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("world_state_mode", "default", rfg::world_state_mode::WSM_DEFAULT, "checkpoint",
                   rfg::world_state_mode::WSM_CHECKPOINT);
}

void bind_world_zone_state(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("world_zone_state", "unloaded", rfg::world_zone_state::WZS_UNLOADED, "streaming",
                   rfg::world_zone_state::WZS_STREAMING, "loaded",
                   rfg::world_zone_state::WZS_LOADED);
}

void bind_save_load_info(sol::state_view& lua) {}

void bind_district_flags(sol::state_view& lua) {}

void bind_nav_cell(sol::state_view& lua) {}

void bind_nav_cell_outer_edge(sol::state_view& lua) {}

void bind_bb_pfg_layer(sol::state_view& lua) {}

void bind_bb_pfg_zone(sol::state_view& lua) {}

void bind_obj_zone(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto obj_zone = table.new_usertype<rfg::obj_zone>("obj_zone", sol::no_constructor);
    //"zone_pfg", &rfg::obj_zone::zone_pfg,
    obj_zone["heightfield_shape"] = &rfg::obj_zone::heightfield_shape;
    obj_zone["stitch_piece_havok_handle"] = &rfg::obj_zone::stitch_piece_havok_handle;
    obj_zone["district_handle"] = &rfg::obj_zone::district_handle;
    //"spawn_res_data", &rfg::obj_zone::spawn_res_data,
    //"ambient_spawn_info", &rfg::obj_zone::ambient_spawn_info,
    obj_zone["wind_min_speed"] = &rfg::obj_zone::wind_min_speed;
    obj_zone["wind_max_speed"] = &rfg::obj_zone::wind_max_speed;
    //"terrain", &rfg::obj_zone::terrain,
    //"m_occluders", &rfg::obj_zone::m_occluders,
    obj_zone["local_bmin"] = &rfg::obj_zone::local_bmin;
    obj_zone["local_bmax"] = &rfg::obj_zone::local_bmax;
    obj_zone["aabb_phantom_index"] = &rfg::obj_zone::aabb_phantom_index;
}

void bind_handle_manager_7280(sol::state_view& lua) {}

void bind_world_state_buf(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto world_state_buf = table.new_usertype<rfg::world_state_buf>("world_state_buf");
    world_state_buf["player_start_pos"] = &rfg::world_state_buf::player_start_pos;
    world_state_buf["player_start_orient"] = &rfg::world_state_buf::player_start_orient;
    world_state_buf["player_start_pos_safehouse"] =
        &rfg::world_state_buf::player_start_pos_safehouse;
    world_state_buf["player_start_orient_safehouse"] =
        &rfg::world_state_buf::player_start_orient_safehouse;
    world_state_buf["buf"] = &rfg::world_state_buf::buf;
    world_state_buf["cur_size"] = &rfg::world_state_buf::cur_size;
    world_state_buf["max_size"] = &rfg::world_state_buf::max_size;
}

void bind_zone_header(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto world_zone_header = table.new_usertype<rfg::zone_header>("world_zone_header");
    world_zone_header["signature"] = &rfg::zone_header::signature;
    world_zone_header["version"] = &rfg::zone_header::version;
    world_zone_header["num_objects"] = &rfg::zone_header::num_objects;
    world_zone_header["num_handles"] = &rfg::zone_header::num_handles;
    world_zone_header["district_hash"] = &rfg::zone_header::district_hash;
    world_zone_header["flags"] = &rfg::zone_header::flags;
}

void bind_world_zone(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto world_zone = table.new_usertype<rfg::world_zone>("world_zone", sol::no_constructor);
    world_zone["bmin"] = &rfg::world_zone::bmin;
    world_zone["bmax"] = &rfg::world_zone::bmax;
    world_zone["name"] = &rfg::world_zone::name;
    world_zone["state"] = &rfg::world_zone::state;
    world_zone["deserialize_header"] = &rfg::world_zone::deserialize_header;
    //"deserialize_header_f", &rfg::world_zone::deserialize_header_f,
    //"deserialize_f", &rfg::world_zone::deserialize_f,
    world_zone["stored_zone_state"] = &rfg::world_zone::stored_zone_state;
    //"zone_objp", &rfg::world_zone::zone_objp,
    world_zone["srid"] = &rfg::world_zone::srid;
    world_zone["is_border_zone"] = &rfg::world_zone::is_border_zone;
    //"obj_handle_mgr", &rfg::world_zone::obj_handle_mgr,
    world_zone["gid"] = &rfg::world_zone::gid;
}

void bind_grid_info_flags(sol::state_view& lua) {}

void bind_grid_info(sol::state_view& lua) {}

void bind_district(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto district =
        table.new_usertype<rfg::district>("district", sol::base_classes, sol::bases<rfg::object>());
    district["control"] = &rfg::district::control;
    district["morale"] = &rfg::district::morale;
    district["control_max"] = &rfg::district::control_max;
    district["morale_max"] = &rfg::district::morale_max;
    district["liberated_tech_level"] = &rfg::district::liberated_tech_level;
    district["liberated_marauder_level"] = &rfg::district::liberated_marauder_level;
    district["liberated_edf_level"] = &rfg::district::liberated_edf_level;
    district["liberated_radio_line_handle"] = &rfg::district::liberated_radio_line_handle;
    district["capstone_line_1"] = &rfg::district::capstone_line_1;
    district["capstone_line_2"] = &rfg::district::capstone_line_2;
    district["min_edf_progression_level"] = &rfg::district::min_edf_progression_level;
    district["liberated"] = &rfg::district::liberated;
    district["needs_to_play_radio_line"] = &rfg::district::needs_to_play_radio_line;
    district["flags"] = &rfg::district::flags;
    district["color"] = &rfg::district::color;
    district["localized_name_hash"] = &rfg::district::localized_name_hash;
    //"grid_ids", &rfg::district::grid_ids,
    district["district_index"] = &rfg::district::district_index;
    district["vfx_tint"] = &rfg::district::vfx_tint;
    //"load_screen_images", &rfg::district::load_screen_images,
    // district["num_load_screen_images"] = &rfg::district::num_load_screen_images;
}

void bind_t_district(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto territory_district = table.new_usertype<rfg::t_district>("territory_district");
    territory_district["name"] =
        sol::property([](rfg::t_district& self) { return std::string(self.name); });
    territory_district["liberated_radio_line"] = &rfg::t_district::liberated_radio_line;
    // territory_district["localized_name_hash"] = &rfg::t_district::localized_name_hash;
    // territory_district["localized_name_hash_no_ar"] =
    // &rfg::t_district::localized_name_hash_no_ar;
    territory_district["control"] = &rfg::t_district::control;
    territory_district["control_max"] = &rfg::t_district::control_max;
    territory_district["morale"] = &rfg::t_district::morale;
    territory_district["morale_max"] = &rfg::t_district::morale_max;
    territory_district["tech_level"] = &rfg::t_district::tech_level;
    territory_district["marauder_level"] = &rfg::t_district::marauder_level;
    territory_district["edf_level"] = &rfg::t_district::edf_level;
    territory_district["edf_progression_level"] = &rfg::t_district::edf_progression_level;
    territory_district["liberated"] = &rfg::t_district::liberated;
    territory_district["flags"] = &rfg::t_district::flags;
    territory_district["color"] = &rfg::t_district::color;
    territory_district["vfx_tint"] = &rfg::t_district::vfx_tint;
    // territory_district["disc_layer"] = &rfg::t_district::disc_layer;
    territory_district["index"] = &rfg::t_district::index;
    // territory_district["thumbnail"] = &rfg::t_district::thumbnail;
    // territory_district["load_screen_images"] = &rfg::t_district::load_screen_images;
    // territory_district["num_load_screen_images"] = &rfg::t_district::num_load_screen_images;
    //"list", &rfg::t_district::list,
    territory_district["next"] = &rfg::t_district::next;
    territory_district["previous"] = &rfg::t_district::previous;
}

void bind_territory(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto territory = table.new_usertype<rfg::territory>("territory");
    territory["name"] = &rfg::territory::name;
    territory["tech_level_default"] = &rfg::territory::tech_level_default;
    territory["tech_level_max"] = &rfg::territory::tech_level_max;
    territory["index"] = &rfg::territory::index;
    territory["districts"] = &rfg::territory::districts;
    territory["vertical_mask_zones"] = &rfg::territory::vertical_mask_zones;
    territory["num_v_mask_zones"] = &rfg::territory::num_v_mask_zones;
    territory["horiz_mask_zones"] = &rfg::territory::horiz_mask_zones;
    territory["num_h_mask_zones"] = &rfg::territory::num_h_mask_zones;
}

void bind_world(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto world = table.new_usertype<rfg::world>("world", sol::no_constructor);
    world["mission_object_creation_mode"] = &rfg::world::mission_object_creation_mode;
    world["level_ambient"] = &rfg::world::level_ambient;
    world["level_back_ambient"] = &rfg::world::level_back_ambient;
    world["last_loaded_territory"] = &rfg::world::last_loaded_territory;
    world["max_world_objects"] = &rfg::world::max_world_objects;
    world["all_objects"] = &rfg::world::all_objects;
    // world["all_objects"] = sol::property([&lua](rfg::world &self) -> sol::table {
    //     //return lua_manager::utils::create_table(lua, &self.all_objects,
    //     self.all_objects.size()); auto all_objects = self.all_objects; int32_t count =
    //     all_objects.size();

    //     sol::table t = lua.create_table(count, 0);
    //     for (int32_t i = 0; i < count; ++i)
    //     {
    //         t[i + 1] = self.all_objects[i];
    //     }
    //     return t;
    // });
    //"type_objects", &rfg::world::type_objects,
    //"subtype_objects", &rfg::world::subtype_objects,
    world["tech_level"] = &rfg::world::tech_level;
    world["tech_level_max"] = &rfg::world::tech_level_max;
    //"thread_id", &rfg::world::thread_id,
    //"object_handle_hash", &rfg::world::object_handle_hash,
    //"destroyed_object_table", &rfg::world::destroyed_object_table,
    //"save_file", &rfg::world::save_file,
    // world["flagged_objects"] = &rfg::world::flagged_objects;
    // world["current_flagged_object"] = &rfg::world::current_flagged_object;
    //"current_flagged_mode", &rfg::world::current_flagged_mode,
    // world["deserialize_state"] = &rfg::world::deserialize_state;
    //"deserialize_pool", &rfg::world::deserialize_pool,
    //"deserialize_list", &rfg::world::deserialize_list,
    // world["cur_world_state"] = &rfg::world::cur_world_state;
    // world["stored_world_state"] = &rfg::world::stored_world_state;
    //"compress_stream", &rfg::world::compress_stream,
    //"decompress_stream", &rfg::world::decompress_stream,
    // world["save_load_flags"] = &rfg::world::sl_flags;
    //"pending_game_save_slot", &rfg::world::pending_game_save_slot,
    world["dlc_bundle_id"] = &rfg::world::dlc_bundle_id;
    // world["pending_filename"] = &rfg::world::pending_filename;
    world["pending_game_load_warp_to_pos"] = &rfg::world::pending_game_load_warp_to_pos;
    world["pending_game_load_warp_to_orient"] = &rfg::world::pending_game_load_warp_to_orient;
    //"load_aborted", &rfg::world::load_aborted,
    //"grid", &rfg::world::grid,
    world["stream_pos"] = &rfg::world::stream_pos;
    world["num_territory_zones"] = &rfg::world::num_territory_zones;
    // world["all_zones"] = &rfg::world::all_zones,
    world["global_zone_grid"] =
        sol::property([](rfg::world& self) { return std::ref(self.global_zone_grid); });
    world["is_territory"] = &rfg::world::is_territory;
    world["territory_name"] =
        sol::property([](rfg::world& self) { return std::string(self.territory_name); });
    world["num_streaming_objects"] = &rfg::world::num_streaming_objects;
    world["stub_serialization_in_progress"] = &rfg::world::stub_serialization_in_progress;
}
} // namespace rfg
