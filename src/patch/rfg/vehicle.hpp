#pragma once

#include "patch/rfg/havok.hpp"
#include "patch/rfg/human.hpp"
#include "patch/rfg/object.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {

struct vehicle_exit_data_flags {
    __int8 teleport : 1;
    __int8 maintain_position : 1;
    __int8 reexit : 1;
    __int8 last_exit_failed : 1;
    __int8 force_dive_exit : 1;
};

struct vehicle_exit_data {
    vehicle_exit_data_flags flags;
};

enum vehicle_seat_selection_method {
    VI_SEAT_SELECTION_METHOD_NONE = 0xFFFFFFFF,
    VI_SEAT_SELECTION_METHOD_SPECIFIED = 0x0,
    VI_SEAT_SELECTION_METHOD_BEST = 0x1,
    NUM_VI_SEAT_SELECTION_METHODS = 0x2,
};

struct vehicle_enter_data_flags {
    __int8 teleport : 1;
    __int8 walk : 1;
    __int8 minimal_processing : 1;
    __int8 reserve_seat_only : 1;
    __int8 use_pf_path : 1;
    __int8 teleport_to_door : 1;
};

struct __attribute__((aligned(4))) vehicle_enter_data {
    vehicle_seat_index specified_seat;
    vehicle_seat_selection_method seat_selection_method;
    vehicle_seat_index destination_seat;
    vehicle_enter_data_flags flags;
};

enum vehicle_class_type {
    VCL_AUTOMOBILE = 0x0,
    VCL_FLYER = 0x1,
    VCL_WALKER = 0x2,
    NUM_VEHICLE_CLASSES = 0x3,
};

enum base_vehicle_type {
    BVT_INVALID = 0xFFFFFFFF,
    BVT_NONE = 0x0,
    BVT_COURIER = 0x1,
    BVT_AMBULANCE = 0x2,
    BVT_TANK = 0x3,
    BVT_ART_TANK = 0x4,
    BVT_BOMBER = 0x5,
    BVT_SPECIAL = 0x6,
    NUM_BASE_VEHICLE_TYPES = 0x7,
};

enum vehicle_road_preference {
    VRP_NONE = 0x0,
    VRP_HIGHWAY = 0x1,
    VRP_NO_HIGHWAY = 0x2,
    NUM_VEHICLE_ROAD_PREFERENCE_TYPES = 0x3,
};

struct lod_info {
    float dist;
};

struct animlib_bones_used_info {
    int unique_id;
    int num_bones;
    unsigned int* bone_indices;
};

struct __attribute__((aligned(4))) vehicle_camera_settings {
    vector lookat_offset;
    vector lookat_vehicle_offset;
    vector lookat_vehicle_enter_offset;
    float lookfrom_height;
    float enter_distance;
    float follow_dist;
    float follow_height;
    float y_axis_rotation_speed;
    float camera_steer_angle;
    float camera_steer_speed;
    bool turret_camera;
    bool force_turret_cam;
};

struct vehicle_turret_mount_info {
    const char* name;
    const char* prop_point;
    vehicle_seat_index seat;
    unsigned int flags;
    void* attached_turret_info; // turret_info *attached_turret_info;
};

struct vehicle_axle_wheel_info {
    bool does_steer;
    bool does_handbrake;
    float engine_torque_factor;
    float mass;
    float friction;
    float ai_friction;
    float braking_torque;
    float spring_compression;
    float spring_extension;
    float spring_strength;
    float spring_power;
    float compression_damping;
    float expansion_damping;
};

struct vehicle_transmission_info {
    unsigned int num_gears;
    float gear_ratios[6];
    float downshift_rpms[5];
    float upshift_rpms[5];
    float differential_gear_ratio;
    float reverse_gear_ratio;
    float clutch_delay;
    float clutch_delay_pre_shift;
    unsigned int forward_to_reverse_delay;
    unsigned int reverse_to_forward_delay;
};

struct vehicle_info_flags {
    __int8 preload : 1;
    __int8 can_block_roads : 1;
    __int8 force_break_links : 1;
    __int8 seat_count_warning : 1;
    __int8 is_walker_flamer : 1;
};

struct __attribute__((aligned(4))) vehicle_info {
    const char* name;
    const char* display_name;
    const char* mesh_name;
    vehicle_class_type vehicle_class;
    float spawn_size;
    bbox spawn_box;
    void* cover_info; // vehicle_cover_info *cover_info;
    int slot_id;
    unsigned int srid;
    const char* variant_family;
    base_vehicle_type vehicle_classification;
    team default_team;
    void* vi_info; // vehicle_interaction_info *vi_info;
    unsigned int m_max_hitpoints;
    int m_abandon_hitpoints;
    float chassis_mass;
    float m_value;
    unsigned int m_chop_shop_props;
    unsigned int m_num_lods;
    lod_info m_lod_info[4];
    int num_turret_mounts;
    vehicle_turret_mount_info turret_mounts[2];
    vehicle_road_preference m_road_preference;
    float engine_torque;
    float ai_engine_torque;
    float min_rpm;
    float optimal_rpm;
    float max_rpm;
    float min_rpm_torque_factor;
    float max_rpm_torque_factor;
    float min_rpm_resistance;
    float opt_rpm_resistance;
    float max_rpm_resistance;
    float reverse_torque_multiplier;
    float clutch_slip_rpm;
    float enlarged_wheel_radius;
    float autobrake_speed;
    float enforced_max_speed;
    float ai_enforced_max_speed;
    float enforced_max_rspeed;
    float powerslide_friction;
    float powerslide_power;
    float force_assist;
    unsigned int m_num_axles;
    vehicle_axle_wheel_info m_axle_wheel_infos[4];
    int m_exhaust_tag_id[4];
    vehicle_transmission_info trans_info;
    float max_steering_angle;
    float max_speed_steering_angle;
    float ai_max_speed_steering_angle;
    float m_steering_wheel_max_speed;
    float m_steering_wheel_max_return_speed;
    float m_steering_wheel_damp_angle;
    float m_steering_wheel_return_damp_angle;
    float counter_steer_min_speed;
    float counter_steer_max_speed;
    float air_steer_roll_max_vel;
    float air_steer_roll_max_angle_rad;
    float air_steer_pitch_max_vel;
    float air_steer_pitch_max_angle_rad;
    float min_pedal_input_to_block;
    float min_time_to_block;
    float ai_min_time_to_block;
    float air_density;
    float frontal_area;
    float drag_coefficient;
    float lift_coefficient;
    float extra_gravity;
    float center_of_mass_y;
    float center_of_mass_z;
    vehicle_camera_settings camera_settings[3];
    int camera_settings_count;
    float m_energy_scale;
    float m_collision_mass_scalar;
    float m_collision_damage_scale;
    float m_terrain_damage_scale;
    float m_bullet_damage_scale;
    float m_vehicle_damage_scale;
    float m_friction_equalizer;
    float m_ai_friction_equalizer;
    float m_torque_roll_factor;
    float m_torque_pitch_factor;
    float m_torque_yaw_factor;
    float m_torque_yaw_scalar;
    float m_extra_torque_factor;
    float m_chassis_unit_inertia_roll;
    float m_chassis_unit_inertia_pitch;
    float m_chassis_unit_inertia_yaw;
    float m_ai_chassis_unit_inertia_yaw;
    float m_viscosity_friction;
    float m_ai_max_braking_decel;
    float m_ai_max_radial_accel;
    float m_alert_multiplier;
    int foley_start;
    int engine_id;
    __int16 engine_wavebank_id;
    int foley_off;
    int foley_engine_peel;
    int foley_shift;
    int foley_grind;
    int foley_honk;
    int m_foley_impact_id[2];
    int m_foley_scraping_id;
    int m_foley_corpse_impact_id;
    int m_foley_component_impact_id;
    int m_foley_wheel_impact_id;
    int m_foley_chassis_land_id[2];
    int m_foley_pass_by;
    int m_foley_door_open_id;
    int m_foley_door_close_id;
    unsigned int m_effect_engine_fire;
    unsigned int m_effect_engine_smoke;
    unsigned int m_effect_corpse_smoke;
    unsigned int m_effect_component_fire;
    unsigned int m_effect_exhaust_normal;
    unsigned int m_effect_exhaust_burst;
    unsigned int m_effect_collision;
    unsigned int m_effect_scrape;
    unsigned int m_effect_component_detach;
    unsigned int m_effect_head_light_primary;
    unsigned int m_effect_head_light_secondary;
    unsigned int m_effect_fog_light;
    unsigned int m_effect_tail_light;
    unsigned int m_effect_brake_light;
    unsigned int m_effect_reverse_light;
    unsigned int m_effect_emergency_light;
    unsigned int m_effect_strobe_light;
    explosion_info* m_explosion_info;
    explosion_info* m_bomb_explosion_info;
    unsigned int m_num_variants;
    float m_normal_spin_damping;
    float m_normal_spin_damping_ai;
    float m_collision_spin_damping;
    float m_collision_spin_threshold;
    float m_camera_fov_multiplier;
    float m_camera_fov_min_speed;
    float m_camera_shake_min_speed;
    float m_radial_blur_max;
    float m_radial_blur_min_speed;
    float m_trailer_chance;
    const char* rig_name;
    const char* anim_set_name;
    foot_ground_effect* footstep_effects;
    animlib_bones_used_info bones_used_info;
    float flyer_max_up_thrust;
    float flyer_max_turn_angvel;
    float flyer_max_turn_angaccl;
    float flyer_max_thrust_offset_x;
    float flyer_max_thrust_offset_z;
    float flyer_max_tilt_angvel;
    float flyer_max_tilt_angaccl;
    float flyer_spin_bank_scalar;
    float flyer_thrust_tilt_scalar;
    float flyer_bank_tilt_scalar;
    float flyer_def_lookat_y_scalar;
    unsigned int flyer_wingtip_effect;
    unsigned int flyer_thruster_effect;
    unsigned int flyer_mainengine_effect;
    unsigned int flyer_jetwash_effect;
    vehicle_info_flags flags;
};

struct lane_spline_base {
    et_ptr_offset<vector, 0> knots;
    et_ptr_offset<vector, 0> in_handles;
    et_ptr_offset<vector, 0> out_handles;
    __int16 num_knots;
    __int16 spline_flags;
    float arc_length[2];
};

struct route_segment_flags {
    __int8 terminal : 1;
    __int8 from_ambient_path : 1;
    __int8 from_navmesh_path : 1;
    __int8 signal_processed : 1;
    __int8 stopped_for_sign : 1;
};

struct __attribute__((aligned(2))) route_segment {
    cubic_bezier_spline cb_spline;
    float length;
    float speed_limit;
    lane_spline_base* base_spline;
    __int16 num_knots_minus_one;
    route_segment_flags flags;
};

struct vehicle_point_info {
    int route_index;
    float u;
    float distance_remaining;
};

struct vehicle_route_info_flags {
    __int8 m_route_segment_inited : 1;
};

struct __attribute__((aligned(2))) vehicle_route_info {
    route_segment route[5];
    lane_spline_base* last_next_spline;
    vehicle_point_info center_info;
    vehicle_point_info bumper_info;
    __int16 num_route_segments;
    vehicle_route_info_flags flags;
};

enum vehicle_ai_state {
    VS_AI_NONE = 0xFFFFFFFF,
    VS_AI_IDLE = 0x0,
    VS_AI_PATHFIND = 0x1,
    NUM_VEHICLE_AI_STATES = 0x2,
};

enum vehicle_pathfind_results {
    VPF_RESULT_SUCCESS = 0x0,
    VPF_RESULT_DELAYED = 0x1,
    VPF_RESULT_FAILURE_BAD_START = 0x2,
    VPF_RESULT_FAILURE_BAD_DESTINATION = 0x3,
    VPF_RESULT_FAILURE_NO_PATH = 0x4,
    NUM_VEHICLE_PATHFIND_RESULTS = 0x5,
};

struct vehicle_pathfind_record {
    vector start;
    vector dest;
    vehicle_pathfind_results result;
};

struct repulsor_lateral_info {
    plane plane_left;
    plane plane_right;
    plane box_left;
    plane box_right;
    plane box_back;
    float angle_with_fvec;
    float start_width_offset;
};

struct vehicle_repulsor_info {
    repulsor_lateral_info lateral_info;
    char affected_by_repulsors;
    char num_path_repulsors;
    unsigned int vpath_repulsor_handles[10];
    timestamp vpath_repulsor_time[10];
    timestamp path_repulsors_collection_time;
};

enum path_outcome {
    PR_UNKNOWN = 0x0,
    PR_OK = 0x1,
    PR_OUT_OF_CHUNK = 0x2,
    PR_ERROR_START_NAVCELL = 0x3,
    PR_ERROR_END_NAVCELL = 0x4,
    PR_ERROR_DEGENERATE = 0x5,
    PR_ERROR_DETOUR_HULL = 0x6,
    PR_ERROR_WATER = 0x7,
    PR_ERROR_UNKNOWN = 0x8,
};

struct vehicle_path_info_flags {
    __int8 jumping : 1;
    __int8 on_bridge : 1;
    __int8 partial_path : 1;
    __int8 road_spline_path : 1;
    __int8 off_road : 1;
    __int8 use_road_offset : 1;
    __int8 gps_path : 1;
    __int8 next_point_inc : 1;
    __int8 ixc_can_control : 1;
    __int8 ixc_turning : 1;
    __int8 ixc_turning_right : 1;
};

struct __attribute__((aligned(4))) vehicle_path_info {
    vector start_pos;
    unsigned __int64 start_nav_cell_handle;
    vector end_pos;
    unsigned __int64 end_nav_cell_handle;
    path_outcome error_code;
    unsigned int closest_road_spline;
    float closest_road_index;
    vehicle_path_info_flags flags;
};

struct navmesh_lane_spline_node {
    navmesh_lane_spline_node* next;
    navmesh_lane_spline_node* prev;
    lane_spline_base lane;
};

enum clear_debris_states {
    CDS_DONT = 0x0,
    CDS_DAMAGE1 = 0x1,
    CDS_DAMAGE2 = 0x2,
    CDS_DAMAGE3 = 0x3,
    CDS_DELETE = 0x4,
    NUM_CLEAR_DEBRIS_STATES = 0x5,
};

struct stuck_info {
    timestamp stuck_threshold_time;
    timestamp stuck_active_time;
    timestamp stuck_clear_time;
    vector stuck_pos;
    timestamp extended_stuck_time;
    float stuck_mass;
    timestamp stuck_mass_timer;
    clear_debris_states clear_debris_state;
    timestamp clear_debris_timer;
};

struct vehicle_steer_info {
    vector goal_pos;
    float curvature_goal;
    float lookahead_dist;
    float lateral_offset;
    float road_offset;
    float wheelbase;
    float inv_radius_steer;
    float vel;
    float desired_vel;
    float accel_val;
    float brake_val;
};

struct vehicle_accel_info {
    float desired_speed;
    float desired_braking_decel;
};

struct vehicle_control_info {
    float max_braking_decel;
    float max_radial_accel;
    float max_steer_curvature;
};

struct vehicle_ai {
    struct flags {
        __int8 m_ignore_repulsors : 1;
        __int8 m_goal_stop_override : 1;
        __int8 m_override_speed : 1;
        __int8 m_override_stop : 1;
        __int8 m_force_stop_reverse : 1;
        __int8 m_follow_pathfinding : 1;
        __int8 m_lateral_offset : 1;
        __int8 m_road_offset : 1;
        __int8 m_unstick_reverse : 1;
        __int8 m_jumping : 1;
        __int8 m_should_not_swerve : 1;
        __int8 m_ignore_lanes : 1;
        __int8 m_ignore_road_directionality : 1;
        __int8 left_side : 1;
        __int8 middle : 1;
        __int8 fallen_off_navmesh : 1;
        __int8 pull_off : 1;
        __int8 at_end_of_route : 1;
        __int8 use_special_roads : 1;
        __int8 need_to_rise : 1;
        __int8 obstructed_by_player : 1;
        __int8 u_turn_active : 1;
        __int8 slowing_for_u_turn : 1;
        __int8 turning : 1;
        __int8 turning_in_place : 1;
        __int8 backing_up : 1;
        __int8 is_courier : 1;
        __int8 is_riding_shotgun : 1;
    };

    vehicle_ai_state ai_state;
    vehicle_ai_state ai_last_state;
    timestamp u_turn_global_delay;
    vehicle_ai::flags flags;
    float target_speed_to_goal;
    float target_decel_to_goal;
    float override_speed;
    float initial_forward_speed;
    vehicle_repulsor_info repulsor_info;
    timestamp navmesh_path_update;
    timestamp swerve_timer;
    timestamp initial_swerve_timer;
    timestamp pull_off_timer;
    stuck_info stuck;
    unsigned int vehicle_handle;
    timestamp checkpoint_timer;
    unsigned int checkpoint_handle;
    unsigned int ambient_wait_object;
    timestamp ambient_wait_timer;
    timestamp change_sides_timer;
    vehicle_steer_info steer_info;
    vehicle_accel_info accel_info;
    vehicle_control_info base_control_info;
    vehicle_control_info active_control_info;
    navmesh_lane_spline_node* navmesh_path;
    vehicle_route_info route_info;
    __attribute__((aligned(8))) vehicle_path_info current_path_info;
    float flying_offset;
    float building_offset;
    float desired_flying_offset;
    float target_offset;
    float terrain_offset;
    float original_offset;
    float necessary_height;
    int update_failures;
    unsigned __int16 active_intersection_controller;
    circ_array<vehicle_pathfind_record, 5> pf_failure_history;
};

struct vehicle_seat_info {
    unsigned int m_current_occupant_handle;
};

struct vehicle_turret_mount {
    vehicle_turret_mount_info* info;
    unsigned int attached_turret;
};

enum vehicle_damage_area_type {
    VDA_ENGINE = 0x0,
    NUM_VEHICLE_DAMAGE_AREAS = 0x1,
};

struct vehicle_damage_area {
    vehicle_damage_area_type m_type;
    int m_max_hit_points;
    int m_hit_points;
    unsigned int m_effect_instances[2];
};

struct __attribute__((aligned(4))) vehicle_damage_event {
    unsigned int attacker_handle;
    weapon_info* attacker_weapon;
    vector damage_position;
    vector damage_normal;
    vector damage_velocity;
    float damage_radius;
    int damage_to_apply;
    damaged_by_types from_type;
    bool from_server;
    bool damage_velocity_valid;
};

struct __attribute__((aligned(8))) vehicle_navcell_info {
    unsigned __int64 last_visited_nav_cell_handle;
    timestamp last_visited_nav_cell_update_timer;
};

struct vehicle_collision_events {
    __int8 m_collided_with_world : 1;
    __int8 m_collided_with_vehicle : 1;
    __int8 m_collided_with_mover : 1;
};

struct vehicle_rdd_flags {
    __int8 m_pos_on_ground_for_create : 1;
    __int8 m_hide_vehicle : 1;
};

enum vehicle_bomb_status {
    VEHICLE_BOMB_NONE = 0x0,
    VEHICLE_BOMB_ARMED = 0x1,
};

struct vehicle_spawn_flags {
    unsigned __int32 no_save : 1;
    unsigned __int32 one_attempt : 1;
    unsigned __int32 interior_spawn : 1;
    unsigned __int32 road_spawn : 1;
    unsigned __int32 high_priority_clean_up : 1;
    unsigned __int32 light_clean_up : 1;
    unsigned __int32 force_to_ground : 1;
    unsigned __int32 air_vehicle : 1;
    unsigned __int32 static_spawn_placement : 1;
    unsigned __int32 convoy_vehicle_spawn : 1;
    unsigned __int32 mobile_vehicle_spawn : 1;
    unsigned __int32 infinite_mass : 1;
    unsigned __int32 has_car_bomb : 1;
};

struct vehicle_flags {
    unsigned __int32 activity : 1;
    unsigned __int32 old_activity : 1;
    unsigned __int32 activity_destroyed : 1;
    unsigned __int32 convoy_vehicle : 1;
    unsigned __int32 ambient_spawn : 1;
    unsigned __int32 death_reported : 1;
    unsigned __int32 no_ragdoll : 1;
    unsigned __int32 despawned_squad_vehicle : 1;
    unsigned __int32 delete_mission_vehicle : 1;
    unsigned __int32 do_not_destroy_with_squad : 1;
    unsigned __int32 m_corpse : 1;
    unsigned __int32 m_despawn_after_fade : 1;
    unsigned __int32 m_door_collision_enabled : 1;
    unsigned __int32 m_engine_running : 1;
    unsigned __int32 m_engine_smoking : 1;
    unsigned __int32 m_fading_in : 1;
    unsigned __int32 m_fading_out : 1;
    unsigned __int32 m_fading_from_nano : 1;
    unsigned __int32 m_hidden : 1;
    unsigned __int32 m_hijacked : 1;
    unsigned __int32 m_scripted_bail : 1;
    unsigned __int32 m_scripted_abandon : 1;
    unsigned __int32 m_horn_down : 1;
    unsigned __int32 m_invulnerable : 1;
    unsigned __int32 m_mission_invulnerable : 1;
    unsigned __int32 m_is_player_car : 1;
    unsigned __int32 m_kill_by_vehicle : 1;
    unsigned __int32 m_mp_honked_horn : 1;
    unsigned __int32 m_needs_repair : 1;
    unsigned __int32 m_occupied : 1;
    unsigned __int32 m_on_fire : 1;
    unsigned __int32 m_nano_sim_fire : 1;
    unsigned __int32 m_nano_sim_smoke : 1;
    unsigned __int32 m_grenade_inside : 1;
    unsigned __int32 m_released_from_cutscene : 1;
    unsigned __int32 m_resource_access_disabled : 1;
    unsigned __int32 m_reverse_last_frame : 1;
    unsigned __int32 m_series_of_honks : 1;
    unsigned __int32 m_siren_dying : 1;
    unsigned __int32 m_siren_audio_on : 1;
    unsigned __int32 m_using_horn : 1;
    unsigned __int32 pass_by_getting_closer : 1;
    unsigned __int32 m_wheels_on_ground : 1;
    unsigned __int32 m_all_wheels_on_ground : 1;
    unsigned __int32 m_only_fire_damage : 1;
    unsigned __int32 m_headlights_on : 1;
    unsigned __int32 m_emergency_lights_on : 1;
    unsigned __int32 high_priority_target : 1;
    unsigned __int32 player_may_capture : 1;
    unsigned __int32 disable_for_npc_drivers : 1;
    unsigned __int32 disable_for_player : 1;
    unsigned __int32 disable_accelerator : 1;
    unsigned __int32 locked_in_place : 1;
    unsigned __int32 fixed_motion : 1;
    unsigned __int32 disable_turrets_for_npcs : 1;
    unsigned __int32 immediate_spawn : 1;
    unsigned __int32 no_player_use : 1;
    unsigned __int32 invisible_driver : 1;
};

struct vehicle;
struct vehicle_spawn_params {
    const vehicle_info* veh_info;
    vector spawn_pos;
    const object_spawn_region* osrp;
    unsigned __int16 zone_id_xy;
    matrix spawn_orient;
    float forward_speed;
    unsigned int parent_handle;
    unsigned int building_handle;
    object_spawn_priority spawn_priority;
    vehicle_flags vflags;
    struct {
        union {
            uint32_t no_save;
            uint32_t one_attempt;
            uint32_t interior_spawn;
            uint32_t road_spawn;
            uint32_t high_priority_clean_up;
            uint32_t light_clean_up;
            uint32_t force_to_ground;
            uint32_t air_vehicle;
            uint32_t static_spawn_placement;
            uint32_t convoy_vehicle_spawn;
            uint32_t mobile_vehicle_spawn;
            uint32_t infinite_mass;
            uint32_t has_car_bomb;
        };
    } veh_spawn_flags;
    vehicle* vp; // vehicle *vp;
};

struct __attribute__((aligned(8))) vehicle : public object {
    char rdd[0x3474]; // object_stream_resource<vehicle::resource_dependent_data> rdd;
    object_spawn_priority spawn_priority;
    vehicle_info* info;
    vector last_pos;
    matrix last_orient;
    vector last_velocity;
    vector last_angular_velocity;
    float forward_velocity;
    float last_forward_velocity;
    vehicle_ai vai;
    char instance[0x428]; // vi_instance vii;
    int aim_handle;
    void* vp; // v_animate *vp;
    matrix43 last_anim_transform;
    timestamp pf_failure_timeout;
    timestamp disable_for_npc_drivers_timer;
    timestamp no_npc_entry_timer;
    object_render_distance render_distance;
    vehicle_seat_info m_seat_info[11];
    vehicle_damage_area m_damage_areas[1];
    int m_num_turret_mounts;
    vehicle_turret_mount m_turret_mounts[2];
    vehicle_bomb_status m_bomb_status;
    vehicle_collision_events m_collisions_this_frame;
    timestamp m_walker_velocity_hack;
    timestamp m_walker_velocity_hack_followup;
    timestamp m_walker_thrown_energy_scaled;
    float saved_angular_dampening;
    int walker_vehicle_collisions;
    timestamp m_vehicle_vs_building_damage;
    vehicle_damage_event damage_events[5];
    int num_damage_events;
    char damage_events_cs[0x3C]; // cs_wrapper damage_events_cs;
    timestamp m_corpse_timer;
    timestamp m_corpse_absolute_longest_timer;
    timestamp on_fire_timestamp;
    unsigned int m_corpse_effect;
    unsigned int m_exhaust_effect_normal[4];
    unsigned int m_exhaust_effect_burst[4];
    vehicle_flags m_flags;
    int m_turret_autofire_ms;
    unsigned int m_num_sub_pieces;
    vehicle_spawn_flags stream_placement_flags;
    vehicle_rdd_flags m_rdd_flags;
    unsigned int m_killer_handle;
    unsigned int most_recent_driver;
    team team_of_most_recent_driver;
    timestamp most_recent_driver_exit_time;
    timestamp damage_sound_propagate_timer;
    weapon_info* m_killer_weapon;
    int ramming_damage_taken;
    float m_electrical_damage_percent;
    float damage_percent;
    unsigned __int16 damage_func_handle;
    unsigned __int16 destroy_func_handle;
    unsigned __int16 on_enter_func_handle;
    unsigned __int16 on_exit_func_handle;
    unsigned __int16 on_take_damage_handle;
    unsigned __int16 on_collision_handle;
    unsigned __int16 on_hit_ped_handle;
    unsigned int reserved_by;
    timestamp m_sound_delay_after_explosion;
    float m_fire_damage_rate;
    float m_fire_fractional_damage;
    timestamp m_fade_timer;
    int m_fade_time;
    unsigned int m_num_mesh_deform_spheres;
    void* m_mesh_deform_sphere_list;  // mesh_deform_sphere_link *m_mesh_deform_sphere_list;
    void* m_mesh_deform_pending_list; // mesh_deform_sphere_link *m_mesh_deform_pending_list;
    char m_tag_deform_weights[32];
    vehicle_navcell_info m_navcell_info;
    timestamp emergency_light_timer;
    float stream_load_distance_sqr;
    float stream_unload_distance_sqr;
    int engine_inst;
    int engine_started_inst;
    timestamp engine_high_load_start_timer;
    int pass_by_play_id;
    float pass_by_distance;
    unsigned int m_nav_cell_detour_request_handle;
    unsigned int m_nav_cell_detour_component_request_handles[8];
    unsigned int m_num_nav_cell_detour_component_request_handles;
    float last_damage_reported;
    unsigned int spawn_node_handle;
    unsigned int squad_handle;
    timestamp vehicle_check_cover_timestamp;
    timestamp vehicle_cover_timestamp;
    vector vehicle_cover_creation_pos;
    farray<unsigned int, 10> vehicle_cover_nodes;
    int vehicle_check_cover_index;
    int vehicle_cover_index;
    char component_rinstance_cs[0x3C]; // cs_wrapper component_rinstance_cs;
    bool infinite_mass;
    bool extra_mass;
    float extra_mass_value;
};
static_assert(sizeof(vehicle) == 0x40B8);

struct walker_flags {
    unsigned __int32 reduce_impact_momentum : 1;
    unsigned __int32 in_ramming_mode : 1;
    unsigned __int32 rotating_left : 1;
    unsigned __int32 rotating_right : 1;
    unsigned __int32 teleport_components : 1;
    unsigned __int32 is_mounting : 1;
    unsigned __int32 jump_jet_on : 1;
    unsigned __int32 jump_take_off : 1;
};

struct walker_resource_dependent_data {
    int left_foot_component_idx;
    int right_foot_component_idx;
};

struct walker_component_info {
    vector desired_pos;
    matrix desired_orient;
    vector anim_pos;
    matrix anim_orient;
    float component_error;
    int has_children;
    vector debug_pos;
    matrix debug_orient;
    timestamp collide_ts;
};

enum walker_ik_joint_location {
    WALKER_IK_JOINT_LEFT_LEG = 0x0,
    WALKER_IK_JOINT_RIGHT_LEG = 0x1,
    NUM_WALKER_IK_JOINTS = 0x2,
};

struct walker_ik_joint {
    int anchor_tag;
    int joint_tag;
    int ik_tag;
    float ik_strength;
    float ik_rate_of_change;
    float correction_amount;
    vector cached_hit_point;
    bool hit_point_valid;
    float cur_foot_p;
    float cur_foot_b;
    walker_ik_joint_location location;
};

struct walker_mp_data {
    char attack_1_id;
    char attack_2_id;
    char attack_3_id;
    char attack_4_id;
    char charge_id;
};

struct mp_x_collision_prediction_info {
    timestamp check_time;
    vector last_start_pos;
    vector last_end_pos;
    vector last_pos;
    vector last_vel;
};

enum walker_model_type {
    WMT_SMALL = 0x0,
    WMT_FLAME = 0x1,
    WMT_CIVILIAN = 0x2,
};

enum walker_control_scheme {
    WCS_FACING_CAMERA = 0x0,
    WCS_CHARACTER_STYLE = 0x1,
};

struct walker : vehicle {
    object_stream_resource<walker_resource_dependent_data> walker_rdd;
    walker_flags walker_flags;
    vector chassis_pos;
    matrix chassis_orient;
    unsigned int collision_model;
    float hull_radius;
    walker_component_info comp_info[74];
    int comp_transform_order[74];
    vector steering_vector;
    float move_speed;
    float cur_rotation_speed;
    float desired_move_speed;
    vector input_velocity;
    vector chassis_pos_last_frame;
    vector actual_velocity;
    float actual_velocity_mag;
    float vertical_anim_speed;
    float y_offset;
    vector mount_vector;
    unsigned int mount_vehicle;
    unsigned int ground_obj_handle;
    unsigned int last_ground_obj_handle;
    vector ground_normal;
    vector ground_world_pos;
    timestamp ground_test_ts;
    float ground_impact_momentum;
    float ram_momentum;
    float ram_max_energy_used;
    float jump_jet_energy;
    float jump_jet_speed;
    float jump_jet_engage_time;
    int jump_jet_tag_idx;
    unsigned int jump_jet_effect;
    int jump_jet_foley;
    timestamp jump_jet_foley_disable;
    timestamp jump_timeout;
    float engine_load;
    timestamp time_since_last_supported;
    walker_model_type model_type;
    walker_control_scheme control_scheme;
    int block_movement_anim;
    block_movement_types block_movement_type;
    walker_ik_joint ik_joints[2];
    void* mp_sim_state; // multi_sim_state<multi_walker_state> *mp_sim_state;
    walker_mp_data mp_data;
    mp_x_collision_prediction_info mp_collision_prediction;
};

struct mp_collision_prediction_info {
    timestamp check_time;
    vector last_start_pos;
    vector last_end_pos;
    vector last_pos;
    vector last_vel;
};

struct automobile : vehicle {
    struct resource_dependent_data {
        void* m_hk_vehicle_data;     // hkpVehicleData *m_hk_vehicle_data;
        void* m_hk_vehicle_instance; // hk_custom_vehicle_instance *m_hk_vehicle_instance;
        unsigned int m_num_wheels;
        void* m_wheel_components[16]; // vehicle_component *m_wheel_components[16];
        unsigned int m_wheel_axle_ids[16];
        float m_wheelbase;
        unsigned int m_axle_wheel_counts[4];
        float m_wheel_radius_per_axle[4];
        float m_wheel_width_per_axle[4];
        bool m_front_wheels[16];
        bool m_back_wheels[16];
    };

    struct tire_track_decal_data {
        vector m_start_pos;
        vector m_move_dir;
        vector m_normal;
        float m_length;
        unsigned int m_decal_handle;
        unsigned int m_obj_handle;
    };

    struct wheel_effect_info {
        unsigned int m_motion_effect;
        unsigned int m_skid_effect;
        int m_skid_foley;
        unsigned int m_peel_effect;
        int m_peel_foley;
        unsigned int m_brake_effect;
        int m_brake_foley;
        circ_array<automobile::tire_track_decal_data, 3> m_track_decals;
    };

    struct collision_effect_info {
        vector m_position;
        vector m_normal;
        unsigned int m_other_handle;
        int m_foley_info;
        unsigned int m_effect_obj;
    };

    object_stream_resource<automobile::resource_dependent_data> automobile_rdd;
    automobile::wheel_effect_info m_wheel_effect_infos[16];
    int m_motion_foley;
    int m_tread_foley;
    void* m_decal_collection_data; // decal_collection_data *m_decal_collection_data;
    unsigned int m_num_decal_collections;
    float m_decal_width;
    bool m_decal_collection_occurred;
    timestamp m_wheel_effect_stopped_timer;
    bool m_wheel_effect_is_stopped;
    int honk_alr_id;
    int foley_siren;
    int foley_megaphone;
    int foley_chassis;
    int engine_peel;
    int gear_shift;
    float user_acc_input;
    timestamp time_at_max_speed;
    bool play_shift_foley;
    timestamp horn_timeout;
    automobile::collision_effect_info m_collision_impact_sounds[4];
    automobile::collision_effect_info m_collision_scraping_sounds[4];
    timestamp m_impact_sound_delay;
    timestamp m_scraping_sound_delay;
    timestamp m_chassis_sound_delay;
    timestamp brake_effect_release_timer;
    timestamp catch_fire_timestamp;
    unsigned int m_h_trailer_vehicle;
    unsigned int m_h_tractor_vehicle;
    float prev_chassis_stress;
    float max_chassis_stress;
    timestamp is_airborne;
    timestamp is_landing;
    timestamp is_skipping;
    timestamp is_skiprecovery;
    float force_assist_value;
    float powerslide_amount;
    float current_powerslide_friction;
    bool powerslide_was_handbrake_on;
    void* mp_sim_state; // multi_sim_state<multi_automobile_state> *mp_sim_state;
    mp_collision_prediction_info mp_collision_prediction;
};

struct flyer;
struct flyer_control_action : hkp_unary_action {
    flyer* fp;
};

struct flyer_flags {
    __int8 landing_gear_up : 1;
    __int8 landing_gear_collision_off : 1;
    __int8 needs_to_takeoff : 1;
    __int8 has_lift : 1;
    __int8 stay_at_constant_height : 1;
    __int8 on_ground : 1;
};

struct __attribute__((aligned(4))) flyer : vehicle {
    struct resource_dependent_data {};

    object_stream_resource<flyer::resource_dependent_data> flyer_rdd;
    flyer_control_action* ctl_action;
    float request_urgency;
    float request_max_vel;
    vector request_point;
    vector request_vel;
    vector request_lookat;
    bool request_point_is_valid;
    bool request_vel_is_valid;
    bool request_lookat_is_valid;
    bool request_stop_at_point;
    bool request_halt;
    bool wing_is_detached;
    float vehicle_mass;
    vector chassis_com_cs;
    vector chassis_com_ws;
    matrix thrust_mat_cs;
    matrix thrust_mat_ws;
    vector thrust_up_target;
    vector hover_noise_vec;
    vector hover_noise_vec_new;
    vector hover_noise_vec_old;
    timestamp hover_noise_timer;
    float hover_noise_dur;
    timestamp engine_off_suspension_period;
    float turbine_rpm_target;
    float turbine_rpm;
    float turbine_load;
    int left_wing;
    int right_wing;
    int left_canard;
    int right_canard;
    unsigned int wingtip_effect[2];
    unsigned int front_thruster[2];
    unsigned int center_thruster[2];
    unsigned int main_engines[2];
    unsigned int jetwash;
    float engine_force;
    timestamp startup_timer;
    timestamp last_player_damage;
    timestamp catch_fire_timer;
    flyer_flags flags;
};

// REF_FUNC(vehicle_request_enter,
//          bool __cdecl(rfg::human* h, rfg::vehicle* v, rfg::vehicle_enter_data* ved), 0x00bb7880);
// REF_FUNC(vehicle_request_exit, void __cdecl(rfg::human* h, rfg::vehicle_exit_data* ved),
//          0x00bb5c80);
} // namespace rfg
