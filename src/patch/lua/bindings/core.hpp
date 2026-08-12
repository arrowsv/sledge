#pragma once

#include <sol/forward.hpp>

namespace lua::bindings {
void bind_all(sol::state_view& lua);
} // namespace lua::bindings
