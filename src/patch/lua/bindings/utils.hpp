#pragma once

#include <sol/forward.hpp>

namespace lua::api::utils {
#define BIND_FLAG(variable, type, field)                                                           \
    variable[#field] = sol::property([](type& self) -> bool { return self.field ? 1 : 0; },        \
                                     [](type& self, bool value) { self.field = value ? 1 : 0; });

template <typename T> sol::table create_table(sol::state_view& lua, T list, int count);
} // namespace lua::api::utils
