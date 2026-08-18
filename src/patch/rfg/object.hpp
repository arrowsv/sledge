#pragma once

#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {

enum object_spawn_priority {
    SPAWN_PRIORITY_INVALID = 0xFFFFFFFF,
    SPAWN_PRIORITY_LOW = 0x0,
    SPAWN_PRIORITY_MEDIUM = 0x1,
    SPAWN_PRIORITY_HIGH = 0x2,
    SPAWN_PRIORITY_SPECIAL = 0x3,
    NUM_SPAWN_PRIORITIES = 0x4,
};

enum spawn_status_result {
    INVALID_SPAWN_STATUS_RESULT = 0xffffffff,
    SPAWN_STATUS_SUCCESS = 0x0,
    SPAWN_STATUS_STREAMING = 0x1,
    SPAWN_STATUS_FAILURE = 0x2,
    NUM_SPAWN_STATUS = 0x3
};

enum object_importance_level {
    OBJECT_IMPORTANCE_LEVEL_UNKNOWN = 0xFFFFFFFF,
    OBJECT_IMPORTANCE_LEVEL_NONE = 0x0,
    OBJECT_IMPORTANCE_LEVEL_LOW = 0x1,
    OBJECT_IMPORTANCE_LEVEL_MEDIUM = 0x2,
    OBJECT_IMPORTANCE_LEVEL_HIGH = 0x3,
    NUM_OBJECT_IMPORTANCE_LEVELS = 0x4,
};

enum object_serialize_mode { OSM_NONE = 0x0, OSM_RESTORE = 0x1, OSM_FULL = 0x2 };

enum hierarchy_notify_code {
    HN_CHILDREN_STREAMED = 0x0,
    HN_PARENT_DESTROYED = 0x1,
};

struct decal_fade_data {
    unsigned int handle;
    float opacity;
};

struct contact_node {
    unsigned int m_contacted_object;
    unsigned __int16 m_num_contacts;
    contact_node* prev;
    contact_node* next;
};

struct object_contact_info {
    contact_node* m_contact_list;
};

struct object_render_distance {
    float apparent_distance;
    int last_frame_processed;
};

struct object_flags {
    __int8 flagged_list_state : 3;
    __int8 lighting_set_once : 1;
    __int8 destroyed : 1;
    __int8 no_save : 1;
    __int8 force_full_save : 1;
    __int8 destroy_on_stream : 1;
    __int8 created_by_mission_or_activity : 1;
    __int8 dont_transform : 1;
    __int8 world_free : 1;
    __int8 streaming : 1;
    __int8 streamed : 1;
    __int8 persistent : 1;
    __int8 original : 1;
    __int8 stub : 1;
    __int8 preserve_handle : 1;
    __int8 bpo_index : 2;
    __int8 is_dependent : 1;
    __int8 visited : 1;
    __int8 special_lifetime : 1;
    __int8 serialize_protected : 1;
    __int8 _dont_use_me : 1;
    __int8 streaming_fixed : 1;
    __int8 render_flags : 4;
};

struct remote_object_flags {
    __int8 remote_object : 1;
    __int8 client_sync : 1;
    __int8 client_destroy_permission : 1;
    __int8 no_destroy_packet : 1;
    __int8 common_create : 1;
};

enum object_type {
    OT_UNDEFINED = 0xFFFFFFFF,
    OT_HUMAN = 0x0,
    OT_ITEM = 0x1,
    OT_MOVER = 0x2,
    OT_VEHICLE = 0x3,
    OT_EFFECT = 0x4,
    OT_DEBRIS = 0x5,
    OT_TURRET = 0x6,
    OT_LIGHT = 0x7,
    OT_PLAYER_START = 0x8,
    OT_COVER_NODE = 0x9,
    OT_NAVPOINT = 0xA,
    OT_SQUAD = 0xB,
    OT_CONVOY = 0xC,
    OT_CONVOY_END = 0xD,
    OT_PATROL = 0xE,
    OT_GUARD_NODE = 0xF,
    OT_SKYBOX = 0x10,
    OT_LADDER = 0x11,
    OT_CONSTRAINT = 0x12,
    OT_ZONE = 0x13,
    OT_TRIGGER_REGION = 0x14,
    OT_MARAUDER_AMBUSH_REGION = 0x15,
    OT_RESTRICTED_AREA = 0x16,
    OT_SPAWN_REGION = 0x17,
    OT_AMBIENT_SPAWN_REGION = 0x18,
    OT_VEHICLE_SPAWN_NODE = 0x19,
    OT_NPC_SPAWN_NODE = 0x1A,
    OT_TURRET_SPAWN_NODE = 0x1B,
    OT_ACTION_NODE = 0x1C,
    OT_SQUAD_SPAWN_NODE = 0x1D,
    OT_ROADBLOCK_NODE = 0x1E,
    OT_SHAPE_CUTTER = 0x1F,
    OT_DISTRICT = 0x20,
    OT_MULTI_MARKER = 0x21,
    OT_PATH_ROAD = 0x22,
    OT_LIGHT_PARAMS = 0x23,
    OT_DUMMY = 0x24,
    OT_ACTIVITY_SPAWN = 0x25,
    OT_RAID_NODE = 0x26,
    OT_SUBZONE = 0x27,
    OT_HOUSE_ARREST_NODE = 0x28,
    OT_DEMOLITIONS_MASTER_NODE = 0x29,
    OT_RIDING_SHOTGUN_NODE = 0x2A,
    OT_DELIVERY_NODE = 0x2B,
    OT_BOUNDING_BOX = 0x2C,
    OT_MISSION_START_NODE = 0x2D,
    OT_COURIER = 0x2E,
    OT_COURIER_END = 0x2F,
    OT_SAFEHOUSE = 0x30,
    OT_BFTP_NODE = 0x31,
    OT_AIR_STRIKE_DEFENSE_NODE = 0x32,
    OT_UPGRADE_NODE = 0x33,
    OT_AREA_DEFENSE_NODE = 0x34,
    NUM_OBJECT_TYPES = 0x35,
};

enum object_sub_type {
    OT_SUB_UNDEFINED = 0xffffffff,
    OT_SUB_MOVER_GENERAL = 0x0,
    OT_SUB_MOVER_RFG = 0x1,
    OT_SUB_HUMAN_NPC = 0x2,
    OT_SUB_HUMAN_PLAYER = 0x3,
    OT_SUB_VEHICLE_AUTO = 0x4,
    OT_SUB_VEHICLE_FLYER = 0x5,
    OT_SUB_VEHICLE_WALKER = 0x6,
    OT_SUB_ITEM_WEAPON = 0x7,
    OT_SUB_ITEM_PROJECTILE = 0x8,
    OT_SUB_ITEM_MULTI_FLAG = 0x9,
    OT_SUB_ITEM_MULTI_BACKPACK = 0xa,
    NUM_OBJECT_SUB_TYPES = 0xb
};

struct object;
// struct object_vtable
// {
//     void *(__thiscall *const _vector_deleting_destructor_)(object *this_, uint32_t arg2);
//     void(__thiscall *const get_bbox)(object const *this_, vector *bmin, vector *bmax);
//     void(__thiscall *const get_local_bbox)(object const *this_, vector *bmin, vector *bmax);
//     int32_t (*const j___purecall)();
//     uint8_t(__thiscall *const is_killed)(object const *this_);
//     uint8_t(__thiscall *const serialize)(object *this_, void *pblock, uint8_t load);
//     object_serialize_mode(__thiscall *const serialize_mode)(object *this_);
//     uint8_t(__thiscall *const stream)(object *this_, uint8_t load);
//     uint8_t(__thiscall *const serialize_restore_if_missing_in_save_file)(object *this_, class
//     obj_prop_block *pblock); uint8_t(__thiscall *const
//     serialize_restore_if_resetting_destruction)(class object *this_, class obj_prop_block
//     *pblock); void(__thiscall *const free_this)(class object *this_); void(__thiscall *const
//     destroy_notify)(class object *this_); void(__thiscall *const update_pos_and_orient)(class
//     object *this_, class vector const *update_pos, class matrix const *update_orient, uint8_t
//     set_havok_data); int32_t(__thiscall *const get_tag_index_from_name)(class object const
//     *this_, char const *tag_name); uint8_t(__thiscall *const get_tag_world_coords)(class object
//     const *this_, int32_t tag_index, class vector *tag_pos, class matrix *tag_orient, class
//     vector *obj_pos, class matrix *obj_orient); uint8_t(__thiscall *const
//     get_tag_local_coords)(class object const *this_, int32_t tag_index, class vector *tag_pos,
//     class matrix *tag_orient); class rl_renderable_mesh const *(__thiscall *const
//     get_static_mesh)(class object const *this_); void(__thiscall *const update_render)(class
//     object *this_, class rl_renderer *__formal0); uint8_t(__thiscall *const
//     enable_object_outline)(class object *this_, int32_t layer); uint8_t(__thiscall *const
//     disable_object_outline)(class object *this_); int32_t(__thiscall *const attach_index)(class
//     object *this_, class vector const *_pos, uint32_t parent_objp_body_handle);
//     uint8_t(__thiscall *const attach_index_is_valid)(class object *this_, int32_t index);
//     float(__thiscall *const get_mass)(class object const *this_);
//     uint8_t(__thiscall *const get_physical_material)(class object const *this_, uint32_t
//     shape_key, class vector *contact_point, class hkpWorldObject const *hk_objp);
//     uint8_t(__thiscall *const get_effect_material)(class object const *this_, uint32_t shape_key,
//     class vector *contact_point, class hkpWorldObject const *hk_objp); float(__thiscall *const
//     get_energy_scale)(class object *this_); void(__thiscall *const process_bullet_hit)(class
//     object *this_, class human *attacker, float damage, struct weapon_fire_info const
//     *fire_info); uint8_t(__thiscall *const process_melee_hit)(class object *this_, class object
//     *attacker, float damage, class vector const *impulse, class vector const *hit_pos, class
//     vector const *hit_normal, uint32_t shape_key, struct rfg::weapon_info const *w_info);
//     void(__thiscall *const hierarchy_notify)(class object *this_, enum hierarchy_notify_code
//     code); uint8_t(__thiscall *const ready_to_stream_out)(class object *this_);
//     uint32_t(__thiscall *const get_alt_hk_body_handle)(class object const *this_, uint32_t
//     index); uint32_t(__thiscall *const get_alt_hk_body_handle_index)(class object const *this_,
//     uint32_t alt_handle); int32_t (*const j___purecall_1)();
// };

struct object {
    void* vtable;
    vector position;
    matrix orient;
    object* child_ptr;
    object* child_next;
    object* child_prev;
    void* child_constraint_ptr; // constraint *child_constraint_ptr;
    void* host_constraint_ptr;  // constraint *host_constraint_ptr;
    void* attach_info_data;     // attach_info_data *attach_info;
    unsigned int havok_handle;
    object_contact_info contact_info;
    object_flags obj_flags;
    remote_object_flags remote_obj_flags;
    char mp_dcmo_index;
    int checking_reset;
    unsigned __int16 name_index;
    object* flagged_next;
    object* flagged_prev;
    unsigned int handle;
    unsigned int parent;
    void* bp_handle; // havok_bpo *bp_handle;
    unsigned __int16 all_index;
    unsigned __int16 type_index;
    unsigned __int16 subtype_index;
    char obj_type;
    char sub_type;
    vector last_known_bmin;
    vector last_known_bmax;
    unsigned int srid;
};
static_assert(sizeof(rfg::object) == 0x9C);

struct object_spawn_region_flags {
    uint8_t disabled : 1;
    uint8_t npc_only : 1;
    uint8_t vehicle_only : 1;
    uint8_t cont_attack_region : 1;
    uint8_t vrail_spawn_region : 1;
};

struct object_spawn_region : object {
    bbox local_bb;
    bbox bb;
    bbox near_bb;
    int team;
    object_spawn_region_flags flags;
};

// REF_FUNC(object_set_visible, void __stdcall(rfg::object *p_this, void *edx, bool visible),
// 0xA8C010); REF_FUNC(object_is_visible, bool __stdcall(rfg::object *p_this), 0x6C38A0);
REF_FUNC(object_set_visibility_plus_children, void __cdecl(rfg::object* object, bool visible),
         OFFSET(0x00a8c070, 0x00a8c440));

// REF_FUNC(havok_body_apply_linear_impulse, void __cdecl(uint32_t handle, const rfg::vector* impulse),
//          0x00823cb0);
// REF_FUNC(havok_body_apply_point_impulse,
//          void __cdecl(uint32_t handle, const rfg::vector* impulse, const rfg::vector* position),
//          0x00823d30);
} // namespace rfg
