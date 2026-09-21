#include "misc.hpp"

#include "multiplayer.hpp"
#include "player.hpp"
#include "files.hpp"
#include "common/constants.hpp"
#include "common/config.hpp"
#include "patch/utils/hook.hpp"
#include "patch/rfg/events.hpp"
#include "patch/lua/manager.hpp"
#include "patch/lua/events/save.hpp"
#include "patch/lua/events/player.hpp"

namespace misc {
    HOOK_FUNC(OFFSET(0x00b37800, 0x00b37c10), void, __cdecl, post_event, rfg::event_data* data) {
        post_event_original(data);

        switch (data->type) {
            case rfg::event_type::EVENT_ALERT_LEVEL_CHANGED: {
                auto event = static_cast<rfg::alert_level_change_event*>(data);
                lua::manager::get().trigger_event(
                    lua::events::event::alert_level_changed,
                    lua::events::alert_level_changed_event(event->old_level, event->alert_level));
                break;
            }
            default:
                break;
        }
    }

    HOOK_FUNC(OFFSET(0x7D8730, 0x007d8710), void, __cdecl, gameseq_set_state,
              rfg::game_state new_state, bool uninterruptible) {
        gameseq_set_state_original(new_state, uninterruptible);
        if (new_state == rfg::game_state::GS_GAMEPLAY) {
            lua::manager::get().trigger_event(lua::events::event::save_loaded,
                                              lua::events::save_loaded_event(), {});
        }
    }

    HOOK_FUNC(OFFSET(0x458740, 0x00458740), const char*, __cdecl, keen_get_build_version) {
        static std::string version = std::string(keen_get_build_version_original()) + " - Sledge " +
                                     std::string(constants::version);
        return version.c_str();
    }

    HOOK_FUNC(OFFSET(0x5D2360, 0x005d2440), uint8_t, __cdecl, rfg_init_stage_1_loop_update) {
        if (config::get().game.skip_startup_videos) {
            *rfg::g_exit_startup_videos() = true;
        }
        return rfg_init_stage_1_loop_update_original();
    }

    void apply_patches() {
        // Enables saving while cheats are active
        utils::memory::write_value<uint8_t>(OFFSET(0x7EADED, 0x7EAD9D), 0);

        post_event_apply();
        gameseq_set_state_apply();
        keen_get_build_version_apply();
        rfg_init_stage_1_loop_update_apply();

        multiplayer::apply_patches();
        player::apply_patches();
        files::apply_patches();
    }
}