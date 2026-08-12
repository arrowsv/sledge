#pragma once

#include "salvage.hpp"

namespace rfg {
struct __attribute__((aligned(4))) explosion_info {
    char m_name[32];
    int m_unique_id;
    unsigned int m_name_crc_str;
    unsigned int flags;
    float m_radius;
    float m_secondary_radius;
    float m_knockdown_radius;
    float m_flinch_radius;
    float m_ai_sound_radius;
    unsigned int m_human_min_damage_hitpoints;
    unsigned int m_human_max_damage_hitpoints;
    unsigned int m_vehicle_min_damage_hitpoints;
    unsigned int m_vehicle_max_damage_hitpoints;
    float player_damage_mult;
    float player_veh_damage_mult;
    float player_vehicle_impulse_mult;
    float m_impulse_magnitude;
    int m_structural_damage;
    unsigned int expanding_explosion_duration;
    unsigned int expanding_explosion_delay;
    unsigned int m_num_effects;
    unsigned int m_effects[4];
    unsigned int m_num_material_effects;
    unsigned int m_material_effects[8];
    char m_material_referenece[8];
    salvage_material_type salvage_material;
    int salvage_max_pieces;
    float salvage_probability;
    int time_between_breaks;
    float half_angle_dot;
    float blast_decal_radius;
    char camera_shake_type[32];
    float camera_shake_multiplier;
    float camera_shake_falloff;
    bool ignore_orientation;
    bool always_ragdoll;
};

} // namespace rfg
