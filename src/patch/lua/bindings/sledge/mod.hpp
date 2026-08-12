#pragma once

#include "common/mods.hpp"
#include <sol/forward.hpp>

namespace lua::bindings::sledge {
void bind_mod(sol::state_view& lua);
void bind_mod_environment(sol::state_view& lua, sol::environment& environment,
                          const mods::mod_info& mod);
} // namespace lua::bindings::sledge
