#pragma once

#include "patch/rfg/human.hpp"
#include "patch/rfg/math/matrix.hpp"
#include "patch/rfg/math/vector.hpp"

namespace rfg {
struct network_to_game_handle {
    unsigned __int16 m_network_handle;
    unsigned int m_game_handle;
};

struct multi_object_state {
    vector position;
    vector linear_velocity;
    vector angular_velocity;
    matrix orientation;
    unsigned int network_time;
};

struct multi_player_blocked_info {
    int raycast_blocked_count;
};

struct multi_player_edge_correction_info {
    int increasing_velocity_count;
    float vertical_velocity;
};

struct mp_ladder_state {
    union {
        struct {
            unsigned __int8 l_state;
            unsigned __int8 l_rung;
        };
        unsigned __int16 data;
    };
};

union multi_player_state_flags {
    struct {
        unsigned __int32 equip_weapon_slot : 3;
        unsigned __int32 do_sprint : 1;
        unsigned __int32 jump_id : 2;
        unsigned __int32 is_on_ladder : 1;
        unsigned __int32 reload : 1;
        unsigned __int32 jetpack : 1;
        unsigned __int32 is_zoomed : 1;
        unsigned __int32 dont_deform_bones : 1;
        unsigned __int32 in_air_detonate : 1;
        unsigned __int32 running_attack : 1;
        unsigned __int32 detonated_charges : 1;
        unsigned __int32 charge_weapon : 2;
        unsigned __int32 melee_primary_id : 2;
        unsigned __int32 melee_secondary_id : 2;
        unsigned __int32 melee_tertiary_id : 2;
        unsigned __int32 melee_firearm_id : 2;
        unsigned __int32 firearm_trigger_down_id : 2;
        unsigned __int32 firearm_trigger_up_id : 2;
        unsigned __int32 throw_attack_id : 2;
        unsigned __int32 is_crouched : 1;
        unsigned __int32 pad_bits : 1;
    };
    unsigned int data;
};

struct multi_player_state : multi_object_state {
    matrix camera_orient;
    vector2 camera_angular_velocity;
    float forward;
    float sideways;
    float hit_points_pct;
    unsigned int ladder_handle;
    human_ragdoll_state ragdoll_state;
    int knockdown_timestamp;
    network_to_game_handle turret_handle;
    network_to_game_handle vehicle_handle;
    unsigned __int8 vehicle_seat;
    mp_ladder_state ladder_state;
    multi_player_state_flags flags;
    unsigned __int16 weapon_magazine_ammo;
    unsigned __int16 weapon_reserve_ammo;
};

} // namespace rfg
