#pragma once

#include "events.hpp"
#include "patch/rfg/weapon.hpp"

namespace lua::events {
struct weapon_fire_event : public event_context {
    rfg::weapon* weapon;

    weapon_fire_event(rfg::weapon* weapon) : weapon(weapon) {}

    sol::table to_table(sol::state_view& lua) const override;
};
} // namespace lua::events
