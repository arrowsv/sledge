#include "patch/rfg/explosion.hpp"
#include <sol/sol.hpp>

namespace rfg
{
void bind_explosion_info(sol::state_view &lua)
{
    auto table = lua["game"].get_or_create<sol::table>();
    
    auto explosion_info = table.new_usertype<rfg::explosion_info>("explosion_info", sol::no_constructor);
    explosion_info["name"] = sol::property([](rfg::explosion_info &self) { return std::string(self.m_name); });
    explosion_info["unique_id"] = &rfg::explosion_info::m_unique_id;
    explosion_info["flags"] = &rfg::explosion_info::flags;
    explosion_info["radius"] = &rfg::explosion_info::m_radius;
    explosion_info["secondary_radius"] = &rfg::explosion_info::m_secondary_radius;
    explosion_info["knockdown_radius"] = &rfg::explosion_info::m_knockdown_radius;
    explosion_info["flinch_radius"] = &rfg::explosion_info::m_flinch_radius;
    explosion_info["ai_sound_radius"] = &rfg::explosion_info::m_ai_sound_radius;
    explosion_info["human_min_damage_hitpoints"] = &rfg::explosion_info::m_human_min_damage_hitpoints;
    explosion_info["human_max_damage_hitpoints"] = &rfg::explosion_info::m_human_max_damage_hitpoints;
    explosion_info["vehicle_min_damage_hitpoints"] = &rfg::explosion_info::m_vehicle_min_damage_hitpoints;
    explosion_info["vehicle_max_damage_hitpoints"] = &rfg::explosion_info::m_vehicle_max_damage_hitpoints;
    explosion_info["player_damage_mult"] = &rfg::explosion_info::player_damage_mult;
    explosion_info["player_veh_damage_mult"] = &rfg::explosion_info::player_veh_damage_mult;
    explosion_info["player_vehicle_impulse_mult"] = &rfg::explosion_info::player_vehicle_impulse_mult;
    explosion_info["impulse_magnitude"] = &rfg::explosion_info::m_impulse_magnitude;
    explosion_info["structural_damage"] = &rfg::explosion_info::m_structural_damage;
    explosion_info["expanding_explosion_duration"] = &rfg::explosion_info::expanding_explosion_duration;
    explosion_info["expanding_explosion_delay"] = &rfg::explosion_info::expanding_explosion_delay;
    // explosion_info["num_effects"] = &rfg::explosion_info::m_num_effects;
    //  explosion_info["effects"] = &rfg::explosion_info::m_effects;
    // explosion_info["num_material_effects"] = &rfg::explosion_info::m_num_material_effects;
    //  explosion_info["material_effects"] = &rfg::explosion_info::m_material_effects;
    // explosion_info["material_referenece"] = &rfg::explosion_info::m_material_referenece;
    explosion_info["salvage_material"] = &rfg::explosion_info::salvage_material;
    explosion_info["salvage_max_pieces"] = &rfg::explosion_info::salvage_max_pieces;
    explosion_info["salvage_probability"] = &rfg::explosion_info::salvage_probability;
    explosion_info["time_between_breaks"] = &rfg::explosion_info::time_between_breaks;
    explosion_info["half_angle_dot"] = &rfg::explosion_info::half_angle_dot;
    explosion_info["blast_decal_radius"] = &rfg::explosion_info::blast_decal_radius;
    // explosion_info["camera_shake_type"] = &rfg::explosion_info::camera_shake_type;
    explosion_info["camera_shake_multiplier"] = &rfg::explosion_info::camera_shake_multiplier;
    explosion_info["camera_shake_falloff"] = &rfg::explosion_info::camera_shake_falloff;
    explosion_info["ignore_orientation"] = &rfg::explosion_info::ignore_orientation;
    explosion_info["always_ragdoll"] = &rfg::explosion_info::always_ragdoll;
}
} // namespace rfg
