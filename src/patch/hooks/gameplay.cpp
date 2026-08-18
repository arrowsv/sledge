#include "gameplay.hpp"

#include "patch/lua/events/player.hpp"
#include "patch/lua/manager.hpp"
#include "patch/rfg/events.hpp"
#include "patch/rfg/player.hpp"
#include "patch/rfg/camera.hpp"
#include "patch/utils/hook.hpp"

namespace hooks::gameplay {
HOOK_FUNC(OFFSET(0x00b37800, 0x00b37c10), void, __cdecl, post_event, rfg::event_data* data) {
    post_event_original(data);

    switch (data->type) {
    case rfg::event_type::EVENT_ALERT_LEVEL_CHANGED: {
        auto event = static_cast<rfg::alert_level_change_event*>(data);
        lua::manager::get().trigger_event(
            lua::events::event::alert_level_changed,
            lua::events::alert_level_changed_event(event->old_level, event->alert_level), {});
        break;
    }
    default:
        break;
    }
}

bool g_camera_overriding_position = false;
bool g_camera_overriding_orientation = false;
MID_HOOK_FUNC(OFFSET(0x6E0440, 0x006e0520), camera_update_position) {
    if (g_camera_overriding_position) {
        ctx.eip = utils::address::convert(OFFSET(0x6E04A8, 0x006e0588));
    }

    if (!g_camera_overriding_orientation) {
        rfg::g_camera()->real_orient = rfg::g_camera()->ideal_orient;
    }
}

HOOK_FUNC(OFFSET(0x00ae6290, 0x00ae66b0), void, __cdecl, player_do_frame, rfg::player* self) {
    lua::manager::get().trigger_event(lua::events::event::player_do_frame,
                                      lua::events::player_do_frame_event(self), {});
    player_do_frame_original(self);
}

void apply() {
    post_event_apply();
    camera_update_position_apply();
    player_do_frame_apply();
}
} // namespace hooks::gameplay
