#pragma once

#include "events.hpp"
#include "patch/rfg/game.hpp"
#include "patch/rfg/player.hpp"

namespace lua::events {
struct player_do_frame_event : public event_context {
    rfg::player* player;

    player_do_frame_event(rfg::player* p) : player(p) {}

    sol::table to_table(sol::state_view& lua) const override;
};

struct alert_level_changed_event : public event_context {
    rfg::alert_level previous_alert_level;
    rfg::alert_level new_alert_level;

    alert_level_changed_event(rfg::alert_level previous_alert_level,
                              rfg::alert_level new_alert_level)
        : previous_alert_level(previous_alert_level), new_alert_level(new_alert_level) {}

    sol::table to_table(sol::state_view& lua) const override;
};
} // namespace lua::events
