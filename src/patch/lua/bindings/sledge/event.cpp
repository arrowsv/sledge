#include "event.hpp"
#include "patch/lua/events/events.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::sledge {

    void bind_event(sol::state_view& lua) {
        auto enums = lua["enums"].get_or_create<sol::table>();

        auto events = enums.create_named("event");
        events["game_do_frame"] = events::event::game_do_frame;
        events["player_do_frame"] = events::event::player_do_frame;
        events["alert_level_changed"] = events::event::alert_level_changed;
        events["save_loaded"] = events::event::save_loaded;
        events["key_down"] = events::event::key_down;
        events["key_up"] = events::event::key_up;
        events["mouse_wheel"] = events::event::mouse_wheel;
    }
}
