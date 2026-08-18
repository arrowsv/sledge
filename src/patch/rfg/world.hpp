#pragma once

#include "containers.hpp"
#include "math/color.hpp"
#include "patch/rfg/havok.hpp"
#include "patch/rfg/object.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {

enum voice_line_handle : uint32_t;

enum world_deserialize_state {
    DS_IDLE = 0x0,
    DS_PENDING = 0x1,
    DS_COLLECT = 0x2,
    DS_COMPRESS = 0x3,
    DS_SAVE_FINALIZE = 0x4,
};

enum world_state_mode {
    WSM_DEFAULT = 0x0,
    WSM_CHECKPOINT = 0x1,
    NUM_WORLD_STATE_MODES = 0x2,
};

enum world_zone_state {
    WZS_UNLOADED = 0x0,
    WZS_STREAMING = 0x1,
    WZS_LOADED = 0x2,
};

struct save_load_info {
    __int8 pending_new_game : 1;
    __int8 reset_destruction : 1;
    __int8 pending_save_game : 1;
    __int8 performing_save_game : 1;
    __int8 pending_save_state : 1;
    __int8 performing_save_state : 1;
    __int8 pending_single_zone : 1;
    __int8 save_game_warp : 1;
    __int8 game_save_checkpoint : 1;
    __int8 game_save_to_disk : 1;
    __int8 pending_load_game_from_memory : 1;
    __int8 auto_save_game : 1;
    __int8 saving_state_data : 1;
    __int8 player_start_at_safehouse : 1;
    vector player_start_pos;
    matrix player_start_orient;
};

struct district_flags {
    __int8 allow_cough : 1;
    __int8 allow_amb_edf_civilian_dump : 1;
    __int8 play_capstone_unlocked_lines : 1;
    __int8 disable_morale_change : 1;
    __int8 disable_control_change : 1;
};

struct nav_cell {
    et_ptr_offset<nav_cell, 1> adjacent_cells[3];
    unsigned int navp;
    unsigned int heap_session_id;
    unsigned __int16 vertices[3];
    unsigned __int16 compound_hull_reference;
    unsigned __int16 heap_data_index;
    char zone_id;
    char flags;
};

struct nav_cell_outer_edge {
    unsigned __int16 nav_cell_index;
    char edge_index;
    unsigned int adjacent_zone;
};

struct bb_pfg_layer {
    unsigned int pfg_sig;
    unsigned int pfg_version;
    unsigned __int16 num_vertices;
    et_ptr_offset<vector, 0> vertices;
    unsigned __int16 num_nav_cells;
    et_ptr_offset<nav_cell, 0> nav_cells;
    et_ptr_offset<nav_cell*, 0> nav_cell_heap;
    unsigned __int16 num_nav_cell_outer_edges;
    et_ptr_offset<nav_cell_outer_edge, 0> nav_cell_outer_edges;
    vector bbox_min;
    vector bbox_max;
};

struct bb_pfg_zone {
    bb_pfg_layer* pfg;
    unsigned int pfg_shape;
    unsigned int pfg_havok_handle;
    bb_pfg_layer* vehicle_pfg;
    unsigned int vehicle_pfg_shape;
    unsigned int vehicle_pfg_havok_handle;
};

struct obj_zone : object {
    bb_pfg_zone zone_pfg;
    unsigned int heightfield_shape;
    unsigned int stitch_piece_havok_handle;
    unsigned int district_handle;
    void* spawn_res_data;     // spawn_resource_data *spawn_res_data;
    void* ambient_spawn_info; // ambient_spawn_info *amb_spawn_info;
    float wind_min_speed;
    float wind_max_speed;
    void* terrain;                 // rfg_terrain *terrain;
    farray<void*, 40> m_occluders; // farray<rl_terrain_occluder *, 40> m_occluders;
    vector local_bmin;
    vector local_bmax;
    int aabb_phantom_index;
};

struct handle_manager_7280 {
    char status[910];
    unsigned int last_bin;
    unsigned int last_slot;
    unsigned int upper_bits;
};

struct world_state_buf {
    vector player_start_pos;
    matrix player_start_orient;
    vector player_start_pos_safehouse;
    matrix player_start_orient_safehouse;
    char* buf;
    int cur_size;
    int max_size;
};

struct zone_header {
    unsigned int signature;
    unsigned int version;
    int num_objects;
    int num_handles;
    unsigned int district_hash;
    unsigned int flags;
};

struct __attribute__((aligned(4))) world_zone {
    vector bmin;
    vector bmax;
    char name[64];
    world_zone_state state;
    zone_header* deserialize_header;
    void* deserialize_header_f; // cfile *deserialize_header_f;
    void* deserialize_f;        // cfile *deserialize_f;
    world_state_buf stored_zone_state;
    obj_zone* zone_objp;
    unsigned int srid;
    bool is_border_zone;
    handle_manager_7280 obj_handle_mgr;
    unsigned __int16 gid;
};

struct grid_info_flags {
    __int8 play_marauder_howl : 1;
    __int8 marauder_zone : 1;
};

struct __attribute__((aligned(2))) grid_info {
    unsigned __int16 gid;
    grid_info_flags flags;
};

struct __attribute__((aligned(4))) district : object {
    float control;
    float morale;
    float control_max;
    float morale_max;
    float liberated_tech_level;
    int liberated_marauder_level;
    int liberated_edf_level;
    voice_line_handle liberated_radio_line_handle;
    voice_line_handle capstone_line_1;
    voice_line_handle capstone_line_2;
    int min_edf_progression_level;
    bool liberated;
    bool needs_to_play_radio_line;
    district_flags flags;
    rfg::color color;
    unsigned int localized_name_hash;
    farray<grid_info, 21> grid_ids;
    char district_index;
    color_float vfx_tint;
    const char* load_screen_images[5];
    char num_load_screen_images;
};

struct t_district {
    const char* name;
    const char* liberated_radio_line;
    unsigned int localized_name_hash;
    unsigned int localized_name_hash_no_ar;
    float control;
    float control_max;
    float morale;
    float morale_max;
    float tech_level;
    int marauder_level;
    int edf_level;
    int edf_progression_level;
    bool liberated;
    district_flags flags;
    rfg::color color;
    rfg::color vfx_tint;
    int disc_layer;
    char index;
    const char* thumbnail;
    const char* load_screen_images[5];
    char num_load_screen_images;
    farray<grid_info, 21> list;
    t_district* next;
    t_district* previous;
};

struct territory {
    const char* name;
    float tech_level_default;
    float tech_level_max;
    char index;
    t_district* districts;
    unsigned __int16* vertical_mask_zones;
    int num_v_mask_zones;
    unsigned __int16* horiz_mask_zones;
    int num_h_mask_zones;
};

struct __attribute__((aligned(8))) world {
    bool mission_object_creation_mode;
    vector level_ambient;
    vector level_back_ambient;
    char last_loaded_territory[64];
    int max_world_objects;
    base_array<object*> all_objects;
    base_array<unsigned short> type_objects[53];
    base_array<unsigned short> subtype_objects[11];
    float tech_level;
    float tech_level_max;
    volatile unsigned int thread_id;
    char object_handle_hash[72];       // dynamic_uint_hash_table<object *> object_handle_hash;
    char destroyed_object_table[8200]; // hash_table<unsigned int, &hash_uint, 1024, unsigned short>
                                       // destroyed_object_table;
    void* save_file;                   // cfile *save_file;
    object* flagged_objects;
    object* current_flagged_object;
    char current_flagged_mode;
    world_deserialize_state deserialize_state;
    void* deserialize_pool; // virtual_mempool *deserialize_pool;
    farray<world_zone*, 32> deserialize_list;
    world_state_mode cur_world_state;
    world_state_buf stored_world_state[2];
    void* compress_stream;   // zlib_stream *compress_stream;
    void* decompress_stream; // zlib_stream *decompress_stream;
    save_load_info sl_flags;
    void* pending_game_save_slot; // game_save_info *pending_game_save_slot;
    int dlc_bundle_id;
    char pending_filename[64];
    vector pending_game_load_warp_to_pos;
    matrix pending_game_load_warp_to_orient;
    volatile bool load_aborted;
    void* grid; // stream_grid *grid;
    vector stream_pos;
    int num_territory_zones;
    world_zone** all_zones;
    world_zone* global_zone_grid[257];
    bool is_territory;
    char territory_name[128];
    int num_streaming_objects;
    bool stub_serialization_in_progress;
};

// REF_VAR(g_world, rfg::world, 0x2F97490);
// REF_VAR(g_havok_world, rfg::hkp_world, 0x02b81284);

// REF_FUNC(get_district_from_position, rfg::district* __cdecl(const rfg::vector* position), 0x78F340);

} // namespace rfg
