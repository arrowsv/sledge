#pragma once

#include "events.hpp"

namespace lua::events {
struct key_up_event : public event_context {
    int key;
    bool shift_down;
    bool control_down;
    bool alt_down;

    key_up_event(int key, bool shift_down, bool control_down, bool alt_down)
        : key(key), shift_down(shift_down), control_down(control_down), alt_down(alt_down) {}

    sol::table to_table(sol::state_view& lua) const override;
};

struct key_down_event : public event_context {
    int key;
    bool shift_down;
    bool control_down;
    bool alt_down;

    key_down_event(int key, bool shift_down, bool control_down, bool alt_down)
        : key(key), shift_down(shift_down), control_down(control_down), alt_down(alt_down) {}

    sol::table to_table(sol::state_view& lua) const override;
};

struct mouse_wheel_event : public event_context {
    int delta;
    bool shift_down;
    bool control_down;
    bool alt_down;

    mouse_wheel_event(int delta, bool shift_down, bool control_down, bool alt_down)
        : delta(delta), shift_down(shift_down), control_down(control_down), alt_down(alt_down) {}

    sol::table to_table(sol::state_view& lua) const override;
};

} // namespace lua::events
