#include "patch/rfg/weapon.hpp"

#include <sol/sol.hpp>
#include <span>

namespace rfg {
void bind_weapon_functions(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table["get_weapon_infos"] = [&lua]() {
        return std::span<rfg::weapon_info>(*rfg::g_weapon_infos(), *rfg::g_weapon_infos_count());
        // rfg::weapon_info *infos = *rfg::g_weapon_infos();
        // int32_t count = *rfg::g_weapon_infos_count();

        // sol::table t = lua.create_table(count, 0);
        // if (!infos)
        //     return t;
        // for (int32_t i = 0; i < count; ++i)
        // {
        //     t[i + 1] = &infos[i];
        // }
        // return t;
    };
    // table["get_weapon_infos_count"] = []() { return *rfg::g_weapon_infos_count(); };

    table["add_weapon_to_cabinet"] = [](const rfg::weapon_info& info, bool unlocked) {
        if (!rfg::weapon_cabinet_unlock_weapon(&info, unlocked)) {
            rfg::weapon_cabinet_add_weapon(&info, unlocked);
        }
    };
}

void bind_aim_drift_profile(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto aim_drift_profile =
        table.new_usertype<rfg::aim_drift_profile>("aim_drift_profile", sol::no_constructor);
    aim_drift_profile["name"] = &rfg::aim_drift_profile::name;
    aim_drift_profile["min_change_direction_time"] =
        &rfg::aim_drift_profile::min_change_direction_time;
    aim_drift_profile["max_change_direction_time"] =
        &rfg::aim_drift_profile::max_change_direction_time;
    aim_drift_profile["acquire_time"] = &rfg::aim_drift_profile::acquire_time;
    aim_drift_profile["max_acquire_penalty"] = &rfg::aim_drift_profile::max_acquire_penalty;
    aim_drift_profile["offscreen_penalty"] = &rfg::aim_drift_profile::offscreen_penalty;
    aim_drift_profile["player_penalty"] = &rfg::aim_drift_profile::player_penalty;
    aim_drift_profile["player_in_cover_penalty"] = &rfg::aim_drift_profile::player_in_cover_penalty;
    aim_drift_profile["my_speed_penalty"] = &rfg::aim_drift_profile::my_speed_penalty;
    aim_drift_profile["target_speed_penalty"] = &rfg::aim_drift_profile::target_speed_penalty;
    aim_drift_profile["kneeling_bonus_pct"] = &rfg::aim_drift_profile::kneeling_bonus_pct;
    aim_drift_profile["return_fire_bonus_pct"] = &rfg::aim_drift_profile::return_fire_bonus_pct;
    aim_drift_profile["min_horizontal_error"] = &rfg::aim_drift_profile::min_horizontal_error;
    aim_drift_profile["max_horizontal_error"] = &rfg::aim_drift_profile::max_horizontal_error;
    aim_drift_profile["max_grow_rate"] = &rfg::aim_drift_profile::max_grow_rate;
    aim_drift_profile["max_decay_rate"] = &rfg::aim_drift_profile::max_decay_rate;
    aim_drift_profile["pos_vertical_scale"] = &rfg::aim_drift_profile::pos_vertical_scale;
    aim_drift_profile["neg_vertical_scale"] = &rfg::aim_drift_profile::neg_vertical_scale;
    aim_drift_profile["max_vertical_error_dist"] = &rfg::aim_drift_profile::max_vertical_error_dist;
}

void bind_weight_times(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weight_times = table.new_usertype<rfg::weight_times>("weight_times", sol::no_constructor);
    weight_times["time"] = &rfg::weight_times::time;
    weight_times["wobble"] = &rfg::weight_times::wobble;
    weight_times["destable"] = &rfg::weight_times::destable;
    weight_times["wander"] = &rfg::weight_times::wander;
    weight_times["jitter"] = &rfg::weight_times::jitter;
    weight_times["oscillate_1"] = &rfg::weight_times::oscillate1;
    weight_times["oscillate_2"] = &rfg::weight_times::oscillate2;
    weight_times["direct"] = &rfg::weight_times::direct;
    weight_times["wander_direct"] = &rfg::weight_times::wander_direct;
    weight_times["blur"] = &rfg::weight_times::blur;
    weight_times["controller_vibration_strong"] = &rfg::weight_times::controller_vibration_strong;
    weight_times["controller_vibration_weak"] = &rfg::weight_times::controller_vibration_weak;
}

void bind_camera_shake(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto camera_shake = table.new_usertype<rfg::camera_shake>("camera_shake", sol::no_constructor);
    camera_shake["name"] = &rfg::camera_shake::name;
    camera_shake["foley_ref"] = &rfg::camera_shake::foley_ref;
    camera_shake["foley_play_id"] = &rfg::camera_shake::foley_play_id;
    camera_shake["wobble"] = &rfg::camera_shake::wobble;
    camera_shake["wobble_variation"] = &rfg::camera_shake::wobble_variation;
    camera_shake["destable"] = &rfg::camera_shake::destable;
    camera_shake["destable_frequency"] = &rfg::camera_shake::destable_frequency;
    camera_shake["wander"] = &rfg::camera_shake::wander;
    camera_shake["wander_frequency"] = &rfg::camera_shake::wander_frequency;
    camera_shake["jitter"] = &rfg::camera_shake::jitter;
    camera_shake["oscillate_1"] = &rfg::camera_shake::oscillate1;
    camera_shake["oscillate_1_frequency"] = &rfg::camera_shake::oscillate1_frequency;
    camera_shake["oscillate_2"] = &rfg::camera_shake::oscillate2;
    camera_shake["oscillate_2_frequency"] = &rfg::camera_shake::oscillate2_frequency;
    camera_shake["direct"] = &rfg::camera_shake::direct;
    camera_shake["wander_direct"] = &rfg::camera_shake::wander_direct;
    camera_shake["weights"] = &rfg::camera_shake::weights;
    camera_shake["num_weights"] = &rfg::camera_shake::num_weights;
}

void bind_weapon_info_projectile_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_info_projectile_info = table.new_usertype<rfg::weapon_info_projectile_info>(
        "weapon_info_projectile_info", sol::no_constructor);
    weapon_info_projectile_info["obj_item_info"] = &rfg::weapon_info_projectile_info::obj_item_info;
    weapon_info_projectile_info["start_speed"] = &rfg::weapon_info_projectile_info::start_speed;
    weapon_info_projectile_info["max_speed"] = &rfg::weapon_info_projectile_info::max_speed;
    weapon_info_projectile_info["acceleration"] = &rfg::weapon_info_projectile_info::acceleration;
    weapon_info_projectile_info["fuse_time"] = &rfg::weapon_info_projectile_info::fuse_time;
    weapon_info_projectile_info["max_throw_dist"] =
        &rfg::weapon_info_projectile_info::max_throw_dist;
    weapon_info_projectile_info["gravity"] = &rfg::weapon_info_projectile_info::gravity;
    weapon_info_projectile_info["sound"] = &rfg::weapon_info_projectile_info::sound;
    weapon_info_projectile_info["effect_1"] = &rfg::weapon_info_projectile_info::effect1;
    weapon_info_projectile_info["effect_2"] = &rfg::weapon_info_projectile_info::effect2;
    weapon_info_projectile_info["effect_3"] = &rfg::weapon_info_projectile_info::effect3;
    weapon_info_projectile_info["effect_4"] = &rfg::weapon_info_projectile_info::effect4;
    weapon_info_projectile_info["flags"] = &rfg::weapon_info_projectile_info::flags;
    weapon_info_projectile_info["inaccurate_flight"] =
        &rfg::weapon_info_projectile_info::inaccurate_flight;
    weapon_info_projectile_info["time_until_propelled"] =
        &rfg::weapon_info_projectile_info::time_until_propelled;
    weapon_info_projectile_info["time_until_prop_expire"] =
        &rfg::weapon_info_projectile_info::time_until_prop_expire;
    weapon_info_projectile_info["time_until_drop"] =
        &rfg::weapon_info_projectile_info::time_until_drop;
    weapon_info_projectile_info["damage_effect"] = &rfg::weapon_info_projectile_info::damage_effect;
    weapon_info_projectile_info["hit_camera_shake"] =
        &rfg::weapon_info_projectile_info::hit_camera_shake;
}

void bind_damage_scaling_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto damage_scaling_info =
        table.new_usertype<rfg::damage_scaling_info>("damage_scaling_info", sol::no_constructor);
    damage_scaling_info["scale_value"] = &rfg::damage_scaling_info::scale_value;
    damage_scaling_info["damage"] = &rfg::damage_scaling_info::damage;
}

void bind_human_melee_combat_move_id(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto human_melee_combat_move_id =
        table.new_enum("human_melee_combat_move_id", "force_to_32_bits",
                       rfg::human_melee_combat_move_id::HUMAN_MELEE_COMBAT_MOVE_ID_FORCE_TO_32_BITS,
                       "invalid", rfg::human_melee_combat_move_id::INVALID_MELEE_COMBAT_MOVE_ID);
}

void bind_animation_group(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto animation_group =
        table.new_enum("animation_group", "none", rfg::animation_group::ANIMATION_GROUP_NONE,
                       "default", rfg::animation_group::ANIMATION_GROUP_DEFAULT, "ak",
                       rfg::animation_group::ANIMATION_GROUP_AK, "melee",
                       rfg::animation_group::ANIMATION_GROUP_MELEE, "pistol",
                       rfg::animation_group::ANIMATION_GROUP_PISTOL, "revolver",
                       rfg::animation_group::ANIMATION_GROUP_REVOLVER, "rifle",
                       rfg::animation_group::ANIMATION_GROUP_RIFLE, "rpg",
                       rfg::animation_group::ANIMATION_GROUP_RPG, "mortar",
                       rfg::animation_group::ANIMATION_GROUP_MORTAR, "mine",
                       rfg::animation_group::ANIMATION_GROUP_MINE, "hammer",
                       rfg::animation_group::ANIMATION_GROUP_HAMMER, "remote_charge",
                       rfg::animation_group::ANIMATION_GROUP_REMOTE_CHARGE, "turret_machinegun",
                       rfg::animation_group::ANIMATION_GROUP_TURRET_MACHINEGUN, "turret_rocket",
                       rfg::animation_group::ANIMATION_GROUP_TURRET_ROCKET, "turret_railgun",
                       rfg::animation_group::ANIMATION_GROUP_TURRET_RAILGUN, "2_hand_carry",
                       rfg::animation_group::ANIMATION_GROUP_2H_CARRY, "gutter",
                       rfg::animation_group::ANIMATION_GROUP_GUTTER, "shotgun",
                       rfg::animation_group::ANIMATION_GROUP_SHOTGUN, "sniper",
                       rfg::animation_group::ANIMATION_GROUP_SNIPER, "arc",
                       rfg::animation_group::ANIMATION_GROUP_ARC, "railgun",
                       rfg::animation_group::ANIMATION_GROUP_RAILGUN, "nano",
                       rfg::animation_group::ANIMATION_GROUP_NANO, "thermobaric_rocket_launcher",
                       rfg::animation_group::ANIMATION_GROUP_THERMOBARIC_ROCKET_LAUNCHER, "pipe",
                       rfg::animation_group::ANIMATION_GROUP_PIPE, "shield",
                       rfg::animation_group::ANIMATION_GROUP_SHIELD, "grinder",
                       rfg::animation_group::ANIMATION_GROUP_GRINDER, "enforcer",
                       rfg::animation_group::ANIMATION_GROUP_ENFORCER);
}

void bind_weapon_class_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_class_type =
        table.new_enum("weapon_class_type", "none", rfg::weapon_class_type::WEAPON_CLASS_NONE,
                       "bullet", rfg::weapon_class_type::WEAPON_CLASS_BULLET, "launcher",
                       rfg::weapon_class_type::WEAPON_CLASS_LAUNCHER, "thrown",
                       rfg::weapon_class_type::WEAPON_CLASS_THROWN, "thrown_charge",
                       rfg::weapon_class_type::WEAPON_CLASS_THROWN_CHARGE, "thrown_mine",
                       rfg::weapon_class_type::WEAPON_CLASS_THROWN_MINE, "thrown_grenade",
                       rfg::weapon_class_type::WEAPON_CLASS_THROWN_GRENADE, "melee",
                       rfg::weapon_class_type::WEAPON_CLASS_MELEE, "sledgehammer",
                       rfg::weapon_class_type::WEAPON_CLASS_SLEDGEHAMMER, "gutter",
                       rfg::weapon_class_type::WEAPON_CLASS_GUTTER, "grinder",
                       rfg::weapon_class_type::WEAPON_CLASS_GRINDER, "arc_welder",
                       rfg::weapon_class_type::WEAPON_CLASS_ARC_WELDER, "nano_rifle",
                       rfg::weapon_class_type::WEAPON_CLASS_NANO_RIFLE, "mass_driver",
                       rfg::weapon_class_type::WEAPON_CLASS_MASS_DRIVER, "harpoon",
                       rfg::weapon_class_type::WEAPON_CLASS_HARPOON, "singularity_bomb",
                       rfg::weapon_class_type::WEAPON_CLASS_SINGULARITY_BOMB, "repair",
                       rfg::weapon_class_type::WEAPON_CLASS_REPAIR, "flame",
                       rfg::weapon_class_type::WEAPON_CLASS_FLAME);
}

void bind_weapon_trigger_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_trigger_type = table.new_enum(
        "weapon_trigger_type", "single", rfg::weapon_trigger_type::WEAPON_TRIGGER_TYPE_SINGLE,
        "automatic", rfg::weapon_trigger_type::WEAPON_TRIGGER_TYPE_AUTOMATIC, "charge",
        rfg::weapon_trigger_type::WEAPON_TRIGGER_TYPE_CHARGE);
}

void bind_weapon_ammo_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_ammo_type =
        table.new_enum("weapon_ammo_type", "bullet", rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_BULLET,
                       "projectile", rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_PROJECTILE, "thrown",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_THROWN, "melee",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_MELEE, "electricity",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_ELECTRICITY, "repair",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_REPAIR, "blanks",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_BLANKS, "flame",
                       rfg::weapon_ammo_type::WEAPON_AMMO_TYPE_FLAME);
}

void bind_weapon_info_flags(sol::state_view& lua) {}

void bind_weapon_firing_pattern(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_firing_pattern_control_point =
        table.new_usertype<rfg::weapon_firing_pattern::control_point>(
            "weapon_firing_pattern_control_point", sol::no_constructor);
    weapon_firing_pattern_control_point["range_pct"] =
        &rfg::weapon_firing_pattern::control_point::range_pct;
    weapon_firing_pattern_control_point["min_burst_size"] =
        &rfg::weapon_firing_pattern::control_point::min_burst_size;
    weapon_firing_pattern_control_point["max_burst_size"] =
        &rfg::weapon_firing_pattern::control_point::max_burst_size;
    weapon_firing_pattern_control_point["min_interval"] =
        &rfg::weapon_firing_pattern::control_point::min_interval;
    weapon_firing_pattern_control_point["max_interval"] =
        &rfg::weapon_firing_pattern::control_point::max_interval;

    auto weapon_firing_pattern_ammo_point =
        table.new_usertype<rfg::weapon_firing_pattern::ammo_point>(
            "weapon_firing_pattern_ammo_point", sol::no_constructor);
    weapon_firing_pattern_ammo_point["range_pct"] =
        &rfg::weapon_firing_pattern::ammo_point::ammo_pct;
    weapon_firing_pattern_ammo_point["min_burst_size"] =
        &rfg::weapon_firing_pattern::ammo_point::min_effective_range;

    auto weapon_firing_pattern_modifier = table.new_usertype<rfg::weapon_firing_pattern::modifier>(
        "weapon_firing_pattern_modifier", sol::no_constructor);
    weapon_firing_pattern_modifier["range_pct"] = &rfg::weapon_firing_pattern::modifier::multiplier;
    weapon_firing_pattern_modifier["min_burst_size"] =
        &rfg::weapon_firing_pattern::modifier::adjustment;

    auto weapon_firing_pattern = table.new_usertype<rfg::weapon_firing_pattern>(
        "weapon_firing_pattern", sol::no_constructor);
    weapon_firing_pattern["name"] = &rfg::weapon_firing_pattern::name;
    weapon_firing_pattern["points"] = &rfg::weapon_firing_pattern::points;
    weapon_firing_pattern["num_control_points"] = &rfg::weapon_firing_pattern::num_control_points;
    weapon_firing_pattern["ammo_points"] = &rfg::weapon_firing_pattern::ammo_points;
    weapon_firing_pattern["num_ammo_points"] = &rfg::weapon_firing_pattern::num_ammo_points;
    weapon_firing_pattern["alert_mod"] = &rfg::weapon_firing_pattern::alert_mod;
    weapon_firing_pattern["flyer_mod"] = &rfg::weapon_firing_pattern::flyer_mod;
    weapon_firing_pattern["heavy_vehicle_mod"] = &rfg::weapon_firing_pattern::heavy_vehicle_mod;
    weapon_firing_pattern["normal_vehicle_mod"] = &rfg::weapon_firing_pattern::normal_vehicle_mod;
    weapon_firing_pattern["covering_fire_mod"] = &rfg::weapon_firing_pattern::covering_fire_mod;
}

void bind_weapon_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_info = table.new_usertype<rfg::weapon_info>("weapon_info", sol::no_constructor);
    weapon_info["name"] =
        sol::property([](rfg::weapon_info& self) { return std::string(self.name); });
    weapon_info["name_crc"] = &rfg::weapon_info::name_crc;
    weapon_info["unique_id"] = &rfg::weapon_info::unique_id;
    weapon_info["flags"] = &rfg::weapon_info::flags;
    weapon_info["weapon_class"] = &rfg::weapon_info::weapon_class;
    weapon_info["weapon_obj_item_info"] = &rfg::weapon_info::weapon_obj_item_info;
    weapon_info["weapon_inv_item_info"] = &rfg::weapon_info::weapon_inv_item_info;
    weapon_info["default_team"] = &rfg::weapon_info::default_team;
    weapon_info["icon_name"] =
        sol::property([](rfg::weapon_info& self) { return std::string(self.icon_name); });
    //"small_icon_name", &rfg::weapon_info::small_icon_name,
    weapon_info["reticule_name"] =
        sol::property([](rfg::weapon_info& self) { return std::string(self.reticule_name); });
    weapon_info["fine_aim_reticule_name"] = sol::property(
        [](rfg::weapon_info& self) { return std::string(self.fine_aim_reticule_name); });
    //"mp_kill_phrase", &rfg::weapon_info::mp_kill_phrase,
    weapon_info["weapon_anim_group"] = &rfg::weapon_info::weapon_anim_group;
    weapon_info["muzzle_flash_effect"] = &rfg::weapon_info::muzzle_flash_effect;
    //"muzzle_smoke_effect", &rfg::weapon_info::muzzle_smoke_effect,
    weapon_info["special_hit_effect"] = &rfg::weapon_info::special_hit_effect;
    weapon_info["special_effect"] = &rfg::weapon_info::special_effect;
    weapon_info["secondary_special_effect"] = &rfg::weapon_info::secondary_special_effect;
    weapon_info["overheated_effect"] = &rfg::weapon_info::overheated_effect;
    weapon_info["tracer_effect"] = &rfg::weapon_info::tracer_effect;
    weapon_info["fire_camera_shake"] = &rfg::weapon_info::fire_camera_shake;
    weapon_info["fire_camera_shake_ignore_disabled"] =
        &rfg::weapon_info::fire_camera_shake_ignore_disabled;
    weapon_info["secondary_camera_shake"] = &rfg::weapon_info::secondary_camera_shake;
    weapon_info["player_hit_camera_shake"] = &rfg::weapon_info::player_hit_camera_shake;
    weapon_info["attachment_point"] = &rfg::weapon_info::attachment_point;
    weapon_info["fire_sound"] = &rfg::weapon_info::fire_sound;
    weapon_info["secondary_sound"] = &rfg::weapon_info::secondary_sound;
    weapon_info["upgrade_sound"] = &rfg::weapon_info::upgrade_sound;
    weapon_info["reload_sound"] = &rfg::weapon_info::reload_sound;
    //"reload_sound_delay", &rfg::weapon_info::reload_sound_delay,
    weapon_info["no_ammo_sound"] = &rfg::weapon_info::no_ammo_sound;
    weapon_info["special_sound"] = &rfg::weapon_info::special_sound;
    weapon_info["flyby_sound"] = &rfg::weapon_info::flyby_sound;
    weapon_info["num_weapon_personas"] = &rfg::weapon_info::num_weapon_personas;
    //"npc_fire_sounds", &rfg::weapon_info::npc_fire_sounds,
    weapon_info["max_range"] = &rfg::weapon_info::max_range;
    weapon_info["red_range"] = &rfg::weapon_info::red_range;
    weapon_info["max_engagement_dist"] = &rfg::weapon_info::max_engagement_dist;
    weapon_info["min_engagement_dist"] = &rfg::weapon_info::min_engagement_dist;
    weapon_info["max_ai_penetrating_dist"] = &rfg::weapon_info::max_ai_penetrating_dist;
    weapon_info["npc_firing_pattern"] = &rfg::weapon_info::npc_firing_pattern;
    weapon_info["npc_aim_drift_profile"] = &rfg::weapon_info::npc_aim_drift_profile;
    weapon_info["trigger_type"] = &rfg::weapon_info::trigger_type;
    weapon_info["ammo_type"] = &rfg::weapon_info::ammo_type;
    weapon_info["magazine_size"] = &rfg::weapon_info::magazine_size;
    weapon_info["magazine_start_num"] = &rfg::weapon_info::magazine_start_num;
    weapon_info["max_rounds"] = &rfg::weapon_info::max_rounds;
    weapon_info["max_rounds_upgrade"] = &rfg::weapon_info::max_rounds_upgrade;
    weapon_info["ammo_box_restock"] = &rfg::weapon_info::ammo_box_restock;
    weapon_info["to_min_spread"] = &rfg::weapon_info::to_min_spread;
    weapon_info["to_max_spread"] = &rfg::weapon_info::to_max_spread;
    weapon_info["melee_group_index"] = &rfg::weapon_info::melee_group_index;
    weapon_info["bullet_group_index"] = &rfg::weapon_info::bullet_group_index;
    weapon_info["tracer_frequency"] = &rfg::weapon_info::tracer_frequency;
    weapon_info["shots_per_round"] = &rfg::weapon_info::shots_per_round;
    weapon_info["firing_sound_radius"] = &rfg::weapon_info::firing_sound_radius;
    weapon_info["npc_refire_delay"] = &rfg::weapon_info::npc_refire_delay;
    weapon_info["default_refire_delay"] = &rfg::weapon_info::default_refire_delay;
    weapon_info["prefire_delay"] = &rfg::weapon_info::prefire_delay;
    weapon_info["default_reload_delay"] = &rfg::weapon_info::default_reload_delay;
    weapon_info["low_scale_damage"] = &rfg::weapon_info::low_scale_damage;
    weapon_info["high_scale_damage"] = &rfg::weapon_info::high_scale_damage;
    weapon_info["explosion_info"] = &rfg::weapon_info::m_explosion_info;
    weapon_info["ai_explosion_info"] = &rfg::weapon_info::m_ai_explosion_info;
    weapon_info["fire_cone_dot"] = &rfg::weapon_info::fire_cone_dot;
    weapon_info["even_spread_accuracy_dot"] = &rfg::weapon_info::even_spread_accuracy_dot;
    weapon_info["max_spread"] = &rfg::weapon_info::max_spread;
    weapon_info["min_spread"] = &rfg::weapon_info::min_spread;
    weapon_info["fine_aim_max_spread"] = &rfg::weapon_info::fine_aim_max_spread;
    weapon_info["fine_aim_min_spread"] = &rfg::weapon_info::fine_aim_min_spread;
    weapon_info["npc_max_spread"] = &rfg::weapon_info::npc_max_spread;
    weapon_info["npc_min_spread"] = &rfg::weapon_info::npc_min_spread;
    weapon_info["spread_multiplier_run"] = &rfg::weapon_info::spread_multiplier_run;
    weapon_info["ragdoll_force_shoot"] = &rfg::weapon_info::ragdoll_force_shoot;
    weapon_info["ragdoll_chance"] = &rfg::weapon_info::ragdoll_chance;
    weapon_info["recoil_camera_kick"] = &rfg::weapon_info::recoil_camera_kick;
    weapon_info["recoil_impulse"] = &rfg::weapon_info::recoil_impulse;
    weapon_info["out_of_ammo_reload_delay"] = &rfg::weapon_info::out_of_ammo_reload_delay;
    weapon_info["overheat_cool_down_time"] = &rfg::weapon_info::overheat_cool_down_time;
    weapon_info["overheat_percent_per_shot"] = &rfg::weapon_info::overheat_percent_per_shot;
    weapon_info["dropped_ammo_scale"] = &rfg::weapon_info::dropped_ammo_scale;
    weapon_info["bullet_hole_scale"] = &rfg::weapon_info::bullet_hole_scale;
    weapon_info["headshot_multiplier"] = &rfg::weapon_info::headshot_multiplier;
    weapon_info["zoom_magnification"] = &rfg::weapon_info::zoom_magnification;
    //"autoaim_override", &rfg::weapon_info::autoaim_override,
    weapon_info["npc_autoaim"] = &rfg::weapon_info::npc_autoaim;
    weapon_info["aim_assist"] = &rfg::weapon_info::aim_assist;
    weapon_info["player_move_speed_multiplier"] = &rfg::weapon_info::player_move_speed_multiplier;
    weapon_info["npc_move_speed_multiplier"] = &rfg::weapon_info::npc_move_speed_multiplier;
    //"alert_multiplier", &rfg::weapon_info::alert_multiplier,
    weapon_info["projectile_info"] = &rfg::weapon_info::projectile_info;
    weapon_info["standing_primary_melee_attack"] = &rfg::weapon_info::standing_primary_melee_attack;
    weapon_info["standing_secondary_melee_attack"] =
        &rfg::weapon_info::standing_secondary_melee_attack;
    weapon_info["standing_tertiary_melee_attack"] =
        &rfg::weapon_info::standing_tertiary_melee_attack;
    weapon_info["crouching_primary_melee_attack"] =
        &rfg::weapon_info::crouching_primary_melee_attack;
    weapon_info["crouching_secondary_melee_attack"] =
        &rfg::weapon_info::crouching_secondary_melee_attack;
    weapon_info["crouching_tertiary_melee_attack"] =
        &rfg::weapon_info::crouching_tertiary_melee_attack;
}

void bind_weapon_callback_idx(sol::state_view& lua) {}

void bind_weapon_callbacks(sol::state_view& lua) {}

void bind_mp_fire_info_flags(sol::state_view& lua) {}

void bind_weapon_fire_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon_fire_info =
        table.new_usertype<rfg::weapon_fire_info>("weapon_fire_info", sol::no_constructor);
    weapon_fire_info["start_pos"] = &rfg::weapon_fire_info::start_pos;
    weapon_fire_info["end_pos"] = &rfg::weapon_fire_info::end_pos;
    weapon_fire_info["hit_handle"] = &rfg::weapon_fire_info::hit_handle;
    weapon_fire_info["hit_pos"] = &rfg::weapon_fire_info::hit_pos;
    weapon_fire_info["hit_normal"] = &rfg::weapon_fire_info::hit_normal;
    weapon_fire_info["hit_shape_key"] = &rfg::weapon_fire_info::hit_shape_key;
    weapon_fire_info["hit_alt_body_idx"] = &rfg::weapon_fire_info::hit_alt_body_idx;
    weapon_fire_info["hit_bone"] = &rfg::weapon_fire_info::hit_bone;
    weapon_fire_info["nearest_human"] = &rfg::weapon_fire_info::nearest_human;
    weapon_fire_info["w_info"] = &rfg::weapon_fire_info::w_info;
    weapon_fire_info["hit_physical_material"] = &rfg::weapon_fire_info::hit_physical_material;
    weapon_fire_info["hit_effect_material"] = &rfg::weapon_fire_info::hit_effect_material;
    weapon_fire_info["hit_location"] = &rfg::weapon_fire_info::hit_location;
}

void bind_electricity_hit_rating(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto electricity_hit_rating = table.new_enum(
        "electricity_hit_rating", "none", rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_NONE,
        "allied_human", rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_ALLIED_HUMAN, "world",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_WORLD, "friendly_human",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_FRIENDLY_HUMAN, "object",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_OBJECT, "dead_human",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_DEAD_HUMAN, "human",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_HUMAN, "electrifiable_object",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_ELECTRIFIABLE_OBJECT, "vehicle",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_VEHICLE, "unfriendly_human",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_UNFRIENDLY_HUMAN, "hostile_human",
        rfg::electricity_hit_rating::ELECTRICITY_HIT_RATING_HOSTILE_HUMAN);
}

void bind_arc_welder_cache_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto arc_welder_cache_info = table.new_usertype<rfg::arc_welder_cache_info>(
        "arc_welder_cache_info", sol::no_constructor);
    arc_welder_cache_info["hit_pos"] = &rfg::arc_welder_cache_info::hit_pos;
    arc_welder_cache_info["hit_normal"] = &rfg::arc_welder_cache_info::hit_normal;
    arc_welder_cache_info["hit_handle"] = &rfg::arc_welder_cache_info::hit_handle;
    arc_welder_cache_info["hit_shape_key"] = &rfg::arc_welder_cache_info::hit_shape_key;
    arc_welder_cache_info["hit_rating"] = &rfg::arc_welder_cache_info::hit_rating;
}

void bind_weapon(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto weapon = table.new_usertype<rfg::weapon>("weapon", sol::no_constructor, sol::base_classes,
                                                  sol::bases<rfg::item, rfg::object>());
    //"previous", &rfg::weapon::previous,
    //"next", &rfg::weapon::next,
    weapon["info"] = &rfg::weapon::info;
    weapon["turret_handle"] = &rfg::weapon::turret_handle;
    weapon["weapon_fire_sound_timestamp"] = &rfg::weapon::weapon_fire_sound_timestamp;
    weapon["weapon_hit_sound_timestamp"] = &rfg::weapon::weapon_hit_sound_timestamp;
    weapon["one_shot_delay_timestamp"] = &rfg::weapon::one_shot_delay_timestamp;
    //"melee_combat_move_past", &rfg::weapon::melee_combat_move_past,
    weapon["melee_combat_in_combo"] = &rfg::weapon::melee_combat_in_combo;
    weapon["arc_welder_post_arc_timer"] = &rfg::weapon::arc_welder_post_arc_timer;
    weapon["multi_rocket_trigger_down_timer"] = &rfg::weapon::multi_rocket_trigger_down_timer;
    weapon["secondary_rockets_to_fire"] = &rfg::weapon::secondary_rockets_to_fire;
    weapon["mat_fx_handle"] = &rfg::weapon::mat_fx_handle;
    weapon["current_mat_fx"] = &rfg::weapon::current_mat_fx;
    weapon["mat_fx_clip_handle"] = &rfg::weapon::mat_fx_clip_handle;
    weapon["mat_fx_handle_for_clip"] = &rfg::weapon::mat_fx_handle_for_clip;
    //"flags", &rfg::weapon::flags,
    //"cb", &rfg::weapon::cb,
    weapon["fire_info"] = &rfg::weapon::fire_info;
    weapon["rounds_in_magazine"] = &rfg::weapon::rounds_in_magazine;
    weapon["rounds_in_reserve"] = &rfg::weapon::rounds_in_reserve;
    weapon["current_spread"] = &rfg::weapon::current_spread;
    weapon["tracer_count"] = &rfg::weapon::tracer_count;
    weapon["refire_delay_time"] = &rfg::weapon::refire_delay_time;
    weapon["overheat_percent"] = &rfg::weapon::overheat_percent;
    weapon["overheated"] = &rfg::weapon::overheated;
    weapon["overheated_effect_handle"] = &rfg::weapon::overheated_effect_handle;
    weapon["reload_delay_timer"] = &rfg::weapon::reload_delay_timer;
    weapon["last_fired_timer"] = &rfg::weapon::last_fired_timer;
    weapon["muzzle_flash_intensity"] = &rfg::weapon::muzzle_flash_intensity;
    weapon["muzzle_flash_effect_handle"] = &rfg::weapon::muzzle_flash_effect_handle;
    weapon["muzzle_smoke_effect_handle"] = &rfg::weapon::muzzle_smoke_effect_handle;
    weapon["muzzle_smoke_timestamp"] = &rfg::weapon::muzzle_smoke_timestamp;
    weapon["grip_tag_index"] = &rfg::weapon::grip_tag_index;
    weapon["secondary_grip_tag_index"] = &rfg::weapon::secondary_grip_tag_index;
    weapon["destruction_tag_index"] = &rfg::weapon::destruction_tag_index;
    weapon["secondary_destruction_tag_index"] = &rfg::weapon::secondary_destruction_tag_index;
    weapon["muzzle_tag_index"] = &rfg::weapon::muzzle_tag_index;
    weapon["melee_blood_effect_tag_index"] = &rfg::weapon::melee_blood_effect_tag_index;
    weapon["num_rounds_fired"] = &rfg::weapon::num_rounds_fired;
    weapon["fire_sound_alr_id"] = &rfg::weapon::fire_sound_alr_id;
    weapon["secondary_sound_id"] = &rfg::weapon::secondary_sound_id;
    weapon["special_sound_id"] = &rfg::weapon::special_sound_id;
    weapon["weapon_persona"] = &rfg::weapon::weapon_persona;
    weapon["grinder_speed_percent"] = &rfg::weapon::grinder_speed_percent;
    weapon["grinder_heat_effect"] = &rfg::weapon::grinder_heat_effect;
    weapon["special_effect_handle"] = &rfg::weapon::special_effect_handle;
    weapon["secondary_special_effect_handle"] = &rfg::weapon::secondary_special_effect_handle;
    //"arc_welder_best_point", &rfg::weapon::arc_welder_best_point
}
} // namespace rfg
