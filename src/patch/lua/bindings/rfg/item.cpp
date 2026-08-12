// #include "patch/rfg/item.hpp"
// #include "patch/rfg/weapon.hpp"
// #include <sol/sol.hpp>

// namespace rfg
// {
// void bind_inventory_item_info(sol::state_view &lua)
// {
//     auto inventory_item_info = lua["game"].get_or_create<sol::table>().new_usertype<rfg::inventory_item_info>(
//         "inventory_item_info", sol::no_constructor);
//     inventory_item_info["name"] = &rfg::inventory_item_info::name;
//     inventory_item_info["name_checksum"] = &rfg::inventory_item_info::name_checksum;
//     inventory_item_info["display_name"] = &rfg::inventory_item_info::display_name;
//     inventory_item_info["cost"] = &rfg::inventory_item_info::cost;
//     inventory_item_info["default_count"] = &rfg::inventory_item_info::default_count;
//     inventory_item_info["max_item"] = &rfg::inventory_item_info::max_item;
//     inventory_item_info["description"] = &rfg::inventory_item_info::description;
//     inventory_item_info["info"] = &rfg::inventory_item_info::w_info;
//     inventory_item_info["item_order"] = &rfg::inventory_item_info::item_order;
//     inventory_item_info["use"] = &rfg::inventory_item_info::use;
// }

// void bind_inventory_item(sol::state_view &lua)
// {
//     auto inventory_item = lua["game"].get_or_create<sol::table>().new_usertype<rfg::inventory_item>(
//         "inventory_item", sol::no_constructor);
//     inventory_item["next"] = &rfg::inventory_item::next;
//     inventory_item["previous"] = &rfg::inventory_item::previous;
//     inventory_item["info"] = &rfg::inventory_item::info;
//     inventory_item["count"] = &rfg::inventory_item::count;
//     inventory_item["selection_slot"] = &rfg::inventory_item::selection_slot;
//     inventory_item["attachment_prop"] = &rfg::inventory_item::attachment_prop;
//     inventory_item["weapon_handle"] = &rfg::inventory_item::weapon_handle;
// }

// void bind_item_damage_info_flags(sol::state_view &lua) {}

// void bind_item_damage_info(sol::state_view &lua)
// {
//     auto item_damage_info = lua["game"].get_or_create<sol::table>().new_usertype<rfg::item_damage_info>(
//         "item_damage_info", sol::no_constructor);
//     item_damage_info["hitpoints"] = &rfg::item_damage_info::hitpoints;
//     //"flags", &rfg::item_damage_info::flags
// }

// void bind_inv_item_info(sol::state_view &lua) {}

// void bind_prop_type(sol::state_view &lua)
// {
//     auto item_prop_type = lua["game"].get_or_create<sol::table>().new_enum(
//         "item_prop_type", "none", rfg::prop_type::PROP_TYPE_NONE, "ammo", rfg::prop_type::PROP_TYPE_AMMO, "clip",
//         rfg::prop_type::PROP_TYPE_CLIP, "accessory", rfg::prop_type::PROP_TYPE_ACCESSORY1, "scope",
//         rfg::prop_type::PROP_TYPE_SCOPE, "silencer", rfg::prop_type::PROP_TYPE_SILENCER, "code_designated",
//         rfg::prop_type::PROP_TYPE_CODE_DESIGNATED, "head_prop", rfg::prop_type::PROP_TYPE_HEAD_PROP, "grenade_1",
//         rfg::prop_type::PROP_TYPE_GRENADE_1, "grenade_2", rfg::prop_type::PROP_TYPE_GRENADE_2, "grenade_3",
//         rfg::prop_type::PROP_TYPE_GRENADE_3, "accessory_misc", rfg::prop_type::PROP_TYPE_ACCESSORY_MISC,
//         "satchel_charge", rfg::prop_type::PROP_TYPE_SATCHEL_CHARGE, "eye_wear", rfg::prop_type::PROP_TYPE_EYE_WEAR,
//         "torso", rfg::prop_type::PROP_TYPE_TORSO, "earring_1", rfg::prop_type::PROP_TYPE_EARRING1, "earring_2",
//         rfg::prop_type::PROP_TYPE_EARRING2, "waist", rfg::prop_type::PROP_TYPE_WAIST, "jetpack",
//         rfg::prop_type::PROP_TYPE_JETPACK, "mp_flag", rfg::prop_type::PROP_TYPE_MP_FLAG, "back",
//         rfg::prop_type::PROP_TYPE_BACK);
// }

// void bind_item_info(sol::state_view &lua)
// {
//     auto item_prop = lua["game"].get_or_create<sol::table>().new_usertype<rfg::item_info::item_prop>(
//         "item_prop", sol::no_constructor);
//     item_prop["name"] = &rfg::item_info::item_prop::prop_name;
//     item_prop["tag"] = &rfg::item_info::item_prop::prop_tag;
//     item_prop["type"] = &rfg::item_info::item_prop::type;
//     //"flags", &rfg::item_info::item_prop::flags

//     auto item_info =
//         lua["game"].get_or_create<sol::table>().new_usertype<rfg::item_info>("item_info", sol::no_constructor);
//     item_info["name"] = &rfg::item_info::name;
//     //item_info["smesh_name"] = &rfg::item_info::smesh_name;
//     //item_info["cmesh_name"] = &rfg::item_info::cmesh_name;
//     //item_info["rig_name"] = &rfg::item_info::rig_name;
//     //item_info["anim_set_name"] = &rfg::item_info::anim_set_name;
//     //item_info["pickup_smesh_name"] = &rfg::item_info::pickup_smesh_name;
//     //item_info["srid"] = &rfg::item_info::srid;
//     //item_info["high_res_srid"] = &rfg::item_info::high_res_srid;
//     //item_info["multiplayer_only"] = &rfg::item_info::multiplayer_only;
//     //item_info["shared_backpack"] = &rfg::item_info::shared_backpack;
//     //item_info["flags"] = &rfg::item_info::flags;
//     //"no_peg_load", &rfg::item_info::no_peg_load,
//     //item_info["material_effect_id"] = &rfg::item_info::material_effect_id;
//     //item_info["num_props"] = &rfg::item_info::num_props;
//     //item_info["props"] = &rfg::item_info::props;
//     //item_info["special_flags"] = &rfg::item_info::special_flags;
//     //"high_res_material", &rfg::item_info::high_res_material,
//     item_info["mass"] = &rfg::item_info::mass;
//     item_info["linear_damping"] = &rfg::item_info::linear_damping;
//     item_info["angular_damping"] = &rfg::item_info::angular_damping;
//     item_info["restitution"] = &rfg::item_info::restitution;
//     item_info["friction"] = &rfg::item_info::friction;
//     //"angular_velocity", &rfg::item_info::angular_velocity,
//     //item_info["respawn_delay"] = &rfg::item_info::respawn_delay;
//     //"touch_arg_1", &rfg::item_info::touch_arg_1,
//     //"touch_arg_2", &rfg::item_info::touch_arg_2,
//     //"touch", &rfg::item_info::touch,
//     //item_info["damage_flags"] = &rfg::item_info::damage_flags;
//     item_info["hitpoints"] = &rfg::item_info::hitpoints;
//     //item_info["pickup_sound"] = &rfg::item_info::pickup_snd;
//     //item_info["pickup_sound_2"] = &rfg::item_info::pickup_snd_2;
//     item_info["spin_time"] = &rfg::item_info::spin_time;
//     //item_info["m_foley_collision"] = &rfg::item_info::m_foley_collision;
//     //item_info["cloth_foley"] = &rfg::item_info::cloth_foley;
//     item_info["safehouse_weapon"] = &rfg::item_info::safehouse_weapon;
//     item_info["explosion_info"] = &rfg::item_info::m_explosion_info;
// }

// void bind_special_purpose_flags(sol::state_view &lua) {}

// void bind_obj_item_flags(sol::state_view &lua) {}

// void bind_item(sol::state_view &lua)
// {
//     auto item = lua["game"].get_or_create<sol::table>().new_usertype<rfg::item>(
//         "item", sol::no_constructor, sol::base_classes, sol::bases<rfg::object>());
//     //"previous", &rfg::item::previous,
//     //"next", &rfg::item::next,
//     item["info"] = &rfg::item::info;
//     //"rdd", &rfg::item::rdd,
//     //"character_instance", &rfg::item::char_instance,
//     item["render_alpha"] = &rfg::item::render_alpha;
//     item["stealth_percent"] = &rfg::item::stealth_percent;
//     item["casts_transparent_shadows"] = &rfg::item::casts_transparent_shadows;
//     item["render_distance"] = &rfg::item::render_distance;
//     //"touch_arg1_override", &rfg::item::touch_arg1_override,
//     //"touch_arg2_override", &rfg::item::touch_arg2_override,
//     //"mass_override", &rfg::item::mass_override,
//     item["collision_type"] = &rfg::item::collision_type;
//     item["prop_type"] = &rfg::item::prop_type;
//     item["deletion_timer"] = &rfg::item::deletion_timer;
//     item["respawn_timer"] = &rfg::item::respawn_timer;
//     //item["touch_delay_timer"] = &rfg::item::touch_delay_timer;
//     //item["cloth_deletion_timer"] = &rfg::item::cloth_deletion_timer;
//     //item["dropped_timer"] = &rfg::item::dropped_timer;
//     //item["nav_cell_detour_request_handle"] = &rfg::item::_nav_cell_detour_request_handle;
//     item["flags"] = &rfg::item::flags;
//     item["last_pos"] = &rfg::item::last_pos;
//     //item["srid"] = &rfg::item::srid;
//     //"cloth_sim", &rfg::item::cloth_sim,
//     item["salvage_material"] = &rfg::item::salvage_material;
//     item["salvage_effect"] = &rfg::item::salvage_effect;
//     //item["m_foley_collision_instance"] = &rfg::item::m_foley_collision_instance;
//     //"mp_sim_state", &rfg::item::mp_sim_state,
//     //"pickup_value", &rfg::item::pickup_value,
//     item["special_flags"] = &rfg::item::special_flags;
//     item["damage_info"] = &rfg::item::damage_info;
//     //"default_batchable_setting", &rfg::item::default_batchable_setting,
//     item["xray_material"] = &rfg::item::xray_material;
//     item["xray_render_alpha"] = &rfg::item::xray_render_alpha;
//     item["owner_handle"] = &rfg::item::owner_handle;
// }

// } // namespace rfg
