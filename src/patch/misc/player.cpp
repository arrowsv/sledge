#include "player.hpp"

#include "patch/lua/events/events.hpp"
#include "patch/lua/manager.hpp"
#include "patch/lua/events/player.hpp"
#include "patch/rfg/camera.hpp"
#include "patch/utils/hook.hpp"

namespace misc::player {
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
                                          lua::events::player_do_frame_event(self));

        player_do_frame_original(self);
    }

    void apply_patches() {
        camera_update_position_apply();
        player_do_frame_apply();
    }
}