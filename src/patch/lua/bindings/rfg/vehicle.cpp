#include "patch/rfg/vehicle.hpp"

#include "patch/rfg/weapon.hpp"
#include <sol/sol.hpp>

namespace rfg {
void bind_vehicle_functions(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
}
void bind_vehicle_exit_data_flags(sol::state_view& lua) {}

void bind_vehicle_exit_data(sol::state_view& lua) {}

void bind_vehicle_seat_selection_method(sol::state_view& lua) {}

void bind_vehicle_enter_data_flags(sol::state_view& lua) {}

void bind_vehicle_enter_data(sol::state_view& lua) {}

void bind_vehicle_class_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("vehicle_class_type", "automobile", rfg::vehicle_class_type::VCL_AUTOMOBILE,
                   "flyer", rfg::vehicle_class_type::VCL_FLYER, "walker",
                   rfg::vehicle_class_type::VCL_WALKER);
}

void bind_base_vehicle_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("base_vehicle_type", "invalid", rfg::base_vehicle_type::BVT_INVALID, "none",
                   rfg::base_vehicle_type::BVT_NONE, "courier", rfg::base_vehicle_type::BVT_COURIER,
                   "ambulance", rfg::base_vehicle_type::BVT_AMBULANCE, "tank",
                   rfg::base_vehicle_type::BVT_TANK, "art_tank",
                   rfg::base_vehicle_type::BVT_ART_TANK, "bomber",
                   rfg::base_vehicle_type::BVT_BOMBER, "special",
                   rfg::base_vehicle_type::BVT_SPECIAL);
}

void bind_vehicle_road_preference(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("vehicle_road_preference", "none", rfg::vehicle_road_preference::VRP_NONE,
                   "highway", rfg::vehicle_road_preference::VRP_HIGHWAY, "no_highway",
                   rfg::vehicle_road_preference::VRP_NO_HIGHWAY);
}

void bind_lod_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto lod_info = table.new_usertype<rfg::lod_info>("lod_info", sol::no_constructor);
    lod_info["dist"] = &rfg::lod_info::dist;
}

void bind_animlib_bones_used_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto animlib_bones_used_info = table.new_usertype<rfg::animlib_bones_used_info>(
        "animlib_bones_used_info", sol::no_constructor);
    animlib_bones_used_info["unique_id"] = &rfg::animlib_bones_used_info::unique_id;
    animlib_bones_used_info["num_bones"] = &rfg::animlib_bones_used_info::num_bones;
    animlib_bones_used_info["bone_indices"] = &rfg::animlib_bones_used_info::bone_indices;
}

void bind_vehicle_camera_settings(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_camera_settings = table.new_usertype<rfg::vehicle_camera_settings>(
        "vehicle_camera_settings", sol::no_constructor);
    vehicle_camera_settings["lookat_offset"] = &rfg::vehicle_camera_settings::lookat_offset;
    vehicle_camera_settings["lookat_vehicle_offset"] =
        &rfg::vehicle_camera_settings::lookat_vehicle_offset;
    vehicle_camera_settings["lookat_vehicle_enter_offset"] =
        &rfg::vehicle_camera_settings::lookat_vehicle_enter_offset;
    vehicle_camera_settings["lookfrom_height"] = &rfg::vehicle_camera_settings::lookfrom_height;
    vehicle_camera_settings["enter_distance"] = &rfg::vehicle_camera_settings::enter_distance;
    vehicle_camera_settings["follow_dist"] = &rfg::vehicle_camera_settings::follow_dist;
    vehicle_camera_settings["follow_height"] = &rfg::vehicle_camera_settings::follow_height;
    vehicle_camera_settings["y_axis_rotation_speed"] =
        &rfg::vehicle_camera_settings::y_axis_rotation_speed;
    vehicle_camera_settings["camera_steer_angle"] =
        &rfg::vehicle_camera_settings::camera_steer_angle;
    vehicle_camera_settings["camera_steer_speed"] =
        &rfg::vehicle_camera_settings::camera_steer_speed;
    vehicle_camera_settings["turret_camera"] = &rfg::vehicle_camera_settings::turret_camera;
    vehicle_camera_settings["force_turret_cam"] = &rfg::vehicle_camera_settings::force_turret_cam;
}

void bind_vehicle_turret_mount_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_turret_mount_info = table.new_usertype<rfg::vehicle_turret_mount_info>(
        "vehicle_turret_mount_info", sol::no_constructor);
    vehicle_turret_mount_info["name"] = &rfg::vehicle_turret_mount_info::name;
    vehicle_turret_mount_info["prop_point"] = &rfg::vehicle_turret_mount_info::prop_point;
    vehicle_turret_mount_info["seat"] = &rfg::vehicle_turret_mount_info::seat;
    vehicle_turret_mount_info["flags"] = &rfg::vehicle_turret_mount_info::flags;
}

void bind_vehicle_axle_wheel_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_axle_wheel_info = table.new_usertype<rfg::vehicle_axle_wheel_info>(
        "vehicle_axle_wheel_info", sol::no_constructor);
    vehicle_axle_wheel_info["does_steer"] = &rfg::vehicle_axle_wheel_info::does_steer;
    vehicle_axle_wheel_info["does_handbrake"] = &rfg::vehicle_axle_wheel_info::does_handbrake;
    vehicle_axle_wheel_info["engine_torque_factor"] =
        &rfg::vehicle_axle_wheel_info::engine_torque_factor;
    vehicle_axle_wheel_info["mass"] = &rfg::vehicle_axle_wheel_info::mass;
    vehicle_axle_wheel_info["friction"] = &rfg::vehicle_axle_wheel_info::friction;
    vehicle_axle_wheel_info["ai_friction"] = &rfg::vehicle_axle_wheel_info::ai_friction;
    vehicle_axle_wheel_info["braking_torque"] = &rfg::vehicle_axle_wheel_info::braking_torque;
    vehicle_axle_wheel_info["spring_compression"] =
        &rfg::vehicle_axle_wheel_info::spring_compression;
    vehicle_axle_wheel_info["spring_extension"] = &rfg::vehicle_axle_wheel_info::spring_extension;
    vehicle_axle_wheel_info["spring_strength"] = &rfg::vehicle_axle_wheel_info::spring_strength;
    vehicle_axle_wheel_info["spring_power"] = &rfg::vehicle_axle_wheel_info::spring_power;
    vehicle_axle_wheel_info["compression_damping"] =
        &rfg::vehicle_axle_wheel_info::compression_damping;
    vehicle_axle_wheel_info["expansion_damping"] = &rfg::vehicle_axle_wheel_info::expansion_damping;
}

void bind_vehicle_transmission_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_transmission_info = table.new_usertype<rfg::vehicle_transmission_info>(
        "vehicle_transmission_info", sol::no_constructor);
    vehicle_transmission_info["num_gears"] = &rfg::vehicle_transmission_info::num_gears;
    vehicle_transmission_info["gear_ratios"] = &rfg::vehicle_transmission_info::gear_ratios;
    vehicle_transmission_info["downshift_rpms"] = &rfg::vehicle_transmission_info::downshift_rpms;
    vehicle_transmission_info["upshift_rpms"] = &rfg::vehicle_transmission_info::upshift_rpms;
    vehicle_transmission_info["differential_gear_ratio"] =
        &rfg::vehicle_transmission_info::differential_gear_ratio;
    vehicle_transmission_info["reverse_gear_ratio"] =
        &rfg::vehicle_transmission_info::reverse_gear_ratio;
    vehicle_transmission_info["clutch_delay"] = &rfg::vehicle_transmission_info::clutch_delay;
    vehicle_transmission_info["clutch_delay_pre_shift"] =
        &rfg::vehicle_transmission_info::clutch_delay_pre_shift;
    vehicle_transmission_info["forward_to_reverse_delay"] =
        &rfg::vehicle_transmission_info::forward_to_reverse_delay;
    vehicle_transmission_info["reverse_to_forward_delay"] =
        &rfg::vehicle_transmission_info::reverse_to_forward_delay;
}

void bind_vehicle_info_flags(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_info_flags =
        table.new_usertype<rfg::vehicle_info_flags>("vehicle_info_flags", sol::no_constructor);
}

void bind_vehicle_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_info = table.new_usertype<rfg::vehicle_info>("vehicle_info", sol::no_constructor);
    vehicle_info["name"] = &rfg::vehicle_info::name;
    vehicle_info["display_name"] = &rfg::vehicle_info::display_name;
    vehicle_info["mesh_name"] = &rfg::vehicle_info::mesh_name;
    vehicle_info["vehicle_class"] = &rfg::vehicle_info::vehicle_class;
    vehicle_info["spawn_size"] = &rfg::vehicle_info::spawn_size;
    vehicle_info["spawn_box"] = &rfg::vehicle_info::spawn_box;
    //"cover_info", &rfg::vehicle_info::cover_info,
    vehicle_info["slot_id"] = &rfg::vehicle_info::slot_id;
    vehicle_info["srid"] = &rfg::vehicle_info::srid;
    vehicle_info["variant_family"] = &rfg::vehicle_info::variant_family;
    vehicle_info["vehicle_classification"] = &rfg::vehicle_info::vehicle_classification;
    vehicle_info["default_team"] = &rfg::vehicle_info::default_team;
    //"vi_info", &rfg::vehicle_info::vi_info,
    vehicle_info["m_max_hitpoints"] = &rfg::vehicle_info::m_max_hitpoints;
    vehicle_info["m_abandon_hitpoints"] = &rfg::vehicle_info::m_abandon_hitpoints;
    vehicle_info["chassis_mass"] = &rfg::vehicle_info::chassis_mass;
    vehicle_info["m_value"] = &rfg::vehicle_info::m_value;
    vehicle_info["m_chop_shop_props"] = &rfg::vehicle_info::m_chop_shop_props;
    vehicle_info["m_num_lods"] = &rfg::vehicle_info::m_num_lods;
    vehicle_info["m_lod_info"] = &rfg::vehicle_info::m_lod_info;
    vehicle_info["num_turret_mounts"] = &rfg::vehicle_info::num_turret_mounts;
    vehicle_info["turret_mounts"] = &rfg::vehicle_info::turret_mounts;
    vehicle_info["m_road_preference"] = &rfg::vehicle_info::m_road_preference;
    vehicle_info["engine_torque"] = &rfg::vehicle_info::engine_torque;
    vehicle_info["ai_engine_torque"] = &rfg::vehicle_info::ai_engine_torque;
    vehicle_info["min_rpm"] = &rfg::vehicle_info::min_rpm;
    vehicle_info["optimal_rpm"] = &rfg::vehicle_info::optimal_rpm;
    vehicle_info["max_rpm"] = &rfg::vehicle_info::max_rpm;
    vehicle_info["min_rpm_torque_factor"] = &rfg::vehicle_info::min_rpm_torque_factor;
    vehicle_info["max_rpm_torque_factor"] = &rfg::vehicle_info::max_rpm_torque_factor;
    vehicle_info["min_rpm_resistance"] = &rfg::vehicle_info::min_rpm_resistance;
    vehicle_info["opt_rpm_resistance"] = &rfg::vehicle_info::opt_rpm_resistance;
    vehicle_info["max_rpm_resistance"] = &rfg::vehicle_info::max_rpm_resistance;
    vehicle_info["reverse_torque_multiplier"] = &rfg::vehicle_info::reverse_torque_multiplier;
    vehicle_info["clutch_slip_rpm"] = &rfg::vehicle_info::clutch_slip_rpm;
    vehicle_info["enlarged_wheel_radius"] = &rfg::vehicle_info::enlarged_wheel_radius;
    vehicle_info["autobrake_speed"] = &rfg::vehicle_info::autobrake_speed;
    vehicle_info["enforced_max_speed"] = &rfg::vehicle_info::enforced_max_speed;
    vehicle_info["ai_enforced_max_speed"] = &rfg::vehicle_info::ai_enforced_max_speed;
    vehicle_info["enforced_max_rspeed"] = &rfg::vehicle_info::enforced_max_rspeed;
    vehicle_info["powerslide_friction"] = &rfg::vehicle_info::powerslide_friction;
    vehicle_info["powerslide_power"] = &rfg::vehicle_info::powerslide_power;
    vehicle_info["force_assist"] = &rfg::vehicle_info::force_assist;
    vehicle_info["m_num_axles"] = &rfg::vehicle_info::m_num_axles;
    vehicle_info["m_axle_wheel_infos"] = &rfg::vehicle_info::m_axle_wheel_infos;
    vehicle_info["m_exhaust_tag_id"] = &rfg::vehicle_info::m_exhaust_tag_id;
    vehicle_info["trans_info"] = &rfg::vehicle_info::trans_info;
    vehicle_info["max_steering_angle"] = &rfg::vehicle_info::max_steering_angle;
    vehicle_info["max_speed_steering_angle"] = &rfg::vehicle_info::max_speed_steering_angle;
    vehicle_info["ai_max_speed_steering_angle"] = &rfg::vehicle_info::ai_max_speed_steering_angle;
    vehicle_info["m_steering_wheel_max_speed"] = &rfg::vehicle_info::m_steering_wheel_max_speed;
    vehicle_info["m_steering_wheel_max_return_speed"] =
        &rfg::vehicle_info::m_steering_wheel_max_return_speed;
    vehicle_info["m_steering_wheel_damp_angle"] = &rfg::vehicle_info::m_steering_wheel_damp_angle;
    vehicle_info["m_steering_wheel_return_damp_angle"] =
        &rfg::vehicle_info::m_steering_wheel_return_damp_angle;
    vehicle_info["counter_steer_min_speed"] = &rfg::vehicle_info::counter_steer_min_speed;
    vehicle_info["counter_steer_max_speed"] = &rfg::vehicle_info::counter_steer_max_speed;
    vehicle_info["air_steer_roll_max_vel"] = &rfg::vehicle_info::air_steer_roll_max_vel;
    vehicle_info["air_steer_roll_max_angle_rad"] = &rfg::vehicle_info::air_steer_roll_max_angle_rad;
    vehicle_info["air_steer_pitch_max_vel"] = &rfg::vehicle_info::air_steer_pitch_max_vel;
    vehicle_info["air_steer_pitch_max_angle_rad"] =
        &rfg::vehicle_info::air_steer_pitch_max_angle_rad;
    vehicle_info["min_pedal_input_to_block"] = &rfg::vehicle_info::min_pedal_input_to_block;
    vehicle_info["min_time_to_block"] = &rfg::vehicle_info::min_time_to_block;
    vehicle_info["ai_min_time_to_block"] = &rfg::vehicle_info::ai_min_time_to_block;
    vehicle_info["air_density"] = &rfg::vehicle_info::air_density;
    vehicle_info["frontal_area"] = &rfg::vehicle_info::frontal_area;
    vehicle_info["drag_coefficient"] = &rfg::vehicle_info::drag_coefficient;
    vehicle_info["lift_coefficient"] = &rfg::vehicle_info::lift_coefficient;
    vehicle_info["extra_gravity"] = &rfg::vehicle_info::extra_gravity;
    vehicle_info["center_of_mass_y"] = &rfg::vehicle_info::center_of_mass_y;
    vehicle_info["center_of_mass_z"] = &rfg::vehicle_info::center_of_mass_z;
    vehicle_info["camera_settings"] = &rfg::vehicle_info::camera_settings;
    vehicle_info["camera_settings_count"] = &rfg::vehicle_info::camera_settings_count;
    vehicle_info["m_energy_scale"] = &rfg::vehicle_info::m_energy_scale;
    vehicle_info["m_collision_mass_scalar"] = &rfg::vehicle_info::m_collision_mass_scalar;
    vehicle_info["m_collision_damage_scale"] = &rfg::vehicle_info::m_collision_damage_scale;
    vehicle_info["m_terrain_damage_scale"] = &rfg::vehicle_info::m_terrain_damage_scale;
    vehicle_info["m_bullet_damage_scale"] = &rfg::vehicle_info::m_bullet_damage_scale;
    vehicle_info["m_vehicle_damage_scale"] = &rfg::vehicle_info::m_vehicle_damage_scale;
    vehicle_info["m_friction_equalizer"] = &rfg::vehicle_info::m_friction_equalizer;
    vehicle_info["m_ai_friction_equalizer"] = &rfg::vehicle_info::m_ai_friction_equalizer;
    vehicle_info["m_torque_roll_factor"] = &rfg::vehicle_info::m_torque_roll_factor;
    vehicle_info["m_torque_pitch_factor"] = &rfg::vehicle_info::m_torque_pitch_factor;
    vehicle_info["m_torque_yaw_factor"] = &rfg::vehicle_info::m_torque_yaw_factor;
    vehicle_info["m_torque_yaw_scalar"] = &rfg::vehicle_info::m_torque_yaw_scalar;
    vehicle_info["m_extra_torque_factor"] = &rfg::vehicle_info::m_extra_torque_factor;
    vehicle_info["m_chassis_unit_inertia_roll"] = &rfg::vehicle_info::m_chassis_unit_inertia_roll;
    vehicle_info["m_chassis_unit_inertia_pitch"] = &rfg::vehicle_info::m_chassis_unit_inertia_pitch;
    vehicle_info["m_chassis_unit_inertia_yaw"] = &rfg::vehicle_info::m_chassis_unit_inertia_yaw;
    vehicle_info["m_ai_chassis_unit_inertia_yaw"] =
        &rfg::vehicle_info::m_ai_chassis_unit_inertia_yaw;
    vehicle_info["m_viscosity_friction"] = &rfg::vehicle_info::m_viscosity_friction;
    vehicle_info["m_ai_max_braking_decel"] = &rfg::vehicle_info::m_ai_max_braking_decel;
    vehicle_info["m_ai_max_radial_accel"] = &rfg::vehicle_info::m_ai_max_radial_accel;
    vehicle_info["m_alert_multiplier"] = &rfg::vehicle_info::m_alert_multiplier;
    vehicle_info["foley_start"] = &rfg::vehicle_info::foley_start;
    vehicle_info["engine_id"] = &rfg::vehicle_info::engine_id;
    vehicle_info["engine_wavebank_id"] = &rfg::vehicle_info::engine_wavebank_id;
    vehicle_info["foley_off"] = &rfg::vehicle_info::foley_off;
    vehicle_info["foley_engine_peel"] = &rfg::vehicle_info::foley_engine_peel;
    vehicle_info["foley_shift"] = &rfg::vehicle_info::foley_shift;
    vehicle_info["foley_grind"] = &rfg::vehicle_info::foley_grind;
    vehicle_info["foley_honk"] = &rfg::vehicle_info::foley_honk;
    vehicle_info["m_foley_impact_id"] = &rfg::vehicle_info::m_foley_impact_id;
    vehicle_info["m_foley_scraping_id"] = &rfg::vehicle_info::m_foley_scraping_id;
    vehicle_info["m_foley_corpse_impact_id"] = &rfg::vehicle_info::m_foley_corpse_impact_id;
    vehicle_info["m_foley_component_impact_id"] = &rfg::vehicle_info::m_foley_component_impact_id;
    vehicle_info["m_foley_wheel_impact_id"] = &rfg::vehicle_info::m_foley_wheel_impact_id;
    vehicle_info["m_foley_chassis_land_id"] = &rfg::vehicle_info::m_foley_chassis_land_id;
    vehicle_info["m_foley_pass_by"] = &rfg::vehicle_info::m_foley_pass_by;
    vehicle_info["m_foley_door_open_id"] = &rfg::vehicle_info::m_foley_door_open_id;
    vehicle_info["m_foley_door_close_id"] = &rfg::vehicle_info::m_foley_door_close_id;
    vehicle_info["m_effect_engine_fire"] = &rfg::vehicle_info::m_effect_engine_fire;
    vehicle_info["m_effect_engine_smoke"] = &rfg::vehicle_info::m_effect_engine_smoke;
    vehicle_info["m_effect_corpse_smoke"] = &rfg::vehicle_info::m_effect_corpse_smoke;
    vehicle_info["m_effect_component_fire"] = &rfg::vehicle_info::m_effect_component_fire;
    vehicle_info["m_effect_exhaust_normal"] = &rfg::vehicle_info::m_effect_exhaust_normal;
    vehicle_info["m_effect_exhaust_burst"] = &rfg::vehicle_info::m_effect_exhaust_burst;
    vehicle_info["m_effect_collision"] = &rfg::vehicle_info::m_effect_collision;
    vehicle_info["m_effect_scrape"] = &rfg::vehicle_info::m_effect_scrape;
    vehicle_info["m_effect_component_detach"] = &rfg::vehicle_info::m_effect_component_detach;
    vehicle_info["m_effect_head_light_primary"] = &rfg::vehicle_info::m_effect_head_light_primary;
    vehicle_info["m_effect_head_light_secondary"] =
        &rfg::vehicle_info::m_effect_head_light_secondary;
    vehicle_info["m_effect_fog_light"] = &rfg::vehicle_info::m_effect_fog_light;
    vehicle_info["m_effect_tail_light"] = &rfg::vehicle_info::m_effect_tail_light;
    vehicle_info["m_effect_brake_light"] = &rfg::vehicle_info::m_effect_brake_light;
    vehicle_info["m_effect_reverse_light"] = &rfg::vehicle_info::m_effect_reverse_light;
    vehicle_info["m_effect_emergency_light"] = &rfg::vehicle_info::m_effect_emergency_light;
    vehicle_info["m_effect_strobe_light"] = &rfg::vehicle_info::m_effect_strobe_light;
    vehicle_info["m_explosion_info"] = &rfg::vehicle_info::m_explosion_info;
    vehicle_info["m_bomb_explosion_info"] = &rfg::vehicle_info::m_bomb_explosion_info;
    vehicle_info["m_num_variants"] = &rfg::vehicle_info::m_num_variants;
    vehicle_info["m_normal_spin_damping"] = &rfg::vehicle_info::m_normal_spin_damping;
    vehicle_info["m_normal_spin_damping_ai"] = &rfg::vehicle_info::m_normal_spin_damping_ai;
    vehicle_info["m_collision_spin_damping"] = &rfg::vehicle_info::m_collision_spin_damping;
    vehicle_info["m_collision_spin_threshold"] = &rfg::vehicle_info::m_collision_spin_threshold;
    vehicle_info["m_camera_fov_multiplier"] = &rfg::vehicle_info::m_camera_fov_multiplier;
    vehicle_info["m_camera_fov_min_speed"] = &rfg::vehicle_info::m_camera_fov_min_speed;
    vehicle_info["m_camera_shake_min_speed"] = &rfg::vehicle_info::m_camera_shake_min_speed;
    vehicle_info["m_radial_blur_max"] = &rfg::vehicle_info::m_radial_blur_max;
    vehicle_info["m_radial_blur_min_speed"] = &rfg::vehicle_info::m_radial_blur_min_speed;
    vehicle_info["m_trailer_chance"] = &rfg::vehicle_info::m_trailer_chance;
    vehicle_info["rig_name"] = &rfg::vehicle_info::rig_name;
    vehicle_info["anim_set_name"] = &rfg::vehicle_info::anim_set_name;
    vehicle_info["footstep_effects"] = &rfg::vehicle_info::footstep_effects;
    vehicle_info["bones_used_info"] = &rfg::vehicle_info::bones_used_info;
    vehicle_info["flyer_max_up_thrust"] = &rfg::vehicle_info::flyer_max_up_thrust;
    vehicle_info["flyer_max_turn_angvel"] = &rfg::vehicle_info::flyer_max_turn_angvel;
    vehicle_info["flyer_max_turn_angaccl"] = &rfg::vehicle_info::flyer_max_turn_angaccl;
    vehicle_info["flyer_max_thrust_offset_x"] = &rfg::vehicle_info::flyer_max_thrust_offset_x;
    vehicle_info["flyer_max_thrust_offset_z"] = &rfg::vehicle_info::flyer_max_thrust_offset_z;
    vehicle_info["flyer_max_tilt_angvel"] = &rfg::vehicle_info::flyer_max_tilt_angvel;
    vehicle_info["flyer_max_tilt_angaccl"] = &rfg::vehicle_info::flyer_max_tilt_angaccl;
    vehicle_info["flyer_spin_bank_scalar"] = &rfg::vehicle_info::flyer_spin_bank_scalar;
    vehicle_info["flyer_thrust_tilt_scalar"] = &rfg::vehicle_info::flyer_thrust_tilt_scalar;
    vehicle_info["flyer_bank_tilt_scalar"] = &rfg::vehicle_info::flyer_bank_tilt_scalar;
    vehicle_info["flyer_def_lookat_y_scalar"] = &rfg::vehicle_info::flyer_def_lookat_y_scalar;
    vehicle_info["flyer_wingtip_effect"] = &rfg::vehicle_info::flyer_wingtip_effect;
    vehicle_info["flyer_thruster_effect"] = &rfg::vehicle_info::flyer_thruster_effect;
    vehicle_info["flyer_mainengine_effect"] = &rfg::vehicle_info::flyer_mainengine_effect;
    vehicle_info["flyer_jetwash_effect"] = &rfg::vehicle_info::flyer_jetwash_effect;
    vehicle_info["flags"] = &rfg::vehicle_info::flags;
}

void bind_lane_spline_base(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto lane_spline_base =
        table.new_usertype<rfg::lane_spline_base>("lane_spline_base", sol::no_constructor);
}

void bind_route_segment_flags(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_usertype<rfg::route_segment_flags>(
        "route_segment_flags", sol::no_constructor
        // BIND_FLAG(rfg::route_segment_flags, terminal),
        // BIND_FLAG(rfg::route_segment_flags, from_ambient_path),
        // BIND_FLAG(rfg::route_segment_flags, from_navmesh_path),
        // BIND_FLAG(rfg::route_segment_flags, signal_processed),
        // BIND_FLAG(rfg::route_segment_flags, stopped_for_sign)
    );
}

void bind_route_segment(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto route_segment =
        table.new_usertype<rfg::route_segment>("route_segment", sol::no_constructor);
    route_segment["cb_spline"] = &rfg::route_segment::cb_spline;
    route_segment["length"] = &rfg::route_segment::length;
    route_segment["speed_limit"] = &rfg::route_segment::speed_limit;
    route_segment["base_spline"] = &rfg::route_segment::base_spline;
    route_segment["num_knots_minus_one"] = &rfg::route_segment::num_knots_minus_one;
    route_segment["flags"] = &rfg::route_segment::flags;
}

void bind_vehicle_point_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_point_info =
        table.new_usertype<rfg::vehicle_point_info>("vehicle_point_info", sol::no_constructor);
    vehicle_point_info["route_index"] = &rfg::vehicle_point_info::route_index;
    vehicle_point_info["u"] = &rfg::vehicle_point_info::u;
    vehicle_point_info["distance_remaining"] = &rfg::vehicle_point_info::distance_remaining;
}

void bind_vehicle_route_info_flags(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_usertype<rfg::vehicle_route_info_flags>(
        "vehicle_route_info_flags", sol::no_constructor
        // BIND_FLAG(rfg::vehicle_route_info_flags, m_route_segment_inited)
    );
}

void bind_vehicle_route_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_route_info =
        table.new_usertype<rfg::vehicle_route_info>("vehicle_route_info", sol::no_constructor);
    vehicle_route_info["route"] = &rfg::vehicle_route_info::route;
    vehicle_route_info["last_next_spline"] = &rfg::vehicle_route_info::last_next_spline;
    vehicle_route_info["center_info"] = &rfg::vehicle_route_info::center_info;
    vehicle_route_info["bumper_info"] = &rfg::vehicle_route_info::bumper_info;
    vehicle_route_info["num_route_segments"] = &rfg::vehicle_route_info::num_route_segments;
    vehicle_route_info["flags"] = &rfg::vehicle_route_info::flags;
}

void bind_vehicle_ai_state(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("vehicle_ai_state", "none", rfg::vehicle_ai_state::VS_AI_NONE, "idle",
                   rfg::vehicle_ai_state::VS_AI_IDLE, "pathfind",
                   rfg::vehicle_ai_state::VS_AI_PATHFIND);
}

void bind_vehicle_pathfind_results(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum(
        "vehicle_pathfind_results", "success", rfg::vehicle_pathfind_results::VPF_RESULT_SUCCESS,
        "delayed", rfg::vehicle_pathfind_results::VPF_RESULT_DELAYED, "failure_bad_start",
        rfg::vehicle_pathfind_results::VPF_RESULT_FAILURE_BAD_START, "failure_bad_destination",
        rfg::vehicle_pathfind_results::VPF_RESULT_FAILURE_BAD_DESTINATION, "failure_no_path",
        rfg::vehicle_pathfind_results::VPF_RESULT_FAILURE_NO_PATH);
}

void bind_vehicle_pathfind_record(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_pathfind_record = table.new_usertype<rfg::vehicle_pathfind_record>(
        "vehicle_pathfind_record", sol::no_constructor);
    vehicle_pathfind_record["start"] = &rfg::vehicle_pathfind_record::start;
    vehicle_pathfind_record["dest"] = &rfg::vehicle_pathfind_record::dest;
    vehicle_pathfind_record["result"] = &rfg::vehicle_pathfind_record::result;
}

void bind_repulsor_lateral_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto repulsor_lateral_info = table.new_usertype<rfg::repulsor_lateral_info>(
        "repulsor_lateral_info", sol::no_constructor);
    repulsor_lateral_info["plane_left"] = &rfg::repulsor_lateral_info::plane_left;
    repulsor_lateral_info["plane_right"] = &rfg::repulsor_lateral_info::plane_right;
    repulsor_lateral_info["box_left"] = &rfg::repulsor_lateral_info::box_left;
    repulsor_lateral_info["box_right"] = &rfg::repulsor_lateral_info::box_right;
    repulsor_lateral_info["box_back"] = &rfg::repulsor_lateral_info::box_back;
    repulsor_lateral_info["angle_with_fvec"] = &rfg::repulsor_lateral_info::angle_with_fvec;
    repulsor_lateral_info["start_width_offset"] = &rfg::repulsor_lateral_info::start_width_offset;
}

void bind_vehicle_repulsor_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_repulsor_info = table.new_usertype<rfg::vehicle_repulsor_info>(
        "vehicle_repulsor_info", sol::no_constructor);
    vehicle_repulsor_info["lateral_info"] = &rfg::vehicle_repulsor_info::lateral_info;
    vehicle_repulsor_info["affected_by_repulsors"] =
        &rfg::vehicle_repulsor_info::affected_by_repulsors;
    vehicle_repulsor_info["num_path_repulsors"] = &rfg::vehicle_repulsor_info::num_path_repulsors;
    vehicle_repulsor_info["vpath_repulsor_handles"] =
        &rfg::vehicle_repulsor_info::vpath_repulsor_handles;
    vehicle_repulsor_info["vpath_repulsor_time"] = &rfg::vehicle_repulsor_info::vpath_repulsor_time;
    vehicle_repulsor_info["path_repulsors_collection_time"] =
        &rfg::vehicle_repulsor_info::path_repulsors_collection_time;
}

void bind_path_outcome(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("path_outcome", "unknown", rfg::path_outcome::PR_UNKNOWN, "ok",
                   rfg::path_outcome::PR_OK, "out_of_chunk", rfg::path_outcome::PR_OUT_OF_CHUNK,
                   "start_navcell", rfg::path_outcome::PR_ERROR_START_NAVCELL, "end_navcell",
                   rfg::path_outcome::PR_ERROR_END_NAVCELL, "error_degenerate",
                   rfg::path_outcome::PR_ERROR_DEGENERATE, "error_detour_hull",
                   rfg::path_outcome::PR_ERROR_DETOUR_HULL, "error_water",
                   rfg::path_outcome::PR_ERROR_WATER, "error_unknown",
                   rfg::path_outcome::PR_ERROR_UNKNOWN);
}

void bind_vehicle_path_info_flags(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_usertype<rfg::vehicle_path_info_flags>(
        "vehicle_path_info_flags", sol::no_constructor
        // BIND_FLAG(rfg::vehicle_path_info_flags, jumping),
        // BIND_FLAG(rfg::vehicle_path_info_flags, on_bridge),
        // BIND_FLAG(rfg::vehicle_path_info_flags, partial_path),
        // BIND_FLAG(rfg::vehicle_path_info_flags, road_spline_path),
        // BIND_FLAG(rfg::vehicle_path_info_flags, off_road),
        // BIND_FLAG(rfg::vehicle_path_info_flags, use_road_offset),
        // BIND_FLAG(rfg::vehicle_path_info_flags, gps_path),
        // BIND_FLAG(rfg::vehicle_path_info_flags, next_point_inc),
        // BIND_FLAG(rfg::vehicle_path_info_flags, ixc_can_control),
        // BIND_FLAG(rfg::vehicle_path_info_flags, ixc_turning),
        // BIND_FLAG(rfg::vehicle_path_info_flags, ixc_turning_right)
    );
}

void bind_vehicle_path_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_path_info =
        table.new_usertype<rfg::vehicle_path_info>("vehicle_path_info", sol::no_constructor);
    vehicle_path_info["start_pos"] = &rfg::vehicle_path_info::start_pos;
    vehicle_path_info["start_nav_cell_handle"] = &rfg::vehicle_path_info::start_nav_cell_handle;
    vehicle_path_info["end_pos"] = &rfg::vehicle_path_info::end_pos;
    vehicle_path_info["end_nav_cell_handle"] = &rfg::vehicle_path_info::end_nav_cell_handle;
    vehicle_path_info["error_code"] = &rfg::vehicle_path_info::error_code;
    vehicle_path_info["closest_road_spline"] = &rfg::vehicle_path_info::closest_road_spline;
    vehicle_path_info["closest_road_index"] = &rfg::vehicle_path_info::closest_road_index;
    vehicle_path_info["flags"] = &rfg::vehicle_path_info::flags;
}

void bind_navmesh_lane_spline_node(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto navmesh_lane_spline_node = table.new_usertype<rfg::navmesh_lane_spline_node>(
        "navmesh_lane_spline_node", sol::no_constructor);
    navmesh_lane_spline_node["next"] = &rfg::navmesh_lane_spline_node::next;
    navmesh_lane_spline_node["previous"] = &rfg::navmesh_lane_spline_node::prev;
    navmesh_lane_spline_node["lane"] = &rfg::navmesh_lane_spline_node::lane;
}

void bind_clear_debris_states(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("clear_debris_states", "dont", rfg::clear_debris_states::CDS_DONT, "damage_1",
                   rfg::clear_debris_states::CDS_DAMAGE1, "damage_2",
                   rfg::clear_debris_states::CDS_DAMAGE2, "damage_3",
                   rfg::clear_debris_states::CDS_DAMAGE3, "delete",
                   rfg::clear_debris_states::CDS_DELETE);
}

void bind_stuck_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto stuck_info = table.new_usertype<rfg::stuck_info>("stuck_info", sol::no_constructor);
    stuck_info["stuck_threshold_time"] = &rfg::stuck_info::stuck_threshold_time;
    stuck_info["stuck_active_time"] = &rfg::stuck_info::stuck_active_time;
    stuck_info["stuck_clear_time"] = &rfg::stuck_info::stuck_clear_time;
    stuck_info["stuck_pos"] = &rfg::stuck_info::stuck_pos;
    stuck_info["extended_stuck_time"] = &rfg::stuck_info::extended_stuck_time;
    stuck_info["stuck_mass"] = &rfg::stuck_info::stuck_mass;
    stuck_info["stuck_mass_timer"] = &rfg::stuck_info::stuck_mass_timer;
    stuck_info["clear_debris_state"] = &rfg::stuck_info::clear_debris_state;
    stuck_info["clear_debris_timer"] = &rfg::stuck_info::clear_debris_timer;
}

void bind_vehicle_steer_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_steer_info =
        table.new_usertype<rfg::vehicle_steer_info>("vehicle_steer_info", sol::no_constructor);
    vehicle_steer_info["goal_pos"] = &rfg::vehicle_steer_info::goal_pos;
    vehicle_steer_info["curvature_goal"] = &rfg::vehicle_steer_info::curvature_goal;
    vehicle_steer_info["lookahead_dist"] = &rfg::vehicle_steer_info::lookahead_dist;
    vehicle_steer_info["lateral_offset"] = &rfg::vehicle_steer_info::lateral_offset;
    vehicle_steer_info["road_offset"] = &rfg::vehicle_steer_info::road_offset;
    vehicle_steer_info["wheelbase"] = &rfg::vehicle_steer_info::wheelbase;
    vehicle_steer_info["inv_radius_steer"] = &rfg::vehicle_steer_info::inv_radius_steer;
    vehicle_steer_info["vel"] = &rfg::vehicle_steer_info::vel;
    vehicle_steer_info["desired_vel"] = &rfg::vehicle_steer_info::desired_vel;
    vehicle_steer_info["accel_val"] = &rfg::vehicle_steer_info::accel_val;
    vehicle_steer_info["brake_val"] = &rfg::vehicle_steer_info::brake_val;
}

void bind_vehicle_accel_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_accel_info =
        table.new_usertype<rfg::vehicle_accel_info>("vehicle_accel_info", sol::no_constructor);
    vehicle_accel_info["desired_speed"] = &rfg::vehicle_accel_info::desired_speed;
    vehicle_accel_info["desired_braking_decel"] = &rfg::vehicle_accel_info::desired_braking_decel;
}

void bind_vehicle_control_info(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle_control_info =
        table.new_usertype<rfg::vehicle_control_info>("vehicle_control_info", sol::no_constructor);
    vehicle_control_info["max_braking_decel"] = &rfg::vehicle_control_info::max_braking_decel;
    vehicle_control_info["max_radial_accel"] = &rfg::vehicle_control_info::max_radial_accel;
    vehicle_control_info["max_steer_curvature"] = &rfg::vehicle_control_info::max_steer_curvature;
}

void bind_vehicle_ai(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_usertype<rfg::vehicle_ai>("vehicle_ai", sol::no_constructor);
}

void bind_vehicle_seat_info(sol::state_view& lua) {}

void bind_vehicle_turret_mount(sol::state_view& lua) {}

void bind_vehicle_damage_area_type(sol::state_view& lua) {}

void bind_vehicle_damage_area(sol::state_view& lua) {}

void bind_vehicle_damage_event(sol::state_view& lua) {}

void bind_vehicle_navcell_info(sol::state_view& lua) {}

void bind_vehicle_collision_events(sol::state_view& lua) {}

void bind_vehicle_rdd_flags(sol::state_view& lua) {}

void bind_vehicle_bomb_status(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("vehicle_bomb_status", "none", rfg::vehicle_bomb_status::VEHICLE_BOMB_NONE,
                   "armed", rfg::vehicle_bomb_status::VEHICLE_BOMB_ARMED);
}

void bind_vehicle_spawn_flags(sol::state_view& lua) {}

void bind_vehicle_flags(sol::state_view& lua) {}

void bind_vehicle_spawn_params(sol::state_view& lua) {}

void bind_vehicle(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto vehicle = table.new_usertype<rfg::vehicle>("vehicle", sol::no_constructor,
                                                    sol::base_classes, sol::bases<rfg::object>());
    //"rdd", &rfg::vehicle::rdd,
    vehicle["spawn_priority"] = &rfg::vehicle::spawn_priority;
    vehicle["info"] = &rfg::vehicle::info;
    vehicle["last_pos"] = &rfg::vehicle::last_pos;
    vehicle["last_orient"] = &rfg::vehicle::last_orient;
    vehicle["last_velocity"] = &rfg::vehicle::last_velocity;
    vehicle["last_angular_velocity"] = &rfg::vehicle::last_angular_velocity;
    vehicle["forward_velocity"] = &rfg::vehicle::forward_velocity;
    vehicle["last_forward_velocity"] = &rfg::vehicle::last_forward_velocity;
    //"vai", &rfg::vehicle::vai,
    //"instance", &rfg::vehicle::instance,
    vehicle["aim_handle"] = &rfg::vehicle::aim_handle;
    //"vp", &rfg::vehicle::vp,
    vehicle["last_anim_transform"] = &rfg::vehicle::last_anim_transform;
    vehicle["pf_failure_timeout"] = &rfg::vehicle::pf_failure_timeout;
    vehicle["disable_for_npc_drivers_timer"] = &rfg::vehicle::disable_for_npc_drivers_timer;
    vehicle["no_npc_entry_timer"] = &rfg::vehicle::no_npc_entry_timer;
    vehicle["render_distance"] = &rfg::vehicle::render_distance;
    vehicle["m_seat_info"] = &rfg::vehicle::m_seat_info;
    vehicle["m_damage_areas"] = &rfg::vehicle::m_damage_areas;
    vehicle["m_num_turret_mounts"] = &rfg::vehicle::m_num_turret_mounts;
    vehicle["m_turret_mounts"] = &rfg::vehicle::m_turret_mounts;
    vehicle["m_bomb_status"] = &rfg::vehicle::m_bomb_status;
    //"m_collisions_this_frame", &rfg::vehicle::m_collisions_this_frame,
    vehicle["m_walker_velocity_hack"] = &rfg::vehicle::m_walker_velocity_hack;
    vehicle["m_walker_velocity_hack_followup"] = &rfg::vehicle::m_walker_velocity_hack_followup;
    vehicle["m_walker_thrown_energy_scaled"] = &rfg::vehicle::m_walker_thrown_energy_scaled;
    vehicle["saved_angular_dampening"] = &rfg::vehicle::saved_angular_dampening;
    //"walker_vehicle_collisions", &rfg::vehicle::walker_vehicle_collisions,
    vehicle["m_vehicle_vs_building_damage"] = &rfg::vehicle::m_vehicle_vs_building_damage;
    vehicle["damage_events"] = &rfg::vehicle::damage_events;
    vehicle["num_damage_events"] = &rfg::vehicle::num_damage_events;
    //"damage_events_cs", &rfg::vehicle::damage_events_cs,
    vehicle["m_corpse_timer"] = &rfg::vehicle::m_corpse_timer;
    vehicle["m_corpse_absolute_longest_timer"] = &rfg::vehicle::m_corpse_absolute_longest_timer;
    vehicle["on_fire_timestamp"] = &rfg::vehicle::on_fire_timestamp;
    vehicle["m_corpse_effect"] = &rfg::vehicle::m_corpse_effect;
    vehicle["m_exhaust_effect_normal"] = &rfg::vehicle::m_exhaust_effect_normal;
    vehicle["m_exhaust_effect_burst"] = &rfg::vehicle::m_exhaust_effect_burst;
    vehicle["m_flags"] = &rfg::vehicle::m_flags;
    vehicle["m_turret_autofire_ms"] = &rfg::vehicle::m_turret_autofire_ms;
    vehicle["m_num_sub_pieces"] = &rfg::vehicle::m_num_sub_pieces;
    vehicle["stream_placement_flags"] = &rfg::vehicle::stream_placement_flags;
    vehicle["m_rdd_flags"] = &rfg::vehicle::m_rdd_flags;
    vehicle["m_killer_handle"] = &rfg::vehicle::m_killer_handle;
    vehicle["most_recent_driver"] = &rfg::vehicle::most_recent_driver;
    vehicle["team_of_most_recent_driver"] = &rfg::vehicle::team_of_most_recent_driver;
    vehicle["most_recent_driver_exit_time"] = &rfg::vehicle::most_recent_driver_exit_time;
    vehicle["damage_sound_propagate_timer"] = &rfg::vehicle::damage_sound_propagate_timer;
    vehicle["m_killer_weapon"] = &rfg::vehicle::m_killer_weapon;
    vehicle["ramming_damage_taken"] = &rfg::vehicle::ramming_damage_taken;
    vehicle["m_electrical_damage_percent"] = &rfg::vehicle::m_electrical_damage_percent;
    vehicle["damage_percent"] = &rfg::vehicle::damage_percent;
    vehicle["damage_func_handle"] = &rfg::vehicle::damage_func_handle;
    vehicle["destroy_func_handle"] = &rfg::vehicle::destroy_func_handle;
    vehicle["on_enter_func_handle"] = &rfg::vehicle::on_enter_func_handle;
    vehicle["on_exit_func_handle"] = &rfg::vehicle::on_exit_func_handle;
    vehicle["on_take_damage_handle"] = &rfg::vehicle::on_take_damage_handle;
    vehicle["on_collision_handle"] = &rfg::vehicle::on_collision_handle;
    vehicle["on_hit_ped_handle"] = &rfg::vehicle::on_hit_ped_handle;
    vehicle["reserved_by"] = &rfg::vehicle::reserved_by;
    vehicle["m_sound_delay_after_explosion"] = &rfg::vehicle::m_sound_delay_after_explosion;
    vehicle["m_fire_damage_rate"] = &rfg::vehicle::m_fire_damage_rate;
    vehicle["m_fire_fractional_damage"] = &rfg::vehicle::m_fire_fractional_damage;
    vehicle["m_fade_timer"] = &rfg::vehicle::m_fade_timer;
    vehicle["m_fade_time"] = &rfg::vehicle::m_fade_time;
    vehicle["m_num_mesh_deform_spheres"] = &rfg::vehicle::m_num_mesh_deform_spheres;
    //"m_mesh_deform_sphere_list", &rfg::vehicle::m_mesh_deform_sphere_list,
    //"m_mesh_deform_pending_list", &rfg::vehicle::m_mesh_deform_pending_list,
    vehicle["m_tag_deform_weights"] = &rfg::vehicle::m_tag_deform_weights;
    vehicle["m_navcell_info"] = &rfg::vehicle::m_navcell_info;
    vehicle["emergency_light_timer"] = &rfg::vehicle::emergency_light_timer;
    vehicle["stream_load_distance_sqr"] = &rfg::vehicle::stream_load_distance_sqr;
    vehicle["stream_unload_distance_sqr"] = &rfg::vehicle::stream_unload_distance_sqr;
    vehicle["engine_inst"] = &rfg::vehicle::engine_inst;
    vehicle["engine_started_inst"] = &rfg::vehicle::engine_started_inst;
    vehicle["engine_high_load_start_timer"] = &rfg::vehicle::engine_high_load_start_timer;
    vehicle["pass_by_play_id"] = &rfg::vehicle::pass_by_play_id;
    vehicle["pass_by_distance"] = &rfg::vehicle::pass_by_distance;
    vehicle["m_nav_cell_detour_request_handle"] = &rfg::vehicle::m_nav_cell_detour_request_handle;
    vehicle["m_nav_cell_detour_component_request_handles"] =
        &rfg::vehicle::m_nav_cell_detour_component_request_handles;
    vehicle["m_num_nav_cell_detour_component_request_handles"] =
        &rfg::vehicle::m_num_nav_cell_detour_component_request_handles;
    vehicle["last_damage_reported"] = &rfg::vehicle::last_damage_reported;
    vehicle["spawn_node_handle"] = &rfg::vehicle::spawn_node_handle;
    vehicle["squad_handle"] = &rfg::vehicle::squad_handle;
    vehicle["vehicle_check_cover_timestamp"] = &rfg::vehicle::vehicle_check_cover_timestamp;
    vehicle["vehicle_cover_timestamp"] = &rfg::vehicle::vehicle_cover_timestamp;
    vehicle["vehicle_cover_creation_pos"] = &rfg::vehicle::vehicle_cover_creation_pos;
    vehicle["vehicle_cover_nodes"] = &rfg::vehicle::vehicle_cover_nodes;
    vehicle["vehicle_check_cover_index"] = &rfg::vehicle::vehicle_check_cover_index;
    vehicle["vehicle_cover_index"] = &rfg::vehicle::vehicle_cover_index;
    //"component_rinstance_cs", &rfg::vehicle::component_rinstance_cs,
    vehicle["infinite_mass"] = &rfg::vehicle::infinite_mass;
    vehicle["extra_mass"] = &rfg::vehicle::extra_mass;
    vehicle["extra_mass_value"] = &rfg::vehicle::extra_mass_value;
}

void bind_walker_flags(sol::state_view& lua) {}

void bind_walker_resource_dependent_data(sol::state_view& lua) {}

void bind_walker_component_info(sol::state_view& lua) {}

void bind_walker_ik_joint_location(sol::state_view& lua) {}

void bind_walker_ik_joint(sol::state_view& lua) {}

void bind_walker_mp_data(sol::state_view& lua) {}

void bind_mp_x_collision_prediction_info(sol::state_view& lua) {}

void bind_walker_model_type(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("walker_model_type", "small", rfg::walker_model_type::WMT_SMALL, "flame",
                   rfg::walker_model_type::WMT_FLAME, "civilian",
                   rfg::walker_model_type::WMT_CIVILIAN);
}

void bind_walker_control_scheme(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_enum("walker_control_scheme", "facing_camera",
                   rfg::walker_control_scheme::WCS_FACING_CAMERA, "character_style",
                   rfg::walker_control_scheme::WCS_CHARACTER_STYLE);
}

void bind_walker(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto walker_resource_dependent_data = table.new_usertype<rfg::walker_resource_dependent_data>(
        "walker_resource_dependent_data", sol::no_constructor);
    walker_resource_dependent_data["left_foot_component_idx"] =
        &rfg::walker_resource_dependent_data::left_foot_component_idx;
    walker_resource_dependent_data["right_foot_component_idx"] =
        &rfg::walker_resource_dependent_data::right_foot_component_idx;

    table.new_usertype<rfg::walker_component_info>("walker_component_info", sol::no_constructor);

    table.new_usertype<rfg::walker_ik_joint>("walker_ik_joint", sol::no_constructor);

    table.new_usertype<rfg::walker_mp_data>("walker_mp_data", sol::no_constructor);

    table.new_usertype<rfg::mp_x_collision_prediction_info>("mp_x_collision_prediction_info",
                                                            sol::no_constructor);

    auto walker = table.new_usertype<rfg::walker>("walker", sol::no_constructor, sol::base_classes,
                                                  sol::bases<rfg::vehicle, rfg::object>());
    walker["walker_rdd"] = &rfg::walker::walker_rdd;
    walker["walker_flags"] = &rfg::walker::walker_flags;
    walker["chassis_pos"] = &rfg::walker::chassis_pos;
    walker["chassis_orient"] = &rfg::walker::chassis_orient;
    walker["collision_model"] = &rfg::walker::collision_model;
    walker["hull_radius"] = &rfg::walker::hull_radius;
    //"comp_info", &rfg::walker::comp_info,
    //"comp_transform_order", &rfg::walker::comp_transform_order,
    walker["steering_vector"] = &rfg::walker::steering_vector;
    walker["move_speed"] = &rfg::walker::move_speed;
    walker["cur_rotation_speed"] = &rfg::walker::cur_rotation_speed;
    walker["desired_move_speed"] = &rfg::walker::desired_move_speed;
    walker["input_velocity"] = &rfg::walker::input_velocity;
    walker["chassis_pos_last_frame"] = &rfg::walker::chassis_pos_last_frame;
    walker["actual_velocity"] = &rfg::walker::actual_velocity;
    walker["actual_velocity_mag"] = &rfg::walker::actual_velocity_mag;
    walker["vertical_anim_speed"] = &rfg::walker::vertical_anim_speed;
    walker["y_offset"] = &rfg::walker::y_offset;
    walker["mount_vector"] = &rfg::walker::mount_vector;
    walker["mount_vehicle"] = &rfg::walker::mount_vehicle;
    walker["ground_obj_handle"] = &rfg::walker::ground_obj_handle;
    walker["last_ground_obj_handle"] = &rfg::walker::last_ground_obj_handle;
    walker["ground_normal"] = &rfg::walker::ground_normal;
    walker["ground_world_pos"] = &rfg::walker::ground_world_pos;
    walker["ground_test_ts"] = &rfg::walker::ground_test_ts;
    walker["ground_impact_momentum"] = &rfg::walker::ground_impact_momentum;
    walker["ram_momentum"] = &rfg::walker::ram_momentum;
    walker["ram_max_energy_used"] = &rfg::walker::ram_max_energy_used;
    walker["jump_jet_energy"] = &rfg::walker::jump_jet_energy;
    walker["jump_jet_speed"] = &rfg::walker::jump_jet_speed;
    walker["jump_jet_engage_time"] = &rfg::walker::jump_jet_engage_time;
    walker["jump_jet_tag_idx"] = &rfg::walker::jump_jet_tag_idx;
    walker["jump_jet_effect"] = &rfg::walker::jump_jet_effect;
    walker["jump_jet_foley"] = &rfg::walker::jump_jet_foley;
    walker["jump_jet_foley_disable"] = &rfg::walker::jump_jet_foley_disable;
    walker["jump_timeout"] = &rfg::walker::jump_timeout;
    walker["engine_load"] = &rfg::walker::engine_load;
    walker["time_since_last_supported"] = &rfg::walker::time_since_last_supported;
    walker["model_type"] = &rfg::walker::model_type;
    walker["control_scheme"] = &rfg::walker::control_scheme;
    walker["block_movement_anim"] = &rfg::walker::block_movement_anim;
    walker["block_movement_type"] = &rfg::walker::block_movement_type;
    //"ik_joints", &rfg::walker::ik_joints,
    //"mp_sim_state", &rfg::walker::mp_sim_state,
    //"mp_data", &rfg::walker::mp_data,
    //"mp_collision_prediction", &rfg::walker::mp_collision_prediction
}

void bind_mp_collision_prediction_info(sol::state_view& lua) {}

void bind_automobile(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto automobile =
        table.new_usertype<rfg::automobile>("automobile", sol::no_constructor, sol::base_classes,
                                            sol::bases<rfg::vehicle, rfg::object>());
    //"automobile_rdd", &rfg::automobile::automobile_rdd,
    //"m_wheel_effect_infos", &rfg::automobile::m_wheel_effect_infos,
    automobile["m_motion_foley"] = &rfg::automobile::m_motion_foley;
    automobile["m_tread_foley"] = &rfg::automobile::m_tread_foley;
    //"m_decal_collection_data", &rfg::automobile::m_decal_collection_data,
    automobile["m_num_decal_collections"] = &rfg::automobile::m_num_decal_collections;
    automobile["m_decal_width"] = &rfg::automobile::m_decal_width;
    automobile["m_decal_collection_occurred"] = &rfg::automobile::m_decal_collection_occurred;
    automobile["m_wheel_effect_stopped_timer"] = &rfg::automobile::m_wheel_effect_stopped_timer;
    automobile["m_wheel_effect_is_stopped"] = &rfg::automobile::m_wheel_effect_is_stopped;
    automobile["honk_alr_id"] = &rfg::automobile::honk_alr_id;
    automobile["foley_siren"] = &rfg::automobile::foley_siren;
    automobile["foley_megaphone"] = &rfg::automobile::foley_megaphone;
    automobile["foley_chassis"] = &rfg::automobile::foley_chassis;
    automobile["engine_peel"] = &rfg::automobile::engine_peel;
    automobile["gear_shift"] = &rfg::automobile::gear_shift;
    automobile["user_acc_input"] = &rfg::automobile::user_acc_input;
    automobile["time_at_max_speed"] = &rfg::automobile::time_at_max_speed;
    automobile["play_shift_foley"] = &rfg::automobile::play_shift_foley;
    automobile["horn_timeout"] = &rfg::automobile::horn_timeout;
    //"m_collision_impact_sounds", &rfg::automobile::m_collision_impact_sounds,
    //"m_collision_scraping_sounds", &rfg::automobile::m_collision_scraping_sounds,
    automobile["m_impact_sound_delay"] = &rfg::automobile::m_impact_sound_delay;
    automobile["m_scraping_sound_delay"] = &rfg::automobile::m_scraping_sound_delay;
    automobile["m_chassis_sound_delay"] = &rfg::automobile::m_chassis_sound_delay;
    automobile["brake_effect_release_timer"] = &rfg::automobile::brake_effect_release_timer;
    automobile["catch_fire_timestamp"] = &rfg::automobile::catch_fire_timestamp;
    automobile["m_h_trailer_vehicle"] = &rfg::automobile::m_h_trailer_vehicle;
    automobile["m_h_tractor_vehicle"] = &rfg::automobile::m_h_tractor_vehicle;
    automobile["prev_chassis_stress"] = &rfg::automobile::prev_chassis_stress;
    automobile["max_chassis_stress"] = &rfg::automobile::max_chassis_stress;
    automobile["is_airborne"] = &rfg::automobile::is_airborne;
    automobile["is_landing"] = &rfg::automobile::is_landing;
    automobile["is_skipping"] = &rfg::automobile::is_skipping;
    automobile["is_skiprecovery"] = &rfg::automobile::is_skiprecovery;
    automobile["force_assist_value"] = &rfg::automobile::force_assist_value;
    automobile["powerslide_amount"] = &rfg::automobile::powerslide_amount;
    automobile["current_powerslide_friction"] = &rfg::automobile::current_powerslide_friction;
    automobile["powerslide_was_handbrake_on"] = &rfg::automobile::powerslide_was_handbrake_on;
    automobile["mp_sim_state"] = &rfg::automobile::mp_sim_state;
    automobile["mp_collision_prediction"] = &rfg::automobile::mp_collision_prediction;
}

void bind_flyer_control_action(sol::state_view& lua) {}

void bind_flyer_flags(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    table.new_usertype<rfg::flyer_flags>("flyer_flags", sol::no_constructor
                                         // BIND_FLAG(rfg::flyer_flags, landing_gear_up),
                                         // BIND_FLAG(rfg::flyer_flags, landing_gear_collision_off),
                                         // BIND_FLAG(rfg::flyer_flags, needs_to_takeoff),
                                         // BIND_FLAG(rfg::flyer_flags, has_lift),
                                         // BIND_FLAG(rfg::flyer_flags, stay_at_constant_height),
                                         // BIND_FLAG(rfg::flyer_flags, on_ground)
    );
}

void bind_flyer(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto flyer = table.new_usertype<rfg::flyer>("flyer", sol::no_constructor, sol::base_classes,
                                                sol::bases<rfg::vehicle, rfg::object>());
    //"flyer_rdd", &rfg::flyer::flyer_rdd,
    //"ctl_action", &rfg::flyer::ctl_action,
    flyer["request_urgency"] = &rfg::flyer::request_urgency;
    flyer["request_max_vel"] = &rfg::flyer::request_max_vel;
    flyer["request_point"] = &rfg::flyer::request_point;
    flyer["request_vel"] = &rfg::flyer::request_vel;
    flyer["request_lookat"] = &rfg::flyer::request_lookat;
    flyer["request_point_is_valid"] = &rfg::flyer::request_point_is_valid;
    flyer["request_vel_is_valid"] = &rfg::flyer::request_vel_is_valid;
    flyer["request_lookat_is_valid"] = &rfg::flyer::request_lookat_is_valid;
    flyer["request_stop_at_point"] = &rfg::flyer::request_stop_at_point;
    flyer["request_halt"] = &rfg::flyer::request_halt;
    flyer["wing_is_detached"] = &rfg::flyer::wing_is_detached;
    flyer["vehicle_mass"] = &rfg::flyer::vehicle_mass;
    flyer["chassis_com_cs"] = &rfg::flyer::chassis_com_cs;
    flyer["chassis_com_ws"] = &rfg::flyer::chassis_com_ws;
    flyer["thrust_mat_cs"] = &rfg::flyer::thrust_mat_cs;
    flyer["thrust_mat_ws"] = &rfg::flyer::thrust_mat_ws;
    flyer["thrust_up_target"] = &rfg::flyer::thrust_up_target;
    flyer["hover_noise_vec"] = &rfg::flyer::hover_noise_vec;
    flyer["hover_noise_vec_new"] = &rfg::flyer::hover_noise_vec_new;
    flyer["hover_noise_vec_old"] = &rfg::flyer::hover_noise_vec_old;
    flyer["hover_noise_timer"] = &rfg::flyer::hover_noise_timer;
    flyer["hover_noise_dur"] = &rfg::flyer::hover_noise_dur;
    flyer["engine_off_suspension_period"] = &rfg::flyer::engine_off_suspension_period;
    flyer["turbine_rpm_target"] = &rfg::flyer::turbine_rpm_target;
    flyer["turbine_rpm"] = &rfg::flyer::turbine_rpm;
    flyer["turbine_load"] = &rfg::flyer::turbine_load;
    flyer["left_wing"] = &rfg::flyer::left_wing;
    flyer["right_wing"] = &rfg::flyer::right_wing;
    flyer["left_canard"] = &rfg::flyer::left_canard;
    flyer["right_canard"] = &rfg::flyer::right_canard;
    flyer["wingtip_effect"] = &rfg::flyer::wingtip_effect;
    flyer["front_thruster"] = &rfg::flyer::front_thruster;
    flyer["center_thruster"] = &rfg::flyer::center_thruster;
    flyer["main_engines"] = &rfg::flyer::main_engines;
    flyer["jetwash"] = &rfg::flyer::jetwash;
    flyer["engine_force"] = &rfg::flyer::engine_force;
    flyer["startup_timer"] = &rfg::flyer::startup_timer;
    flyer["last_player_damage"] = &rfg::flyer::last_player_damage;
    flyer["catch_fire_timer"] = &rfg::flyer::catch_fire_timer;
    flyer["flags"] = &rfg::flyer::flags;
}

} // namespace rfg
