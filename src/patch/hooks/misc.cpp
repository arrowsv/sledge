#include "misc.hpp"

#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/mods.hpp"
#include "patch/lua/events/save.hpp"
#include "patch/lua/manager.hpp"
#include "patch/rfg/game.hpp"
#include "patch/utils/hook.hpp"

#include <crashcatch.hpp>
#include <plog/Log.h>

namespace hooks::misc {
HOOK_FUNC(0x00941aa0, void, __cdecl, set_mod_table_hash, uint32_t mod_table_hash) {
    auto num_mods_enabled = mods::manager::get().get_enabled_mods().size();
    set_mod_table_hash_original(mod_table_hash + num_mods_enabled);
}

HOOK_FUNC(0x0058ad30, void, __cdecl, frametime_set_cap, float min, float max) {
    frametime_set_cap_original(*rfg::g_frametime_minimum() = 1.0 / config::get().fps_limit, max);
}

HOOK_FUNC(0x00c109e0, int32_t, __cdecl, keen_main, int32_t argc, char** argv) {
    CrashCatch::enable();
    auto result = keen_main_original(argc, argv);
    return result;
}

HOOK_FUNC(0xBF4570, void, __cdecl, native_print, const char* message) {
    PLOG_INFO << "[Game] " << message;
    native_print_original(message);
}

HOOK_FUNC(0x7D87E0, void, __cdecl, gameseq_push_state, rfg::game_state new_state, bool transparent,
          bool pause_beneath) {
    gameseq_push_state_original(new_state, transparent, pause_beneath);
}

HOOK_FUNC(0x7D8730, void, __cdecl, gameseq_set_state, rfg::game_state new_state,
          bool uninterruptible) {
    gameseq_set_state_original(new_state, uninterruptible);
    if (new_state == rfg::game_state::GS_GAMEPLAY)
        lua::manager::get().trigger_event(lua::events::event::save_loaded,
                                          lua::events::save_loaded_event(), {});
}

HOOK_FUNC(0x458740, const char*, __cdecl, keen_get_build_version) {
    static std::string version = std::string(keen_get_build_version_original()) + " - Sledge " +
                                 std::string(constants::version);
    return version.c_str();
}

HOOK_FUNC(0x5D2360, uint8_t, __cdecl, rfg_init_stage_1_loop_update) {
    if (config::get().skip_startup_videos)
        *rfg::g_exit_startup_videos() = true;
    return rfg_init_stage_1_loop_update_original();
}

void apply() {
    // Remove "Matchmaking" menu option
    utils::memory::write_value<uint8_t>(0x16624B0, 0);

    // Remove "Spectator" menu option
    utils::memory::write_value<uint8_t>(0x16624F0, 0);

    // Decrease match countdown time from 10 seconds to 5 seconds
    // utils::memory::write_value<int32_t>(0x9AAD8D, 5000); // Make this customisable through Lua
    //                                                      // once multiplayer scripting/maps exist

    // Enables saving while cheats are active
    // void stats_set_cheat(cheat_indexes cheat_index, uint8_t enable)
    utils::memory::write_value<uint8_t>(0x7EADED, 0);

    keen_main_apply();
    gameseq_set_state_apply();
    gameseq_push_state_apply();
    rfg_init_stage_1_loop_update_apply();
    frametime_set_cap_apply();
    keen_get_build_version_apply();
    set_mod_table_hash_apply();
}
} // namespace hooks::misc
