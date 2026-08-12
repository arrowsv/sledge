#include "events.hpp"

namespace lua::events {
sol::table event_context::to_table(sol::state_view& lua) const { return lua.create_table(); }
} // namespace lua::events
