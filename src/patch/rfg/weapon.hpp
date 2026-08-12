#pragma once

#include "item.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {
enum team : uint32_t;
enum object_hit_location : uint32_t;

struct aim_drift_profile {
    char name[64];
    int min_change_direction_time;
    int max_change_direction_time;
    int acquire_time;
    float max_acquire_penalty;
    float offscreen_penalty;
    float player_penalty;
    float player_in_cover_penalty;
    float my_speed_penalty;
    float target_speed_penalty;
    float kneeling_bonus_pct;
    float return_fire_bonus_pct;
    float min_horizontal_error;
    float max_horizontal_error;
    float max_grow_rate;
    float max_decay_rate;
    float pos_vertical_scale;
    float neg_vertical_scale;
    float max_vertical_error_dist;
};

struct weight_times {
    float time;
    float wobble;
    float destable;
    float wander;
    float jitter;
    float oscillate1;
    float oscillate2;
    float direct;
    float wander_direct;
    float blur;
    float controller_vibration_strong;
    float controller_vibration_weak;
};

struct camera_shake {
    char name[32];
    int foley_ref;
    int foley_play_id;
    vector wobble;
    float wobble_variation;
    vector destable;
    float destable_frequency;
    vector wander;
    float wander_frequency;
    vector jitter;
    vector oscillate1;
    float oscillate1_frequency;
    vector oscillate2;
    float oscillate2_frequency;
    vector direct;
    vector wander_direct;
    weight_times weights[10];
    int num_weights;
};

struct weapon_info_projectile_info {
    item_info* obj_item_info;
    float start_speed;
    float max_speed;
    float acceleration;
    unsigned __int16 fuse_time;
    float max_throw_dist;
    float gravity;
    int sound;
    unsigned int effect1;
    unsigned int effect2;
    unsigned int effect3;
    unsigned int effect4;
    unsigned int flags;
    float inaccurate_flight;
    float time_until_propelled;
    float time_until_prop_expire;
    float time_until_drop;
    unsigned int damage_effect;
    camera_shake* hit_camera_shake;
};

struct damage_scaling_info {
    float scale_value;
    float damage[4];
};

enum human_melee_combat_move_id {
    HUMAN_MELEE_COMBAT_MOVE_ID_FORCE_TO_32_BITS = 0x7FFFFFFF,
    INVALID_MELEE_COMBAT_MOVE_ID = -0x1,
};

enum animation_group {
    ANIMATION_GROUP_NONE = -0x1,
    ANIMATION_GROUP_DEFAULT = 0x0,
    ANIMATION_GROUP_AK = 0x1,
    ANIMATION_GROUP_MELEE = 0x2,
    ANIMATION_GROUP_PISTOL = 0x3,
    ANIMATION_GROUP_REVOLVER = 0x4,
    ANIMATION_GROUP_RIFLE = 0x5,
    ANIMATION_GROUP_RPG = 0x6,
    ANIMATION_GROUP_MORTAR = 0x7,
    ANIMATION_GROUP_MINE = 0x8,
    ANIMATION_GROUP_HAMMER = 0x9,
    ANIMATION_GROUP_REMOTE_CHARGE = 0xA,
    ANIMATION_GROUP_TURRET_MACHINEGUN = 0xB,
    ANIMATION_GROUP_TURRET_ROCKET = 0xC,
    ANIMATION_GROUP_TURRET_RAILGUN = 0xD,
    ANIMATION_GROUP_2H_CARRY = 0xE,
    ANIMATION_GROUP_GUTTER = 0xF,
    ANIMATION_GROUP_SHOTGUN = 0x10,
    ANIMATION_GROUP_SNIPER = 0x11,
    ANIMATION_GROUP_ARC = 0x12,
    ANIMATION_GROUP_RAILGUN = 0x13,
    ANIMATION_GROUP_NANO = 0x14,
    ANIMATION_GROUP_THERMOBARIC_ROCKET_LAUNCHER = 0x15,
    ANIMATION_GROUP_PIPE = 0x16,
    ANIMATION_GROUP_SHIELD = 0x17,
    ANIMATION_GROUP_GRINDER = 0x18,
    ANIMATION_GROUP_ENFORCER = 0x19,
    NUM_ANIM_GROUPS = 0x1A,
};

enum weapon_class_type {
    WEAPON_CLASS_NONE = -0x1,
    WEAPON_CLASS_BULLET = 0x0,
    WEAPON_CLASS_LAUNCHER = 0x1,
    WEAPON_CLASS_THROWN = 0x2,
    WEAPON_CLASS_THROWN_CHARGE = 0x3,
    WEAPON_CLASS_THROWN_MINE = 0x4,
    WEAPON_CLASS_THROWN_GRENADE = 0x5,
    WEAPON_CLASS_MELEE = 0x6,
    WEAPON_CLASS_SLEDGEHAMMER = 0x7,
    WEAPON_CLASS_GUTTER = 0x8,
    WEAPON_CLASS_GRINDER = 0x9,
    WEAPON_CLASS_ARC_WELDER = 0xA,
    WEAPON_CLASS_NANO_RIFLE = 0xB,
    WEAPON_CLASS_MASS_DRIVER = 0xC,
    WEAPON_CLASS_HARPOON = 0xD,
    WEAPON_CLASS_SINGULARITY_BOMB = 0xE,
    WEAPON_CLASS_REPAIR = 0xF,
    WEAPON_CLASS_FLAME = 0x10,
    NUM_WEAPON_CLASSES = 0x11,
};

enum weapon_trigger_type {
    WEAPON_TRIGGER_TYPE_SINGLE = 0x0,
    WEAPON_TRIGGER_TYPE_AUTOMATIC = 0x1,
    WEAPON_TRIGGER_TYPE_CHARGE = 0x2,
    NUM_WEAPON_TRIGGER_TYPES = 0x3,
};

enum weapon_ammo_type {
    WEAPON_AMMO_TYPE_BULLET = 0x0,
    WEAPON_AMMO_TYPE_PROJECTILE = 0x1,
    WEAPON_AMMO_TYPE_THROWN = 0x2,
    WEAPON_AMMO_TYPE_MELEE = 0x3,
    WEAPON_AMMO_TYPE_ELECTRICITY = 0x4,
    WEAPON_AMMO_TYPE_REPAIR = 0x5,
    WEAPON_AMMO_TYPE_BLANKS = 0x6,
    WEAPON_AMMO_TYPE_FLAME = 0x7,
    NUM_WEAPON_AMMO_TYPES = 0x8,
};

struct weapon_info_flags {
    __int8 armor_piercing : 1;
    __int8 can_fine_aim : 1;
    __int8 can_scope : 1;
    __int8 shatter : 1;
    __int8 held_in_left_hand : 1;
    __int8 draw_proj_in_opposite_hand : 1;
    __int8 silent_bullets : 1;
    __int8 penetrating_bullets : 1;
    __int8 non_inventory : 1;
    __int8 use_even_spread : 1;
    __int8 disable_player_cover : 1;
    __int8 mp_selectable : 1;
    __int8 is_obvious_weapon : 1;
    __int8 auto_aim_curved_trail : 1;
    __int8 looping_effects : 1;
    __int8 never_in_cabinet : 1;
    __int8 use_secondary_weapon_heat : 1;
    __int8 dont_drop_on_death : 1;
};

struct weapon_firing_pattern {
    struct control_point {
        float range_pct;
        float min_burst_size;
        float max_burst_size;
        float min_interval;
        float max_interval;
    };

    struct ammo_point {
        float ammo_pct;
        float min_effective_range;
    };

    struct modifier {
        float multiplier;
        float adjustment;
    };

    char* name;
    weapon_firing_pattern::control_point points[8];
    int num_control_points;
    weapon_firing_pattern::ammo_point ammo_points[3];
    int num_ammo_points;
    weapon_firing_pattern::modifier alert_mod;
    weapon_firing_pattern::modifier flyer_mod;
    weapon_firing_pattern::modifier heavy_vehicle_mod;
    weapon_firing_pattern::modifier normal_vehicle_mod;
    weapon_firing_pattern::modifier covering_fire_mod;
};

struct weapon_info {
    char* name;
    checksum_string name_crc;
    int unique_id;
    weapon_info_flags flags;
    weapon_class_type weapon_class;
    item_info* weapon_obj_item_info;
    inv_item_info* weapon_inv_item_info;
    team default_team;
    char* icon_name;
    char* small_icon_name;
    char* reticule_name;
    char* fine_aim_reticule_name;
    char* mp_kill_phrase;
    animation_group weapon_anim_group;
    unsigned int muzzle_flash_effect;
    unsigned int muzzle_smoke_effect;
    unsigned int special_hit_effect;
    unsigned int special_effect;
    unsigned int secondary_special_effect;
    unsigned int overheated_effect;
    unsigned int tracer_effect;
    camera_shake* fire_camera_shake;
    bool fire_camera_shake_ignore_disabled;
    camera_shake* secondary_camera_shake;
    camera_shake* player_hit_camera_shake;
    char attachment_point[32];
    int fire_sound;
    int secondary_sound;
    int upgrade_sound;
    int reload_sound;
    int reload_sound_delay;
    int no_ammo_sound;
    int special_sound;
    int flyby_sound;
    int num_weapon_personas;
    int npc_fire_sounds[16];
    float max_range;
    float red_range;
    float max_engagement_dist;
    float min_engagement_dist;
    float max_ai_penetrating_dist;
    const weapon_firing_pattern* npc_firing_pattern;
    const aim_drift_profile* npc_aim_drift_profile;
    weapon_trigger_type trigger_type;
    weapon_ammo_type ammo_type;
    unsigned __int16 magazine_size;
    unsigned __int16 magazine_start_num;
    unsigned __int16 max_rounds;
    unsigned __int16 max_rounds_upgrade;
    unsigned __int16 ammo_box_restock;
    unsigned __int16 to_min_spread;
    unsigned __int16 to_max_spread;
    unsigned __int8 melee_group_index;
    unsigned __int8 bullet_group_index;
    unsigned __int8 tracer_frequency;
    unsigned __int8 shots_per_round;
    float firing_sound_radius;
    float npc_refire_delay;
    float default_refire_delay;
    float prefire_delay;
    int default_reload_delay;
    damage_scaling_info low_scale_damage;
    damage_scaling_info high_scale_damage;
    const explosion_info* m_explosion_info;
    const explosion_info* m_ai_explosion_info;
    float fire_cone_dot;
    float even_spread_accuracy_dot;
    float max_spread;
    float min_spread;
    float fine_aim_max_spread;
    float fine_aim_min_spread;
    float npc_max_spread;
    float npc_min_spread;
    float spread_multiplier_run;
    float ragdoll_force_shoot;
    float ragdoll_chance;
    float recoil_camera_kick;
    float recoil_impulse;
    int out_of_ammo_reload_delay;
    float overheat_cool_down_time;
    float overheat_percent_per_shot;
    float dropped_ammo_scale;
    float bullet_hole_scale;
    float headshot_multiplier;
    float zoom_magnification;
    float autoaim_override;
    float npc_autoaim;
    float aim_assist;
    float player_move_speed_multiplier;
    float npc_move_speed_multiplier;
    float alert_multiplier;
    weapon_info_projectile_info projectile_info;
    human_melee_combat_move_id standing_primary_melee_attack;
    human_melee_combat_move_id standing_secondary_melee_attack;
    human_melee_combat_move_id standing_tertiary_melee_attack;
    human_melee_combat_move_id crouching_primary_melee_attack;
    human_melee_combat_move_id crouching_secondary_melee_attack;
    human_melee_combat_move_id crouching_tertiary_melee_attack;
};

enum weapon_callback_idx {
    INVALID_WEAPON_CB_IDX = 0xFFFFFFFF,
    WEAPON_CB_IDX_PRESS_TRIGGER = 0x0,
    WEAPON_CB_IDX_RELEASE_TRIGGER = 0x1,
    WEAPON_CB_IDX_READY_TO_FIRE = 0x2,
    WEAPON_CB_IDX_CAN_FIRE = 0x3,
    WEAPON_CB_IDX_POST_FIRE = 0x4,
    NUM_WEAPON_CB_IDX = 0x5,
};

struct weapon;
struct weapon_callbacks {
    bool(__cdecl* func)(weapon_callback_idx, weapon*, unsigned int);
    unsigned int user_handle;
};

struct mp_fire_info_flags {
    union flags_union //$E89E83DC7B0A3B57C1E8BDC492E17C6D
    {
        struct flags_bitfield //$38737281F511CDB066E9B5C23F0F4E63
        {
            __int8 local_fire : 1;
            __int8 trigger_single : 1;
            __int8 hit_player : 1;
            __int8 from_server : 1;
            __int8 sim_bullet : 1;
            __int8 send_packet : 1;
        };

        flags_bitfield bitfield;
        char flag_data;
    } data;
};

struct __attribute__((aligned(4))) weapon_fire_info {
    vector start_pos;
    vector end_pos;
    unsigned int hit_handle;
    vector hit_pos;
    vector hit_normal;
    unsigned int hit_shape_key;
    unsigned int hit_alt_body_idx;
    int hit_bone;
    unsigned int nearest_human;
    weapon_info* w_info;
    char hit_physical_material;
    char hit_effect_material;
    object_hit_location hit_location;
    mp_fire_info_flags mp_flags;
};

enum electricity_hit_rating {
    ELECTRICITY_HIT_RATING_NONE = 0x0,
    ELECTRICITY_HIT_RATING_ALLIED_HUMAN = 0x1,
    ELECTRICITY_HIT_RATING_WORLD = 0x2,
    ELECTRICITY_HIT_RATING_FRIENDLY_HUMAN = 0x3,
    ELECTRICITY_HIT_RATING_OBJECT = 0x4,
    ELECTRICITY_HIT_RATING_DEAD_HUMAN = 0x5,
    ELECTRICITY_HIT_RATING_HUMAN = 0x6,
    ELECTRICITY_HIT_RATING_ELECTRIFIABLE_OBJECT = 0x7,
    ELECTRICITY_HIT_RATING_VEHICLE = 0x8,
    ELECTRICITY_HIT_RATING_UNFRIENDLY_HUMAN = 0x9,
    ELECTRICITY_HIT_RATING_HOSTILE_HUMAN = 0xA,
    NUM_ELECTRICITY_HIT_RATINGS = 0xB,
};

struct arc_welder_cache_info {
    vector hit_pos;
    vector hit_normal;
    unsigned int hit_handle;
    unsigned int hit_shape_key;
    electricity_hit_rating hit_rating;
};

struct weapon : item {
    struct weapon_flags {
        __int8 fire_info_is_new : 1;
        __int8 trigger_down : 1;
        __int8 is_linked : 1;
        __int8 delay_fire : 1;
        __int8 processed_since_last_trigger_pull : 1;
        __int8 played_dry_fire : 1;
        __int8 playing_pickup_effect : 1;
    };

    weapon* previous;
    weapon* next;
    weapon_info* info;
    unsigned int turret_handle;
    timestamp weapon_fire_sound_timestamp;
    timestamp weapon_hit_sound_timestamp;
    timestamp one_shot_delay_timestamp;
    int melee_combat_move_past;
    bool melee_combat_in_combo;
    timestamp arc_welder_post_arc_timer;
    timestamp multi_rocket_trigger_down_timer;
    int secondary_rockets_to_fire;
    unsigned int mat_fx_handle[4];
    unsigned int current_mat_fx;
    unsigned int mat_fx_clip_handle;
    unsigned int mat_fx_handle_for_clip;
    weapon::weapon_flags flags;
    weapon_callbacks cb[5];
    weapon_fire_info fire_info;
    int rounds_in_magazine;
    int rounds_in_reserve;
    float current_spread;
    char tracer_count;
    float refire_delay_time;
    float overheat_percent;
    bool overheated;
    unsigned int overheated_effect_handle;
    timestamp reload_delay_timer;
    timestamp last_fired_timer;
    float muzzle_flash_intensity;
    unsigned int muzzle_flash_effect_handle;
    unsigned int muzzle_smoke_effect_handle;
    timestamp muzzle_smoke_timestamp;
    int grip_tag_index;
    int secondary_grip_tag_index;
    int destruction_tag_index;
    int secondary_destruction_tag_index;
    int muzzle_tag_index;
    int melee_blood_effect_tag_index;
    int num_rounds_fired;
    int fire_sound_alr_id;
    int secondary_sound_id;
    int special_sound_id;
    int weapon_persona;
    float grinder_speed_percent;
    float grinder_heat_effect;
    unsigned int special_effect_handle;
    unsigned int secondary_special_effect_handle;
    farray<arc_welder_cache_info, 3> arc_welder_best_point;
};
static_assert(sizeof(weapon) == 0x2FC);

REF_FUNC(get_weapon_info_from_handle, const rfg::weapon_info* __cdecl(uint32_t handle), 0x00bd9a10);

REF_FUNC(weapon_cabinet_unlock_weapon, bool* __cdecl(const rfg::weapon_info* info, bool unlocked),
         0x0085b3e0);
REF_FUNC(weapon_cabinet_add_weapon, void* __cdecl(const rfg::weapon_info* info, bool unlocked),
         0x00877220);

REF_VAR(g_weapon_infos, rfg::weapon_info*, 0x3881C9C);
REF_VAR(g_weapon_infos_count, int, 0x3881C94);
} // namespace rfg
