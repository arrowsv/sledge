#pragma once

#include "patch/utils/memory.hpp"

#include "containers.hpp"
#include "math/matrix.hpp"
#include "math/vector.hpp"

namespace rfg {
enum control_axis_action {
    CAA_AXIS_INVALID = 0xFFFFFFFF,
    CAA_CAMERA_ROTATE = 0x0,
    CAA_CAMERA_ELEVATE = 0x1,
    CAA_WALK_TURN_LEFT_RIGHT = 0x2,
    CAA_WALK_FORWARD_BACKWARD = 0x3,
    CAA_TANK_STEER = 0x4,
    CAA_TANK_STEER_VERT = 0x5,
    CAA_TANK_CAMERA_ROTATE = 0x6,
    CAA_TANK_CAMERA_ELEVATE = 0x7,
    CAA_DRIVE_STEER = 0x8,
    CAA_DRIVE_STEER_VERT = 0x9,
    CAA_DRIVE_CAMERA_ROTATE = 0xA,
    CAA_DRIVE_CAMERA_ELEVATE = 0xB,
    CAA_ZOOM_IN_OUT = 0xC,
    CAA_CYCLE_WEAPONS = 0xD,
    CAA_STUB_1 = 0xE,
    CAA_STUB_2 = 0xF,
    CAA_STUB_3 = 0x10,
    CAA_STUB_4 = 0x11,
    CAA_STUB_5 = 0x12,
    CAA_STUB_6 = 0x13,
    CAA_STUB_7 = 0x14,
    CAA_SCROLL_BAR = 0x15,
    CAA_VDC_ACCELERATE_AXIS = 0x16,
    CAA_VDC_BRAKE_REVERSE_AXIS = 0x17,
    CAA_MAP_PAN_CAMERA_LEFT_RIGHT = 0x18,
    CAA_MAP_PAN_CAMERA_UP_DOWN = 0x19,
    NUM_CONTROL_AXIS_ACTIONS = 0x1A,
    RESERVED_NUM_CONTROL_AXIS_ACTIONS = 0x32,
};

enum camera_free_control_types {
    CAMERA_FREE_CONTROL_TYPE_NORMAL = 0x0,
    CAMERA_FREE_CONTROL_TYPE_PREDICTIVE = 0x1,
    CAMERA_FREE_CONTROL_TYPE_TREAD = 0x2,
    CAMERA_FREE_CONTROL_TYPE_TREAD_CAM_REL = 0x3,
    CAMERA_FREE_CONTROL_TYPE_COUNT = 0x4,
};

struct camera_swoop_params {
    float swoop_in_speed;
    float in_handle_lengths[3];
    float out_handle_lengths[3];
    float in_handle_lengths_swing[3];
    float out_handle_lengths_swing[3];
    float behind_head_dist;
    float swing_factor_x;
    float swing_factor_z;
};

struct free_submode_params {
    float xz_dist;
    float y_dist;
    float lookat_offset_x;
    float lookat_offset_y;
    float lookat_offset_z;
    float lookat_offset_y_delta;
    float min_elev_angle_rad;
    float max_elev_angle_rad;
    float free_fov;
    camera_swoop_params fp_swoop_params;
    float base_pitch;
    float dist_from_lookat;
    float y_axis_rotation_speed;
    int vehicle_camera_selection;
};

struct free_mode_params_flags {
    __int8 target_moved_last_frame : 1;
    __int8 suppress_target_lag : 1;
    __int8 swinging_to_dir : 1;
    __int8 elev_relaxing : 1;
    __int8 heading_is_bashed : 1;
    __int8 unresolvable_obstruction : 1;
    __int8 debug_mode : 1;
    __int8 look_back : 1;
    __int8 look_back_last : 1;
};

struct __attribute__((aligned(4))) free_mode_params {
    free_submode_params* submode_params;
    free_submode_params* cur_interior_params;
    free_submode_params* cur_exterior_params;
    free_submode_params* cur_vehicle_params;
    camera_free_control_types control_type;
    vector last_lookat_pos;
    float suppressed_target_lag_pct;
    float user_rot;
    float auto_rot;
    float auto_rot_vel;
    float user_rot_vel;
    float user_elev;
    float last_elev_angle;
    float last_vehicle_pitch;
    float desired_elev_angle;
    float control_multiplier;
    float pitch_drift_vel;
    float heading_drift_vel;
    float camera_swing_rate;
    vector debug_offset;
    float swing_percent;
    float swing_time;
    float swing_start_heading;
    float swing_goal_heading;
    vector bash_heading_dir;
    vector bash_heading_start_dir;
    float bash_heading_percent;
    float bash_heading_time;
    float cur_dist_from_lookat;
    float goal_dist_from_lookat;
    float steering_angle;
    float last_gyro_heading_offset;
    float last_gyro_pitch_offset;
    vector last_gyro_offset;
    float last_mouse_heading_offset;
    float last_mouse_pitch_offset;
    vector last_mouse_offset;
    vector mouse_absolute_pos;
    control_axis_action last_h_action;
    control_axis_action last_v_action;
    free_mode_params_flags flags;
};

struct __attribute__((aligned(4))) lookaround_mode_params {
    float rot_p;
    float rot_h;
    float pitch;
    float pitch_base;
    float prev_pitch;
    float heading;
    float heading_base;
    float prev_heading;
    float rotvel_p;
    float rotvel_h;
    float rotvel_added_p;
    float rotvel_added_h;
    float rot_p_multiplier;
    float rot_h_multiplier;
    bool ragdoll_cam;
    float recoil_start_pitch;
    __int8 over_the_shoulder : 1;
    __int8 recoiling : 1;
};

struct thirdperson_mode_params {
    vector cur_offset;
    vector desired_offset;
    float interpolation_time;
    float ragdoll_offset;
};

struct cardinal_spline {
    vector* pts;
    int num_pts;
    float tension;
};

struct mini_script_params {
    int num_knots;
    float period_per_spline_unit;
    vector pos_knots[32];
    vector fvec_knots[32];
    vector rvec_knots[32];
    cardinal_spline pos_spline;
    cardinal_spline fvec_spline;
    cardinal_spline rvec_spline;
    float cur_time;
};

struct keylist_vector {
    unsigned __int16 num_keys;
    et_ptr_offset<vector, 0> key_positions;
    et_ptr_offset<float, 0> key_times;
};

struct keylist_float {
    unsigned __int16 num_keys;
    et_ptr_offset<float, 0> key_vals;
    et_ptr_offset<float, 0> key_times;
};

struct keylist_quaternion {
    unsigned __int16 num_keys;
    et_ptr_offset<short_quaternion, 0> key_rotations;
    et_ptr_offset<float, 0> key_times;
};

struct c_cutscene_shot {
    float start_time;
    float end_time;
    keylist_vector translation_keys;
    keylist_quaternion rotation_keys;
    keylist_float fov_keys;
    keylist_float blur_keys;
    keylist_float near_plane_keys;
    keylist_float focus_start_plane_keys;
    keylist_float focus_end_plane_keys;
    keylist_float far_plane_keys;
};

struct c_cutscene_camera {
    unsigned __int16 csc_version;
    unsigned __int16 csc_num_shots;
    et_ptr_offset<c_cutscene_shot, 0> csc_shots;
};

struct cutscene_mode_params {
    c_cutscene_camera* camera_script;
    int flags;
    vector base_pos;
    matrix base_orient;
};

struct camera_view_table_entry {
    char* name;
    int change_view_time;
    int out_time_override;
    int target_focus_speed;
    int terrain_focus_speed;
    float fov_min;
    float fov_min_sp;
    float fov_max;
    float fov_zoom_percent;
    float focal_distance_min;
    float focal_distance_max;
    float focal_range_near;
    float focal_range_far;
    float focused_distance_normal;
    float focused_distance_zoom;
    float focused_dist_target_multiplier;
    float camera_distance;
    bool use_dof;
    bool use_weapon_fov;
    bool use_far_values;
    bool use_fov_zoom;
    bool override_weapon_zoom;
    bool override_weapon_max_range;
    unsigned int effect_handle;
};

struct camera_view_data {
    float camera_distance;
    float focused_distance;
    float focal_distance;
    float focal_range_near;
    float focal_range_far;
    float fov;
    bool dof_enable;
    camera_view_table_entry* last_view;
    camera_view_table_entry* current_view;
    timestamp_percent transition_timestamp;
    timestamp_percent target_zoom_timestamp;
    timestamp lost_target;
    unsigned int current_target;
    float temp_distance_override;
    float last_camera_distance;
    float target_camera_distance;
    float last_focal_distance;
    float target_focal_distance;
    float last_focused_distance;
    float target_focused_distance;
    float last_range_near;
    float target_range_near;
    float last_range_far;
    float target_range_far;
    float last_fov;
    float target_fov;
    float min_zoom;
    float max_zoom;
    float max_range;
    unsigned int effect_info_handle;
    unsigned int effect_handle;
};

struct __attribute__((aligned(8))) plane_info {
    vector4 plane;
    int neg_verts;
    int pos_verts;
    bool active;
};

struct __attribute__((aligned(4))) frustum_cache {
    vector absPlanes[9];
    int numValidCornerPoints;
    vector corners[8];
    bool dirty;
};

struct rl_frustum_base {
    int num_active_planes;
    int max_planes;
    __attribute__((aligned(16))) plane_info planes[9];
    frustum_cache cache;
};

struct __attribute__((aligned(8))) rl_view_frustum : rl_frustum_base {
    vector view_point;
};

enum camera_mode {
    CAMERA_FREE_MODE = 0x0,
    CAMERA_SLEW_MODE = 0x1,
    CAMERA_CURSOR_MODE = 0x2,
    CAMERA_MINI_SCRIPT_MODE = 0x3,
    CAMERA_CUTSCENE_SCRIPT_MODE = 0x4,
    CAMERA_DUMB_MODE = 0x5,
    CAMERA_DEATH_MODE = 0x6,
    CAMERA_LOOKAROUND_MODE = 0x7,
    CAMERA_FIRST_PERSON_MODE = 0x8,
    CAMERA_TURRET_MODE = 0x9,
    CAMERA_THIRD_PERSON_MODE = 0xa,
    CAMERA_TEST_SUITE_MODE = 0xb,
    CAMERA_SATELLITE_MODE = 0xc,
    NUM_CAMERA_MODES = 0xd
};

struct camera {
    camera_mode mode;
    camera_mode mode_stack[0x8];
    int32_t mode_stack_size;
    camera_mode level_mode;
    vector real_pos;
    vector ideal_pos;
    vector last_pos;
    matrix real_orient;
    matrix ideal_orient;
    matrix last_orient;
    float real_fov;
    float ideal_fov;
    float last_fov;
    uint32_t target_handle;
    vector last_target_pos;
    matrix last_target_orient;
    float last_aim_point_dist;
    float last_collision_fraction;
    float vertical_velocity;
    uint32_t flags;
    vector render_pos;
    matrix render_orient;
    free_mode_params free_params;
    lookaround_mode_params lookaround_params;
    thirdperson_mode_params third_person_params;
    mini_script_params mscript_params;
    cutscene_mode_params cscript_params;
    camera_view_data view_data;
    uint8_t m_dof_enable;
    float m_focus_start_A;
    float m_focus_start_B;
    float m_focus_end_B;
    float m_near_clip_dist;
    float m_far_clip_dist;
    float m_high_lod_far_clip_dist;
    uint8_t culling_frustum_valid;
    rl_view_frustum m_culling_frustum;
};

REF_VAR(g_camera, rfg::camera, 0x01de3b50);

} // namespace rfg
